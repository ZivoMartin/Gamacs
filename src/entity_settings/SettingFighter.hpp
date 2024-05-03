#ifndef SAFE_SETTING_FIGHTER
#define SAFE_SETTING_FIGHTER

#include "Setting.hpp"

class SettingFighter : public Setting {

public:

    SettingFighter(Env* env, Kind kind);
    SettingFighter(Env* env, Kind kind, int lvl);
    ~SettingFighter();
    
    int inc_lvl(int);
    void set_lvl(int);
    
    int get_max_hp() const;
    int get_current_hp() const;
    int get_lvl() const;
    std::vector<SDL_Texture*> sprite_attack() const;
    
private:
    int max_hp;
    int current_hp;
    int lvl = 1;
    
};

#endif
