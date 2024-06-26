#ifndef SAFE_MOVABLE_POWN
#define SAFE_MOVABLE_POWN

#include "../../interfaces/MovableFighter.hpp"
#include "Pown.hpp"

#define DEFAULT_MP 5
#define DEFAULT_AP 4
#define MOTIONLESS -1
#define REACHED 0

class SettingAttack;
class SettingFighter;
class Env;
class LifeBar;

class PownMovable : public MovableFighter, public Pown {

public:
    PownMovable(Env* env, SettingFighter* setting);
    ~PownMovable();
    
    void action() override;
    bool walk_to(Position pos);
    bool is_moving() const;
    void actualise_walk_timer();
    void reach_square();
	virtual void move_finished();
	void set_pos(Position) override;
	bool is_valid_move(Position) const;
    bool is_valid_move(Position pos, int* d) const;
	virtual void your_turn() = 0;
	virtual void end_of_turn();
	int get_turn_pm() const;
	void set_ap(int);

    bool can_attack_with(Position pos, SettingAttack* attack);
    void attack(SettingAttack* attack);
	LifeBar* get_life_bar();
	void get_attacked_by(SettingAttack* attack) override;
	bool is_full_life();
	void try_to_end_turn();
    
private:
	int ap = DEFAULT_AP;
	int turn_ap = DEFAULT_AP;
	int mp = DEFAULT_MP;
	int turn_mp = DEFAULT_MP;
	int move_d;
    Position asked_pos;
    int walk_timer = MOTIONLESS;
    Direction current_dir;
    SettingFighter* setting;
    std::vector<Position> positions;
	LifeBar* life_bar;
};

#endif
