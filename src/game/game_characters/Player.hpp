#ifndef SAFE_PLAYER
#define SAFE_PLAYER

#include <vector>
#include "MapEntity.hpp"
#include "../../sprites/Movable.hpp"
#include "../../interfaces/Collider.hpp"

class Env;

class Player : public Movable, public MapEntity {

public:
	Player(Env* env);
	~Player();
	void interact();
	void draw() override;
	void action() override;
	void collide(Monster* monster) override;
	void collide(MapEntity* entity) override;
	void collide(Pnj* pnj) override;

private:
	std::vector<MapEntity*> entity_around;
};

#endif
