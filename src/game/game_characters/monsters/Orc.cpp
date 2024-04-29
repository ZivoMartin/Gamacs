#include "Orc.hpp"
#include "../../../Env.hpp"
#define IMG_ORC_PATH "../res/orcSheet.png"
#define ORC_WIDTH 0.12
#define ORC_HEIGHT 0.15

Orc::Orc(Env* env, Position pos) : Monster(env, IMG_ORC_PATH, pos, ORC_WIDTH, ORC_HEIGHT) {}

Orc::~Orc() {}

