#ifndef SAFE_MONSTER
#define SAFE_MONSTER

#include "../MapEntity.hpp"
#include "../../../interfaces/MovableFighter.hpp"

class Env;

class Monster : public MovableFighter, public MapEntity {

public:
	Monster(Env* env, Kind monster_kind, Position pos, float w, float h);
	~Monster();
	void action() override;
	void collide(MapEntity* entity) override;
	void collide(GamePlayer* player) override;
	void interact_with_player() override;
    
};

#endif
