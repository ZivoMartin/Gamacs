#ifndef SAFE_PLAYER_POWN
#define SAFE_PLAYER_POWN

#include "Pown.hpp"
#include "../interfaces/Player.hpp"
#include "../sprites/Movable.hpp"

class Env;

class PownPlayer : public Movable, public Pown, public Player {

public:
    PownPlayer(Env* env);
    ~PownPlayer();

    void action() override;
    
}; 

#endif
