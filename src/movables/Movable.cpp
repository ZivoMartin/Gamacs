#include "Movable.hpp"
#include "../Env.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60
#define BASE_SPEED 3;

Movable::Movable(Env* env, const char* img_path, SDL_Point pos, float fx, float fy) {
	this->env = env;
	this->sprite_sheet = (SDL_Texture*)  cp(IMG_LoadTexture(env->get_ren(), img_path));
	this->pos = {TILE_SIZE*pos.x, TILE_SIZE*pos.y};
	this->speed = BASE_SPEED;
	this->width = BASE_WIDTH;
	this->height = BASE_HEIGHT;
	this->factors = {fx, fy};
	this->current_sprite = {0, 10};
}

Movable::~Movable() {
	SDL_DestroyTexture(get_text());
}

void Movable::set_frame_speed(int new_frame_speed) {
	frame_speed = new_frame_speed;
}

void Movable::update() {
	int win_size = std::min(get_env()->win_width(), get_env()->win_height());
	set_size(win_size*fx(), win_size*fy());
	if (!has_move) set_sprite_col(0);
	has_move = false;
}

SDL_Texture* Movable::get_text() {
	return this->sprite_sheet;
}

void Movable::move(int dx, int dy) {
	SDL_Point* pos = get_pos();
	if (frame_speed == RUN_MOD) {
		dx *= 2;
		dy *= 2;
	}
	pos->x += dx;
	pos->y += dy;
}

void Movable::draw() {
	draw(get_pos()->x, get_pos()->y);
}

void Movable::draw(int x, int y) {
  SDL_Point* pos = get_pos();
  SDL_Rect src = (SDL_Rect){
	  TOP_SS_X + current_sprite.x*SPRITE_W + current_sprite.x*SPRITE_DECALL_X,
	  TOP_SS_Y + current_sprite.y*SPRITE_H + current_sprite.y*SPRITE_DECALL_Y,
	  SPRITE_W,
	  SPRITE_H
  };
  SDL_Rect dest = (SDL_Rect){x, y, width, height};
  cc(SDL_RenderCopy(get_ren(), get_text(), &src, &dest));
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
int Movable::get_width() {
	return this->width;
}

int Movable::get_height() {
	return this->height;
}

void Movable::set_width(int w) {
	this->width = w;
}

void Movable::set_height(int h) {
	this->height = h;
}

void Movable::set_size(int w, int h) {
	set_width(w);
	set_height(h);
}

float Movable::fx() {
	return this->factors.x;
}

float Movable::fy() {
	return this->factors.y;
}

void Movable::set_sprite_col(int x) {
	this->current_sprite.x = x;
}

void Movable::set_sprite_row(int y) {
	this->current_sprite.y = y;
}

int Movable::get_sprite_col() {
	return current_sprite.x;
}

int Movable::get_sprite_row() {
	return current_sprite.y;
}

void Movable::inc_sprite_col() {
    set_sprite_col((get_sprite_col()+1)%NB_MOVE_SPRITE);
}


void Movable::set_current_sprite(int x, int y) {
	set_sprite_col(x);
	set_sprite_row(y);
}

void Movable::move(Direction dir) {
	if (env->get_now()%frame_speed == 0) inc_sprite_col();
	if (dir == Top)   {
		set_sprite_row(SPRITE_TOP_ROW);	
		move(0, -speed);
	}
	else if (dir == Bot){
		set_sprite_row(SPRITE_BOT_ROW);
		move(0, speed);
	}   
	else if (dir == Left) {
		set_sprite_row(SPRITE_LEFT_ROW);
		move(-speed, 0);
	}  
	else if (dir == Right) {
		set_sprite_row(SPRITE_RIGHT_ROW);
		move(speed, 0);
	}
	has_move = true;
}


void Movable::attack() {
	
}
