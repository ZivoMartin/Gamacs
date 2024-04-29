#include "Movable.hpp"
#include "../Env.hpp"
#include "../include/sprite_data.hpp"

#define BASE_WIDTH 60
#define BASE_HEIGHT 60
#define BASE_SPRITE 0, 10

Movable::Movable(Env* env, const SpriteSheet sprite_sheet, float fx, float fy) : Sprite(env, sprite_sheet, fx, fy) {
    this->speed = BASE_SPEED;
    set_current_sprite(BASE_SPRITE);
}

Movable::~Movable() {}

void Movable::set_frame_speed(int new_frame_speed) {
	frame_speed = new_frame_speed;
}

void Movable::update() {
	Sprite::update();
	this->action();
	update_frame();
	if (!has_move && !occupated()) set_sprite_col(0);
	has_move = false;
}

void Movable::set_speed(int s) {
	speed = s;
}

void Movable::move(int dx, int dy) {
	get_pos()->inc_x(dx);
	get_pos()->inc_y(dy);
}


void Movable::draw(int x, int y) {
	SDL_Rect src = (SDL_Rect){
		TOP_SS_X + current_sprite.x()*SPRITE_W + current_sprite.x()*SPRITE_DECALL_X-13,
		TOP_SS_Y + current_sprite.y()*SPRITE_H + current_sprite.y()*SPRITE_DECALL_Y-10,
		SPRITE_W+30,
		SPRITE_H+10
	};
	SDL_Rect dest = (SDL_Rect){x, y, get_width()+10, get_height()};
	cc(SDL_RenderCopy(get_ren(), get_text(), &src, &dest));
}

int Movable::get_speed() {
	return this->speed;
}


void Movable::set_sprite_col(int x) {
	current_sprite.set_x(x);
}

void Movable::set_sprite_row(int y) {
	current_sprite.set_y(y);
}

int Movable::get_sprite_col() {
	return current_sprite.x();
}

int Movable::get_sprite_row() {
	return current_sprite.y();
}

void Movable::inc_sprite_col() {
    set_sprite_col((get_sprite_col()+1)%nb_sprite_col);
	if (get_sprite_col() == 0) set_activity(false);
}

void Movable::set_current_sprite(int x, int y) {
	set_sprite_col(x);
	set_sprite_row(y);
}

void Movable::update_frame() {
	if (get_env()->get_now()%frame_speed == 0) inc_sprite_col();
}

void Movable::move(Direction dir) {
	if (!occupated()) {
		current_dir = dir;
		nb_sprite_col = NB_MOVE_SPRITE;
		update_frame();
		set_sprite_row(SPRITE_MOVE_ROW + dir);
		has_move = true;
	}
	if (dir == Top) move(0, -speed);
	else if (dir == Bot) move(0, speed);
	else if (dir == Left) move(-speed, 0);
	else if (dir == Right) move(speed, 0);
}


void Movable::attack(int attack_number) {
	if (!occupated()) {
		set_activity(true);
		set_sprite_row(attack_sprites_number[attack_number][0] + current_dir);
		nb_sprite_col = attack_sprites_number[attack_number][1];
	}
}

bool Movable::occupated() {
	return is_doing_something;
}

void Movable::set_activity(bool act) {
	is_doing_something = act;
}
