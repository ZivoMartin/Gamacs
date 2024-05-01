#include "PownMonster.hpp"
#include "MainBattle.hpp"

#define BASE_POS_MONSTER 0, 0


PownMonster::PownMonster(Env* env, SpriteSheet monster_sheet) : PownMovable(env, monster_sheet) {
	set_initial_pos(Position(BASE_POS_MONSTER));
}

PownMonster::~PownMonster() {}

void PownMonster::your_turn() {
	random_move();
}


void PownMonster::end_of_turn() {
	PownMovable::end_of_turn();
}

void PownMonster::random_move() {
	if (get_turn_pm() != 0) {
		
	}
}
