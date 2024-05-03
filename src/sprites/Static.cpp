#include "Static.hpp"
#include "../include/sprite_data.hpp"
#include "../Env.hpp"


Static::Static(Env* env, const char* text, float fx, float fy) : Sprite(env, text, fx, fy) {}
Static::Static(Env* env, Setting* setting, float fx, float fy) : Sprite(env, setting, fx, fy) {}
Static::~Static() {}


void Static::draw(int x, int y) {
	SDL_Rect dest = (SDL_Rect){x, y, get_width()+10, get_height()};
  cc(SDL_RenderCopy(get_ren(), get_text(), NULL, &dest));
}


