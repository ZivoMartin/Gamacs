#include "Player.hpp"
#include "../Env.hpp"
#define IMG_PLAYER_PATH "../res/player.png"
#define PLAYER_WIDTH 60
#define PLAYER_HEIGHT 60
#define BASE_SPEED 10;
#define BASE_PLAYER_POS {MAP_WIDTH/2, MAP_HEIGHT/2}

Player::Player(Env* env) : Movable(env, IMG_PLAYER_PATH, BASE_PLAYER_POS) {}

Player::~Player() {}

void Player::draw() {
	int x, y;
	SDL_GetWindowSize(get_env()->get_win(), &x, &y);
	SDL_Rect r = (SDL_Rect){x/2 - PLAYER_WIDTH/2, y/2 - PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT};
	cc(SDL_RenderCopy(get_ren(), get_text(), NULL, &r));
}
