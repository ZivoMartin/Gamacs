#include "BattleSquare.hpp"
#include "MainBattle.hpp"
#include "powns/PownPlayer.hpp"
#include "powns/Pown.hpp"

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

#define DEFAULT 100
#define PRONOUNCED 255
#define OPPACITY 100
#define DEFAULT_COLOR {DEFAULT, DEFAULT, DEFAULT, DEFAULT}
SDL_Color BattleSquare::get_color() {
    Selected s = get_battle()->get_select();
    if (s == Move) return get_color_move();
	else if (s == Attack) return get_color_attack();
    else return DEFAULT_COLOR;       
}

#define RANGE_AND_VALID {DEFAULT, 255, DEFAULT, OPPACITY}
#define NOT_RANGE_BUT_VALID {255, DEFAULT, DEFAULT, OPPACITY}
#define RANGE_BUT_INVALID {DEFAULT, DEFAULT, DEFAULT, OPPACITY}
#define NOT_RANGE_AND_INVALID {255, DEFAULT, DEFAULT, OPPACITY*2}
SDL_Color BattleSquare::get_color_attack() {
    PownPlayer* player = get_battle()->get_player();
    SettingAttack* attack = get_battle()->get_selected_attack();
    if (!is_empty() && get_pown()->is_attackable_by_player())
        if (player->can_attack_with(pos, attack))
            return RANGE_AND_VALID;
        else
            return NOT_RANGE_BUT_VALID;
    else
        if (player->can_attack_with(pos, attack))
            return RANGE_BUT_INVALID;
        else
            return NOT_RANGE_AND_INVALID;
}

#define CAN_MOVE_ON {DEFAULT, DEFAULT, PRONOUNCED, DEFAULT}
#define CAN_NOT_MOVE_ON {PRONOUNCED, DEFAULT, DEFAULT, DEFAULT}
SDL_Color BattleSquare::get_color_move() {
    if (get_battle()->get_player()->is_valid_move(pos))
        return CAN_MOVE_ON;
    else
        return CAN_NOT_MOVE_ON;	
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
