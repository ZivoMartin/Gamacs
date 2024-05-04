#include "SettingFighter.hpp"
#include "SettingAttack.hpp"

SettingFighter::SettingFighter(Env* env, Kind kind) : Setting(env, kind) {
    max_hp = 100;
    current_hp = max_hp;
    attacks.push_back(new SettingAttack(DefaultAttack));
}

SettingFighter::SettingFighter(Env* env, Kind kind, int lvl) : Setting(env, kind) {
    puts("Not implemented yet");
    exit(1);
    lvl = lvl;
}

SettingFighter::~SettingFighter() {}

int SettingFighter::get_max_hp() const {
    return max_hp;
}

int SettingFighter::get_current_hp() const {
    return current_hp;
}

int SettingFighter::get_lvl() const {
    return lvl;
}

std::vector<SettingAttack*> SettingFighter::get_attacks() const {
    return attacks;
}


int SettingFighter::inc_lvl(int x) {
    lvl += x;
    return lvl;
}

void SettingFighter::set_lvl(int x) {
    lvl = x;
}

