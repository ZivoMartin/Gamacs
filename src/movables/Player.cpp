#include "Player.hpp"
#include "../Env.hpp"
#define IMG_PLAYER_PATH "../res/mageSheet.png"
#define PLAYER_WIDTH 0.07
#define PLAYER_HEIGHT 0.1
#define BASE_PLAYER_POS {17, 20}

Player::Player(Env* env) : Movable(env, IMG_PLAYER_PATH, BASE_PLAYER_POS, PLAYER_WIDTH, PLAYER_HEIGHT) {
	this->set_current_sprite(0, 10);
}

Player::~Player() {}

void Player::action() {
	draw();
}

void Player::draw() {
	int x, y;
	SDL_GetWindowSize(get_env()->get_win(), &x, &y);
	Movable::draw(x/2 - get_width()/2, y/2 - get_height()/2);
}

void Player::interact() {
	
}

