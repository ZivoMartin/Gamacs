#include "Setting.hpp"
#include "../Env.hpp"

Setting::Setting(Env* env, Kind kind) {
    if (kind == NbKind) {
        fprintf(stderr, "NbKind can't be instantiate.");
        exit(1);
    }
    // Todo: do a request to our iris database and get the specific data of the given kind.
    this->kind = kind;
    if (kind == KindOrc) sprite_sheet = OrcSheet;
    else if (kind == KindGolem) sprite_sheet = GolemSheet;
    else sprite_sheet = PLAYER_SHEET;
    this->texture = env->get_text(sprite_sheet);
}

Setting::~Setting() {}

SpriteSheet Setting::get_sprite_sheet() const {
    return sprite_sheet;
}

SDL_Texture* Setting::get_text() {
    return this->texture;
}

Kind Setting::get_kind() const {
    return kind;
}
