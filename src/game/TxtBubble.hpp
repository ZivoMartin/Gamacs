#ifndef SAFE_TXT_BUBBLE
#define SAFE_TXT_BUBBLE

#include "../sprites/Static.hpp"

class TxtBubble : public Static {

public:
	TxtBubble(Env* env, const char* txt, Position p);
	~TxtBubble();
	void update() override;
	
};

#endif
