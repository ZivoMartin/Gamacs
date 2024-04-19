#ifndef SAFE_PLAYER
#define SAFE_PLAYER

#include "Movable.hpp"

class Env;

class Player : public Movable {

public:
	Player(Env* env);
	~Player();
	void draw() override;
	void action() override;
	void interact();
};

#endif
