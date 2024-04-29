#include "TxtBubble.hpp"

#define BUBBLE_HEIGHT 0.2
#define BUBBLE_WIDTH 0.3

TxtBubble::TxtBubble(Env* env, const char* txt, Position pos) : Static(env, txt, BUBBLE_WIDTH, BUBBLE_HEIGHT) {
	set_initial_pos(pos);
}

TxtBubble::~TxtBubble() {}

void TxtBubble::update() {
	Static::update();
	MapEntity::draw();
}
