#ifndef SAFE_PLAYER
#define SAFE_PLAYER

class Env;

class Player {

public:
	Player(Env* env);
	~Player();
	Env* get_env();
	void draw();
	
private:
	Env* env;
	
};

#endif
