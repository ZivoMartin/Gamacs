#include "LifeBar.hpp"
#include "../entity_settings/SettingFighter.hpp"
#include "powns/PownMovable.hpp"
#include "MainBattle.hpp"

#define BAR_WIDTH 0.8
#define BAR_HEIGHT 0.15

LifeBar::LifeBar(MainBattle* battle, PownMovable* pown) {
	this->battle = battle;
	this->pown = pown;
	actualise_hp();
}


LifeBar::~LifeBar() {
	SDL_DestroyTexture(get_hp_text());
}

SDL_Texture* LifeBar::get_hp_text() const {
	return hp_text;
}

PownMovable* LifeBar::get_pown() const {
	return pown;
}

MainBattle* LifeBar::get_battle() const {
	return battle;
}


#define RED_LIFE 255, 100, 100, 255
#define GREEN_LIFE 100, 255, 100, 255

void LifeBar::draw() const {
	if (pown->is_moving()) return;
	SettingFighter* set = get_pown()->get_setting_fighter();
	int width  = get_battle()->get_ts()*BAR_WIDTH,
		height = get_battle()->get_ts()*BAR_HEIGHT;
	int current_hp_w = width * ((float) set->get_current_hp() / set->get_max_hp());
	Position pos = pown->get_pos().battle_get_screen_coord(get_battle());
	int bar_decal = width*0.2;
	SDL_Rect life_r = {
		.x=pos.x() + bar_decal,
		.y=pos.y() + battle->get_ts() - (int) (height*1.05),
		.w=current_hp_w,
		.h=height
	};
	draw_rect(life_r, {GREEN_LIFE});
	if (!get_pown()->is_full_life()) {
		life_r.w = width - current_hp_w;
		life_r.x += current_hp_w;
		draw_rect(life_r, {RED_LIFE});
	}
	SDL_Rect hp_rect = {
		pos.x(),
		life_r.y,
		bar_decal,
		life_r.h
	};
	SDL_RenderCopy(get_battle()->get_ren(), get_hp_text(), NULL, &hp_rect);
}

void LifeBar::draw_rect(SDL_Rect r, SDL_Color c) const {
	SDL_SetRenderDrawColor(get_battle()->get_ren(), c.r, c.g, c.b, c.a);
	SDL_RenderDrawRect(get_battle()->get_ren(), &r);         
	SDL_RenderFillRect(get_battle()->get_ren(), &r);
}

void LifeBar::actualise_hp() {
	SDL_DestroyTexture(get_hp_text());
	char buff[7]; 
	sprintf(buff, "%d", get_pown()->get_current_hp());
	SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(battle->get_lablib()), buff, {255, 255, 255, 255});
    this->hp_text = (SDL_Texture*) cp(SDL_CreateTextureFromSurface(battle->get_ren(), surf));
    SDL_FreeSurface(surf);

}
