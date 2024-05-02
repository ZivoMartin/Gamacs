#ifndef POWN_MONSTER_SAFE
#define POWN_MONSTER_SAFE

#include "PownMovable.hpp"


class PownMonster : public PownMovable {

public:
	PownMonster(Env* env, SpriteSheet monster_sheet);
	~PownMonster();

	void your_turn() override;
	void move_finished() override;
    void end_of_turn() override;
	Position random_move() const;
	
private:
    bool re_walk = true;
	
};



#endif
