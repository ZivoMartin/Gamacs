#ifndef SAFE_SETTING
#define SAFE_SETTING

#include "../include/global_include.hpp"

class Env;

class Setting {

public:

    Setting(Env* env, Kind kind);
    ~Setting();
    
    SpriteSheet get_sprite_sheet() const;
    Kind get_kind() const;
    SDL_Texture* get_text();
    
private:
    SpriteSheet sprite_sheet;
    Kind kind;
    SDL_Texture* texture;
    
};







#endif
