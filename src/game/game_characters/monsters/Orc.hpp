#ifndef SAFE_ORC
#define SAFE_ORC

#include "Monster.hpp"

class Env;

class Orc : public Monster {

public:
	Orc(Env* env, Position pos);
	~Orc();
};

#endif
