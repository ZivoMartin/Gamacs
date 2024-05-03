#include "SettingAttack.hpp"

SettingAttack::SettingAttack(AttackType) {
    damage = 3;
    range = 3;
}

int SettingAttack::get_range() const {
    return range;
}

int SettingAttack::get_damage() const {
    return damage;
}

AttackType SettingAttack::get_type() const {
    return type;
}
