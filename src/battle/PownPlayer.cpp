#include "PownPlayer.hpp"
#include "../Env.hpp"

#define PLAYER_START_POS 7, 4

PownPlayer::PownPlayer(Env* env) : Pown(env->get_battle()), Player(env),  Movable(env, PLAYER_SHEET, Position(PLAYER_START_POS), POWN_SIZE) {}

PownPlayer::~PownPlayer() {}


void PownPlayer::action() {
    Pown::draw();
}
