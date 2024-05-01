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
	void your_turn() override;
	void end_of_turn() override;
	
private:
	std::vector<void (PownPlayer::*)(Position)> select_actions;
    
}; 

#endif
