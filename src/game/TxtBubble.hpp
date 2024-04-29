#ifndef SAFE_TXT_BUBBLE
#define SAFE_TXT_BUBBLE

#include "../sprites/Static.hpp"
#include "game_characters/MapEntity.hpp"
class TxtBubble : public Static, public MapEntity {

public:
	TxtBubble(Env* env, const char* txt, Position pos);
	~TxtBubble();
	void update() override;
	
};

#endif
