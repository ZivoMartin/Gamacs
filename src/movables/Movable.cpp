#include "Movable.hpp"
#include "../Env.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60
#define BASE_SPEED 10;

Movable::Movable(Env* env, const char* img_path, SDL_FPoint pos) {
	this->env = env;
	this->text = (SDL_Texture*)  cp(IMG_LoadTexture(env->get_ren(), img_path));
	this->pos = {(int) (env->win_width()*pos.x), (int) (env->win_height()*pos.y)};
	this->speed = BASE_SPEED;
}

Movable::~Movable() {
	SDL_DestroyTexture(get_text());
}

SDL_Texture* Movable::get_text() {
	return this->text;
}

void Movable::move(int dx, int dy) {
	SDL_Point* pos = get_pos();
	pos->x += dx;
	pos->y += dy;
}

void Movable::draw() {
  SDL_Point* pos = get_pos();
  SDL_Rect r = (SDL_Rect){pos->x, pos->y, BASE_WIDTH, BASE_HEIGHT};
  cc(SDL_RenderCopy(get_ren(), get_text(), NULL, &r));
}

Env* Movable::get_env() {
	return this->env;
}

SDL_Renderer* Movable::get_ren() {
	return get_env()->get_ren();
}

SDL_Point* Movable::get_pos() {
	return &this->pos;
}

int Movable::get_speed() {
	return this->speed;
}
