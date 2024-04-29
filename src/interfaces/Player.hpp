#ifndef SAFE_PLAYER
#define SAFE_PLAYER

#include <vector>

#include "../sprites/Movable.hpp"
#include "Updatable.hpp"

class Env;

class Player  {

public:
	Player(Env* env);
	~Player();

private:
};

#endif
