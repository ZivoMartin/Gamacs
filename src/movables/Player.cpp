#include "Player.hpp"
#include "../Env.hpp"
#define IMG_PLAYER_PATH "../res/player.png"
#define PLAYER_WIDTH 0.08
#define PLAYER_HEIGHT 0.08
#define BASE_SPEED 10;
#define BASE_PLAYER_POS {MAP_WIDTH/2, MAP_HEIGHT/2}

Player::Player(Env* env) : Movable(env, IMG_PLAYER_PATH, BASE_PLAYER_POS) {}

Player::~Player() {}

void Player::draw() {
	int x, y;
	SDL_GetWindowSize(get_env()->get_win(), &x, &y);
	int ps = std::max(get_env()->win_width()*PLAYER_WIDTH, get_env()->win_height()*PLAYER_HEIGHT);
	SDL_Rect r = (SDL_Rect){x/2 - ps/2, y/2 - ps/2, ps, ps};
	cc(SDL_RenderCopy(get_ren(), get_text(), NULL, &r));
}
