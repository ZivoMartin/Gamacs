#include "PownPlayer.hpp"
#include "../Env.hpp"

#define PLAYER_START_POS 4, 5

PownPlayer::PownPlayer(Env* env) : Pown(env->get_battle()), Player(env),  Movable(env, PLAYER_SHEET, POWN_SIZE) {
	set_initial_pos(Position(PLAYER_START_POS));
 }

PownPlayer::~PownPlayer() {}


void PownPlayer::action() {
    Pown::draw();
}
