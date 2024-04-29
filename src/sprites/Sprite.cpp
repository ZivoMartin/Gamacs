#include "Sprite.hpp"
#include "../Env.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60

Sprite::Sprite(Env* env, SpriteSheet sprite_sheet, Position pos, float fx, float fy) {
	this->sprite_sheet = env->get_text(sprite_sheet);
    init(env, pos, fx, fy);
}

Sprite::Sprite(Env* env, const char* text, Position pos, float fx, float fy) {
    SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(env->get_lablib()), text, {255, 255, 255, 255});
    this->sprite_sheet = (SDL_Texture*) cp(SDL_CreateTextureFromSurface(env->get_ren(), surf));
    SDL_FreeSurface(surf);
    init(env, pos, fx, fy);
}

Sprite::~Sprite() {}

void Sprite::init(Env* env, Position pos, float fx, float fy) {
    this->env = env;
	this->pos = Position(pos.x()*PIXEL_TILE_SIZE, pos.y()*PIXEL_TILE_SIZE);
    set_width(BASE_WIDTH);
	set_height(BASE_HEIGHT);
	this->factors = {fx, fy};
}

void Sprite::update() {
	int win_size = std::min(get_env()->win_width(), get_env()->win_height());
	set_size(win_size*fx(), win_size*fy());
}

Env* Sprite::get_env() const {
	return env;
}

SDL_Renderer* Sprite::get_ren() const {
	return get_env()->get_ren();
}

SDL_Window* Sprite::get_win() const {
	return get_env()->get_win();
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

Position* Sprite::get_pos() {
	return &this->pos;
}

void Sprite::set_size(int w, int h) {
	set_width(w);
	set_height(h);
}

SDL_Texture* Sprite::get_text() {
	return sprite_sheet;
}

float Sprite::fx() {
	return factors.x;
}

float Sprite::fy() {
	return factors.y;
}
