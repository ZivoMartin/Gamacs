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

typedef enum Selected {
	Move,
	Nothing,
	Attack,
	NbSelect
} Selected;


class Pown;
class PownPlayer;
class PownMovable;

class MainBattle : public Renderer {

public:
	MainBattle(Env* env, Lablib* lablib);
	~MainBattle();
	void init_lablib(Lablib* lablib) override;
	void render() override;
	void handdle_keypress() override;
	void fight(SpriteSheet monster);
	
	SDL_Texture* get_square_txt() const;
	int get_dw() const;
	int get_dh() const;
	int get_ts() const;

    void click_on_empty_square(Position p);
	void display_board();
	void click_on_grid();

	void set(Pown* p);
    void set_empty(int i, int j);
	void set_empty(Position pos);
	bool is_empty_square(Position pos) const;
	bool is_empty_square(int i, int j) const;
	Pown* get(int i, int j) const;
    Pown* get(Position p) const;
    PownPlayer* get_player() const;
	Selected get_select() const;
	void set_select(Selected select);
	void end_of_pown_turn();

	bool is_player_turn() const;
	void set_player_turn();
	void disable_player_turn();
    bool is_valid_pos(Position pos) const;
    SDL_Color get_current_square_color(Position pos);
	
private:
	SDL_Texture* square_text;
	int decal_w, decal_h, tile_size;
    PownPlayer* player;
	std::vector<PownMovable*> powns;
	Pown* board[BATTLE_WIDTH][BATTLE_HEIGHT];
	Selected select = Nothing;
	int current_pown = 0;
	bool player_turn = false;
};

void b_display_board(Button* grid);

void b_click_on_grid(Button* grid);

#endif

