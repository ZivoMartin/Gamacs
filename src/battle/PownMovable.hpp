#ifndef SAFE_MOVABLE_POWN
#define SAFE_MOVABLE_POWN

#include "../sprites/Movable.hpp"
#include "Pown.hpp"

#define MOTIONLESS -1
#define REACHED 0

class Env;

class PownMovable : public Movable, public Pown {

public:
    PownMovable(Env* env, SpriteSheet sprite_sheet);
    ~PownMovable();
    
    void action() override;
    void walk_to(Position pos);
    bool is_moving();
    void actualise_walk_timer();
    void reach_square();
    
private:
    Position asked_pos;
    int walk_timer = MOTIONLESS;
    Direction current_dir;
    std::vector<Position> positions;
};



#endif
