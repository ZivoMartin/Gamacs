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
    void clicked() override;
    
    MainBattle* get_battle() const;
    Position get_move_delta() const;
    void inc_md_x(int x);
    void inc_md_y(int y);
    void reset_move_delta();
    virtual bool is_attackable_by_player() const = 0;
	virtual bool is_attackable_by_monster() const = 0;
	
private:
    Position move_delta = Position(0, 0);
    MainBattle* battle;
};



#endif
