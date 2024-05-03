#ifndef SAFE_SETTING
#define SAFE_SETTING

#include "../include/global_include.hpp"

class Env;

class Setting {

public:

    Setting(Env* env, Kind kind);
    ~Setting();
    
    Kind get_kind() const;
    SDL_Texture* get_text();
    
private:
    Kind kind;
    SDL_Texture* texture;
    
};







#endif
