#ifndef SAFE_COLLIDER
#define SAFE_COLLIDER

class Monster;
class Player;
class Sprite;

class Collider {

public:
	virtual void collide(Sprite* sprite) {}
	virtual void collide(Player* player) {}
	virtual void collide(Monster* monster) {}
	virtual void collide(Pnj* pnj) {}
	
};

#endif
