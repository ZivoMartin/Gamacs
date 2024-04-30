#include "PownMonster.hpp"

#define BASE_POS_MONSTER 4, 1

PownMonster::PownMonster(Env* env, SpriteSheet monster_sheet) : PownMovable(env, monster_sheet) {
	set_initial_pos(Position(BASE_POS_MONSTER));
}

PownMonster::~PownMonster() {}
