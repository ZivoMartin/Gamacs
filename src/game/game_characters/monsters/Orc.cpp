#include "Orc.hpp"
#include "../../../Env.hpp"
#define ORC_WIDTH 0.12
#define ORC_HEIGHT 0.15

Orc::Orc(Env* env, Position pos) : Monster(env, OrcSheet, pos, ORC_WIDTH, ORC_HEIGHT) {}

Orc::~Orc() {}

