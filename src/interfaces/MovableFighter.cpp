#include "MovableFighter.hpp"
#include "../entity_settings/SettingFighter.hpp"

MovableFighter::MovableFighter(Env* env, Kind kind, float fx, float fy) : Movable(env, nullptr, fx, fy){
    setting = new SettingFighter(env, kind);
    set_setting(setting);
}

MovableFighter::MovableFighter(Env* env, SettingFighter* setting, float fx, float fy) : Movable(env, setting, fx, fy){
    this->setting = setting;
}

SettingFighter* MovableFighter::get_setting_fighter() const {
    return setting;
}

SettingAttack* MovableFighter::get_attack(AttackType attack_type) {
    for (SettingAttack* set : setting->get_attacks()) 
        if (set->get_type() == attack_type) return set;
    
}
