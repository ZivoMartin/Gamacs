#include "Golem.hpp"

#define IMG_GOLEM_PATH "../res/golem.png"

Golem::Golem(Env* env) : Movable(env, IMG_GOLEM_PATH) {}

Golem::~Golem() {}
