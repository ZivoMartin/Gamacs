#ifndef SAFE_PLAYER
#define SAFE_PLAYER

#include "../include.hpp"
#include "Movable.hpp"

class Env;

class Player : public Movable {

public:
	Player(Env* env);
	~Player();

};

#endif
