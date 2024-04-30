#include "PownPlayer.hpp"
#include "../Env.hpp"

#define PLAYER_START_POS 7, 5

PownPlayer::PownPlayer(Env* env) : PownMovable(env, PLAYER_SHEET), Player(env) {
	set_initial_pos(Position(PLAYER_START_POS));
 }

PownPlayer::~PownPlayer() {}


void PownPlayer::click_on_grid(Position pos) {
    if (!is_moving()) walk_to(pos);
}


void PownPlayer::reset_pos() {
	get_pos()->set_pos(PLAYER_START_POS);
}
