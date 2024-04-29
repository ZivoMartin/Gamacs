#include "Static.hpp"
#include "../include/sprite_data.hpp"
#include "../Env.hpp"


Static::Static(Env* env, const char* text, Position pos, float fx, float fy) : Sprite(env, text, pos, fx, fy) {}
Static::Static(Env* env, SpriteSheet sprite_sheet, Position pos, float fx, float fy) : Sprite(env, sprite_sheet, pos, fx, fy) {}
Static::~Static() {}


void Static::draw(int x, int y) {
	SDL_Rect dest = (SDL_Rect){x, y, get_width()+10, get_height()};
  cc(SDL_RenderCopy(get_ren(), get_text(), NULL, &dest));
}


