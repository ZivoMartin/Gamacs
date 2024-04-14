#ifndef SAFE_MOVABLE
#define SAFE_MOVABLE

#include "../include.hpp"

class Env;

class Movable {

public:
	Movable(Env* env, const char* img_path, SDL_Point pos);
	~Movable();
	Env* get_env();
	virtual void draw();
	SDL_Texture* get_text();
	SDL_Renderer* get_ren();
	SDL_Point* get_pos();
	virtual void move(int dx, int dy);
	int get_speed();
	void recompute_position();

private:
	Env* env;
	SDL_Texture* text;
	SDL_Point pos;
	int speed;
};

#endif
