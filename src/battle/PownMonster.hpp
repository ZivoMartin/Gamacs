#ifndef POWN_MONSTER_SAFE
#define POWN_MONSTER_SAFE

#include "PownMovable.hpp"


class PownMonster : public PownMovable {

public:
	PownMonster(Env* env, SpriteSheet monster_sheet);
	~PownMonster();

	void your_turn() override;
	void end_of_turn() override;
	void random_move();
	
private:

	
};



#endif
