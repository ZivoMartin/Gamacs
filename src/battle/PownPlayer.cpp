#include "PownPlayer.hpp"
#include "MainBattle.hpp"
#include "../Env.hpp"

#define PLAYER_START_POS 7, 5

PownPlayer::PownPlayer(Env* env) : PownMovable(env, PLAYER_SHEET), Player(env) {
	set_initial_pos(Position(PLAYER_START_POS));
	select_actions.resize(NbSelect);
	select_actions[Nothing] = &PownPlayer::nothing_click;
	select_actions[Move] = &PownPlayer::move_click;
 }

PownPlayer::~PownPlayer() {}

void PownPlayer::move_click(Position pos) {
	if (!is_moving()) walk_to(pos);
}

void PownPlayer::nothing_click(Position pos) {
	
}

void PownPlayer::click_on_grid(Position pos) {
	(this->*(select_actions[get_battle()->get_select()]))(pos);
}


void PownPlayer::reset_pos() {
	set_pos(Position(PLAYER_START_POS));
}

void PownPlayer::your_turn() {
	get_battle()->set_player_turn();
}

void PownPlayer::end_of_turn() {
	PownMovable::end_of_turn();
	get_battle()->disable_player_turn();
	get_battle()->set_select(Nothing);
}

