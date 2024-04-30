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
	

    
}; 

#endif
