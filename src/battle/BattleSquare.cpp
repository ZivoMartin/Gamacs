#include "BattleSquare.hpp"
#include "MainBattle.hpp"
#include "PownPlayer.hpp"
#include "Pown.hpp"

#define NOTHING nullptr

BattleSquare::BattleSquare(MainBattle* battle, Position pos) {
	this->battle = battle;
	this->pos = pos;
}

BattleSquare::~BattleSquare() {
	if (pown != nullptr) delete pown;
}
	
MainBattle* BattleSquare::get_battle() {
	return battle;
}

Pown* BattleSquare::get_pown() {
	return pown;
}

void BattleSquare::set_pown(Pown* pown) {
	this->pown = pown;
}

#define DEFAULT_COLOR {100, 100, 100, 100}

SDL_Color BattleSquare::get_color() {
    if (get_battle()->get_select() == Move)
		if (get_battle()->get_player()->is_valid_move(pos))
			return {100, 100, 200, 100};
		else
			return {200, 100, 100, 100};	
	else if (get_battle()->get_select() == Attack)
		if (get_battle()->get_player()->can_attack_with(pos, get_battle()->get_selected_attack()))
			return {255, 200, 200, 100};
		else
			if (!is_empty() && get_pown()->is_attackable_by_player())
				return {100, 255, 100, 100};
			else
				return {255, 100, 100, 200};

    else 
        return DEFAULT_COLOR;       
}




bool BattleSquare::is_empty() {
	return get_pown() == NOTHING;
}

void BattleSquare::set_empty() {
	set_pown(NOTHING);
}

void BattleSquare::clicked() {
	if (!is_empty()) get_pown()->clicked();
}
