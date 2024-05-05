#ifndef BATTLE_SQUARE_SAFE
#define BATTLE_SQUARE_SAFE

#include "../include/global_include.hpp"


class MainBattle;
class Pown;

class BattleSquare {

public:
	
	BattleSquare(MainBattle* battle, Position pos);
	~BattleSquare();
	
	MainBattle* get_battle();
	Pown* get_pown();
	void set_pown(Pown* pown);
	SDL_Color get_color();
	SDL_Color get_color_move();
    SDL_Color get_color_attack();
    
	bool is_empty();
	void set_empty();
	void clicked();
	
private:
	MainBattle* battle;
	Pown* pown = nullptr;
	Position pos;
};


#endif
