#ifndef SAFE_STATIC
#define SAFE_STATIC
#include "../include/global_include.hpp"
#include "../interfaces/Collider.hpp"

#include "Sprite.hpp"

class Env;
class Monster;
class Player;

class Static : public Sprite {

public:
	Static(Env* env, const char* img_path, SDL_Point pos, float fx, float fy);
	~Static();
	virtual void draw(int x, int y) override;
	virtual void draw() override;

private:

};


#endif
