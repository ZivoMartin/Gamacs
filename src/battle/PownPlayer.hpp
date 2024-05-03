#ifndef SAFE_PLAYER_POWN
#define SAFE_PLAYER_POWN

#include "PownMovable.hpp"
#include "../interfaces/Player.hpp"

class Env;

class PownPlayer : public PownMovable, public Player {

public:
    PownPlayer(Env* env);
    ~PownPlayer();

    void click_on_grid(Position pos);
	void reset_pos();
	void nothing_click(Position pos);
	void move_click(Position pos);
	void attack_click(Position pos);
	void your_turn() override;
	void end_of_turn() override;
	bool is_attackable_by_monster() const override;
	bool is_attackable_by_player() const override;
	
private:
	std::vector<void (PownPlayer::*)(Position)> select_actions;
    
}; 

#endif
