#include "Player.hpp"

#define IMG_PLAYER_PATH "../res/player.png"
#define PLAYER_WIDTH 60
#define PLAYER_HEIGHT 60
#define BASE_SPEED 10;
#define BASE_PLAYER_POS {0.5, 0.5}

Player::Player(Env* env) : Movable(env, IMG_PLAYER_PATH, BASE_PLAYER_POS) {}

Player::~Player() {}
