#include "Monster.hpp"
#include "../Player.hpp"
#include "../../Env.hpp"

#define MONSTER_SPEED 1

Monster::Monster(Env* env, const char* sheet_p, SDL_Point pos, float w, float h) : Movable(env, sheet_p, pos, w, h){
	set_speed(MONSTER_SPEED);
}

Monster::~Monster() {}

void Monster::action() {
	int now = get_env()->get_now();
	if (now%200<50) this->move(Bot);
	else if (now%200<100) this->move(Right);
	else if (now%200<150) this->move(Top);
	else if (now%200<200) this->move(Left);
	this->update();
	this->draw();
}

void Monster::draw() {
	SDL_Point p = get_env()->convert_coord_to_pixels(*get_pos());
	SDL_Point map_dim = get_env()->game_dim();
	int w = get_width();
	int h = get_height();
	if (p.x > -w && p.y > -h && p.x < map_dim.x && p.y < map_dim.y) Movable::draw(p.x, p.y);
}
