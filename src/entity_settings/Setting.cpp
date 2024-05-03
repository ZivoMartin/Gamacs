#include "Setting.hpp"
#include "../Env.hpp"

Setting::Setting(Env* env, Kind kind) {
    if (kind == NbKind) {
        fprintf(stderr, "NbKind can't be instantiate.");
        exit(1);
    }
    // Todo: do a request to our iris database and get the specific data of the given kind.
    this->kind = kind;
    this->texture = env->get_text(kind);
}

Setting::~Setting() {}

SDL_Texture* Setting::get_text() {
    return this->texture;
}

Kind Setting::get_kind() const {
    return kind;
}
