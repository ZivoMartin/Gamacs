#ifndef SAFE_MONSTER
#define SAFE_MONSTER

#include "../Movable.hpp"

class Env;

class Monster : public Movable {

public:
	Monster(Env* env, const char* sheet_p, SDL_Point pos, float w, float h);
	~Monster();
	void action() override;
	void collide(Sprite* sprite) override;
	void collide(Player* player) override;
	void interact_with_player() override;
};

#endif
