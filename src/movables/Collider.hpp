#ifndef SAFE_COLLIDER
#define SAFE_COLLIDER


class Monster;
class Player;
class MapEntity;

class Collider {

public:
	virtual void collide(MapEntity* entity) {}
	virtual void collide(Player* player) {}
	virtual void collide(Monster* monster) {}
	virtual void collide(Pnj* pnj) {}
	
};

#endif
