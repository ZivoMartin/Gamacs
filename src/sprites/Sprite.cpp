#include "Sprite.hpp"
#include "../Env.hpp"
#include "../entity_settings/Setting.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60

Sprite::Sprite(Env* env, Setting* setting, float fx, float fy) {
    set_setting(setting);
    init(env, fx, fy);
}

Sprite::Sprite(Env* env, const char* text, float fx, float fy) {
    SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(env->get_lablib()), text, {255, 255, 255, 255});
    this->sprite_sheet = (SDL_Texture*) cp(SDL_CreateTextureFromSurface(env->get_ren(), surf));
    SDL_FreeSurface(surf);
    init(env, fx, fy);
}

Sprite::~Sprite() {}

void Sprite::init(Env* env, float fx, float fy) {
    this->env = env;
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


int Sprite::get_width() const {
	return this->width;
}

int Sprite::get_height() const {
	return this->height;
}

void Sprite::set_width(int w) {
	this->width = w;
}

void Sprite::set_pos(Position pos) {
    this->pos = pos;
}

void Sprite::set_height(int h) {
	this->height = h;
}

Position Sprite::get_pos() const {
	return pos;
}

void Sprite::set_size(int w, int h) {
	set_width(w);
	set_height(h);
}

SDL_Texture* Sprite::get_text() const {
	return setting->get_text();
}

Setting* Sprite::get_setting() const {
    return setting;
}

void Sprite::set_setting(Setting* setting) {
    this->setting = setting;
}

float Sprite::fx() const {
	return factors.x;
}

float Sprite::fy() const {
	return factors.y;
}

