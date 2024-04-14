#include "Golem.hpp"

#define IMG_GOLEM_PATH "../res/golem.png"

Golem::Golem(Env* env, SDL_FPoint pos) : Movable(env, IMG_GOLEM_PATH, pos) {}

Golem::~Golem() {}

void Golem::action() {
	this->move(10, 0);
	this->draw();
}
