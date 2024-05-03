#ifndef SAFE_MOVABLE_FIGHTER_INT
#define SAFE_MOVABLE_FIGHTER_INT

#include "../sprites/Movable.hpp"

class SettingFighter;

class MovableFighter : public Movable {

public:
    MovableFighter(Env* env, Kind kind, float fx, float fy);
    MovableFighter(Env* env, SettingFighter* setting, float w, float h);
    SettingFighter* get_setting_fighter() const;
    SettingAttack* get_attack(AttackType attack) const;
private:
    SettingFighter* setting;
    
};


#endif
