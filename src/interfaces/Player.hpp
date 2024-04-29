#ifndef SAFE_PLAYER
#define SAFE_PLAYER

#include <vector>

#include "../sprites/Movable.hpp"
#include "Updatable.hpp"

class Env;

class Player : public Movable, virtual Updatable {

public:
	Player(Env* env);
	~Player();
	void action() override;
    virtual void draw() override = 0;

private:
};

#endif
