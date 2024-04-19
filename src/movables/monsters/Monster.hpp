#ifndef SAFE_MONSTER
#define SAFE_MONSTER

#include "../Movable.hpp"

class Env;

class Monster : public Movable {

public:
	Monster(Env* env, const char* sheet_p, SDL_Point pos, float w, float h);
	~Monster();
	void draw() override;
	void action() override;
};

#endif
