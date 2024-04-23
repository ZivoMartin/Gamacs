#ifndef SAFE_PLAYER
#define SAFE_PLAYER

#include <vector>
#include "Movable.hpp"

class Env;

class Player : public Movable {

public:
	Player(Env* env);
	~Player();
	void interact();
	void draw() override;
	void action() override;
	void collide(Monster* monster) override;
	void collide(Sprite* sprite) override;
	void collide(Pnj* pnj) override;

private:
	std::vector<Sprite*> sprites_around;
};

#endif
