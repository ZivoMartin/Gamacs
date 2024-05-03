#ifndef POWN_MONSTER_SAFE
#define POWN_MONSTER_SAFE

#include "PownMovable.hpp"

class SettingFighter;

class PownMonster : public PownMovable {

public:
	PownMonster(Env* env, SettingFighter* setting);
	~PownMonster();

	void your_turn() override;
	void move_finished() override;
    void end_of_turn() override;
	Position random_move() const;

	bool is_attackable_by_player() const override;
	bool is_attackable_by_monster() const override;
	
private:
    bool re_walk = true;
	
};



#endif
