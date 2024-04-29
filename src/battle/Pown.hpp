#ifndef SAFE_POWN
#define SAFE_POWN

#include "../include/global_include.hpp"
#include "../interfaces/Updatable.hpp"

#define POWN_SIZE 0.1, 0.12

class MainBattle;

class Pown : virtual public Updatable {
    
public:
    Pown(MainBattle* battle);
    ~Pown();

	void set_initial_pos(Position p) override;
    void draw() override;
    
    MainBattle* get_battle();

private:
    MainBattle* battle;
};



#endif
