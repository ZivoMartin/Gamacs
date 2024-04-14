#ifndef SAFE_GOLEM
#define SAFE_GOLEM

#include "../include.hpp"
#include "Movable.hpp"

class Env;

class Golem : public Movable {

public:
	Golem(Env* env, SDL_FPoint pos);
	~Golem();
	void action();
};

#endif
