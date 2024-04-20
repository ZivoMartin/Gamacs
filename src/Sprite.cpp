#include "Sprite.hpp"
#include "sprite_data.hpp"
#include "Env.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60

Sprite::Sprite(Env* env, const char* img_path, SDL_Point pos, float fx, float fy) {
	this->env = env;
	this->sprite_sheet = (SDL_Texture*)  cp(IMG_LoadTexture(env->get_ren(), img_path));
	this->pos = {TILE_SIZE*pos.x, TILE_SIZE*pos.y};
	this->width = BASE_WIDTH;
	this->height = BASE_HEIGHT;
	this->factors = {fx, fy};
}

Sprite::~Sprite() {
	SDL_DestroyTexture(get_text());
}

void Sprite::update() {
	int win_size = std::min(get_env()->win_width(), get_env()->win_height());
	set_size(win_size*fx(), win_size*fy());
}

SDL_Texture* Sprite::get_text() {
	return this->sprite_sheet;
}

void Sprite::draw() {
	draw(get_pos()->x, get_pos()->y);
}

void Sprite::draw(int x, int y) {
  SDL_Rect dest = (SDL_Rect){x, y, width+10, height};
  cc(SDL_RenderCopy(get_ren(), get_text(), NULL, &dest));
}

Env* Sprite::get_env() {
	return this->env;
}

SDL_Renderer* Sprite::get_ren() {
	return get_env()->get_ren();
}

SDL_Point* Sprite::get_pos() {
	return &this->pos;
}

int Sprite::get_width() {
	return this->width;
}

int Sprite::get_height() {
	return this->height;
}

void Sprite::set_width(int w) {
	this->width = w;
}

void Sprite::set_height(int h) {
	this->height = h;
}

void Sprite::set_size(int w, int h) {
	set_width(w);
	set_height(h);
}

float Sprite::fx() {
	return this->factors.x;
}

float Sprite::fy() {
	return this->factors.y;
}

