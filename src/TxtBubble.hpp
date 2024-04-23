#ifndef SAFE_TXT_BUBBLE
#define SAFE_TXT_BUBBLE

#include "movables/Sprite.hpp"

class TxtBubble : public Sprite {

public:
	TxtBubble(Env* env, const char* txt, SDL_Point p);
	~TxtBubble();
	void update() override;
	
};

#endif
