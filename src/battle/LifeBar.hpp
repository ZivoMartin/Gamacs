#ifndef  LIFEBAR_SAFE
#define LIFEBAR_SAFE


#include "../include/global_include.hpp"

class PownMovable;
class MainBattle;

class LifeBar {

public:

	LifeBar(MainBattle* battle, PownMovable* pown);
	~LifeBar();

	PownMovable* get_pown() const;
	void draw() const;
	MainBattle* get_battle() const;
	SDL_Texture* get_hp_text() const;
	void actualise_hp();
	
private:

	void draw_rect(SDL_Rect r, SDL_Color c) const;
	
	MainBattle* battle;
	PownMovable* pown;
	SDL_Texture* hp_text = nullptr;
	
};







#endif

