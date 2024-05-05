#include "PownMonster.hpp"
#include "../MainBattle.hpp"
#include "../../Env.hpp"
#include "../../entity_settings/SettingFighter.hpp"
#include "../../entity_settings/SettingAttack.hpp"
#define BASE_POS_MONSTER 1, 0


PownMonster::PownMonster(Env* env, SettingFighter* setting) : PownMovable(env, setting) {
	set_initial_pos(Position(BASE_POS_MONSTER));
	set_ap(0);
}

PownMonster::~PownMonster() {}

void PownMonster::your_turn() {
	walk_to(random_move());
}

void PownMonster::move_finished() {
    PownMovable::move_finished();
    Position p = random_move();
    if (re_walk) walk_to(p);
    re_walk = true;
}

void PownMonster::end_of_turn() {
    PownMovable::end_of_turn();
    re_walk = false;
}

Position PownMonster::random_move() const {
    Position pos[4] = {Position(0, -1), Position(-1, 0), Position(0, 1), Position(1, 0)};
    Position random = pos[get_env()->random(0, 3)];
    while (
        !get_battle()->is_valid_pos(get_pos() + random)
        || get_battle()->get(get_pos() + random) != nullptr)
        random = pos[get_env()->random(0, 3)];
    return random + get_pos();
}

bool PownMonster::is_attackable_by_player() const {
	return true;
}

bool PownMonster::is_attackable_by_monster() const {
	return false;
}
