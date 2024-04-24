#ifndef SAFE_BATTLE
#define SAFE_BATTLE

#include "Renderer.hpp"
#include "../include.hpp"

#define BATTLE_TILE_SIZE 40
#define BATTLE_WIDTH 10
#define BATTLE_HEIGHT 5

class Sprite;
class Player;

class MainBattle : public Renderer {

public:
	MainBattle(Env* env, Lablib* lablib);
	~MainBattle();
	void init_lablib(Lablib* lablib) override;
	void render() override;
	void handdle_keypress() override;
	
private:
	
};

void display_board(Button* b);


#endif

