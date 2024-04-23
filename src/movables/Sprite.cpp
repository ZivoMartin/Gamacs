#include "Sprite.hpp"
#include "../sprite_data.hpp"
#include "../movables/monsters/Monster.hpp"
#include "../movables/Player.hpp"
#include "../Env.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60

Sprite::Sprite(Env* env, const char* img_path, SDL_Point pos, float fx, float fy) {
	this->env = env;
	SDL_Surface* surf = IMG_Load(img_path);
	if (!surf) 
		surf = TTF_RenderText_Blended(lablib_get_font(env->get_lablib()), img_path, (SDL_Color) {255, 255, 255, 255});  
	this->sprite_sheet = SDL_CreateTextureFromSurface(env->get_ren(), surf);
	SDL_FreeSurface(surf);
	this->pos = {PIXEL_TILE_SIZE*pos.x, PIXEL_TILE_SIZE*pos.y};
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
	SDL_Point p = get_env()->convert_coord_to_pixels(*get_pos());
	SDL_Point map_dim = get_env()->game_dim();
	if (p.x > -get_width() && p.y > -get_height() && p.x < map_dim.x && p.y < map_dim.y)
		draw(p.x, p.y);
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

void Sprite::set_interactible() {
	can_interact_with_player = true;
}

bool Sprite::get_can_interact_with_player() {
	return can_interact_with_player;
}
