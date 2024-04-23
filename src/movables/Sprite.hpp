#ifndef SAFE_SPRITE
#define SAFE_SPRITE
#include "../include.hpp"
#include "Collider.hpp"

class Env;
class Monster;
class Player;

class Sprite : public Collider {

public:
	Sprite(Env* env, const char* img_path, SDL_Point pos, float fx, float fy);
	~Sprite();
	virtual void update();
	Env* get_env();
	virtual void draw(int x, int y);
	virtual void draw();
	SDL_Texture* get_text();
	SDL_Renderer* get_ren();
	SDL_Point* get_pos();

	int get_width();
	int get_height();
	void set_width(int w);
	void set_height(int h);
	void set_size(int w, int h);
	

	float fx();
	float fy();

	virtual void interact_with_player() {}
	void set_interactible();
	bool get_can_interact_with_player();
	
private:
	Env* env;
	SDL_Texture* sprite_sheet;
	SDL_Point pos;
	SDL_FPoint factors;
	int width, height;
	bool can_interact_with_player = false;
};


#endif
