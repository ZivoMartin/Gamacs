#ifndef SAFE_ATTACK_SETTING
#define SAFE_ATTACK_SETTING

#include "../include/global_include.hpp"


class SettingAttack {

public:
    SettingAttack(AttackType attack);
    int get_damage() const;
    int get_range() const;
    AttackType get_type() const;
	int get_cost() const;
	void set_cost(int);
	
private:
    int damage;
    int range;
    AttackType type;
	int cost;
};


#endif
