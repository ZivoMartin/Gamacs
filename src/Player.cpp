#include "Player.hpp"


Player::Player(Env* env) {
	this->env = env;
}

Player::~Player() {}


void Player::draw() {}

Env* Player::get_env() {
	return this->env;
}
