#include "Monster.hpp"
#include "../Player.hpp"
#include "../../Env.hpp"

Monster::Monster(Env* env, const char* sheet_p, SDL_Point pos, float w, float h) : Movable(env, sheet_p, pos, w, h){}

Monster::~Monster() {}

void Monster::action() {
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
