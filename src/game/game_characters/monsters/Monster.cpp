#include "Monster.hpp"
#include "../GamePlayer.hpp"
#include "../../../Env.hpp"
#include "../../../entity_settings/SettingFighter.hpp"
#define MONSTER_SPEED 1

Monster::Monster(Env* env, Kind monster_kind, Position pos, float w, float h) : MovableFighter(env, monster_kind, w, h) {
	set_initial_pos(pos);
	set_speed(MONSTER_SPEED);
	set_interactible();
}

Monster::~Monster() {}

void Monster::action() {
	int now = get_env()->get_now();
	if (!occupated()) {
		if (now%200<50) 	  this->move(Bot);
		else if (now%200<100) this->move(Right);
		else if (now%200<150) this->move(Top);
		else if (now%200<200) this->move(Left);
	}
	MapEntity::draw();
}


void Monster::collide(MapEntity* entity) {
	entity->collide(this);
}

void Monster::collide(GamePlayer* player) {}

void Monster::interact_with_player() {
	get_env()->go_battle(get_setting_fighter());
}
