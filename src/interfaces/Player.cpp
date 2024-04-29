#include "Player.hpp"
#include "../Env.hpp"
#define IMG_PLAYER_PATH "res/mageSheet.png"
#define PLAYER_WIDTH 0.07
#define PLAYER_HEIGHT 0.1
#define BASE_PLAYER_POS {17, 20}

Player::Player(Env* env) : Movable(env, IMG_PLAYER_PATH, BASE_PLAYER_POS, PLAYER_WIDTH, PLAYER_HEIGHT)  {}

Player::~Player() {}

void Player::action() {
	draw();
}
