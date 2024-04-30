#ifndef SAFE_BATTLE
#define SAFE_BATTLE

#include "../interfaces/Renderer.hpp"
#include "../include/global_include.hpp"

#define BATTLE_SQUARE_PATH "res/battle_square.png"
#define BATTLE_BG "res/battle_bg.png"
#define BATTLE_TILE_SIZE 0.12
#define BATTLE_WIDTH 10
#define BATTLE_HEIGHT 7
#define GRID_DECAL_TOP 0.05
#define BASE_PLAYER_X 4
#define BASE_PLAYER_Y 5

class Pown;

class MainBattle : public Renderer {

public:
	MainBattle(Env* env, Lablib* lablib);
	~MainBattle();
	void init_lablib(Lablib* lablib) override;
	void render() override;
	void handdle_keypress() override;
	SDL_Texture* get_square_txt();
	int get_dw();
	int get_dh();
	int get_ts();

    void click_on_empty_square(Position p);
	void display_board();
	void click_on_grid();

	void set(Pown* p);
    void set_empty(int i, int j);
	Pown* get(int i, int j);
	
private:
	SDL_Texture* square_text;
	int decal_w, decal_h, tile_size;
	Pown* board[BATTLE_WIDTH][BATTLE_HEIGHT];
};

void b_display_board(Button* grid);

void b_click_on_grid(Button* grid);

#endif

