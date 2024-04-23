#ifndef ENV_SAFE
#define ENV_SAFE

#include "include.hpp"

#define BACKGROUND_COLOR 100, 80, 160, 255

#define MAX_KEYCODE 322

class Player;
class Sprite;
class RegularAction;
class Map;
class TxtBubble;

class Env {

public:
	Env();
	~Env();
	void init_lablib();
	void init_pnj();
	void game_loop();
	SDL_Window* get_win();
	SDL_Renderer* get_ren();
	bool is_running();
	void handdle_events();
	void render_game();
	void render_menu();
	Player* get_player();
	void handdle_keypress_game();
	bool is_active(SDL_Keycode c);
	void enable_key(SDL_Keycode c);
	void disable_key(SDL_Keycode c);
	void update_sprites();
	Lablib* get_lablib();
	int win_width();
	int win_height();
	void init_regular_actions();
	void test_regular_actions();
	int get_now();
	void place_monsters();
	SDL_Point convert_coord_to_pixels(SDL_Point c);
	SDL_Point game_dim();
	bool player_is_running();

	bool stop_inc_action() {return false;}
	void talk(Pnj* pnj);
	void talk_and_inc(Pnj* pnj);
	void talk_and_reset(Pnj* pnj);
	
private:
	Lablib* lablib;
	bool running;
	SDL_Window* w;
	SDL_Renderer* ren;
	Player* player;
	std::vector<Sprite*> sprites;
	std::vector<RegularAction*> regular_actions;
	std::map<Scene*, void (Env::*)()> render_function;
	std::map<SDL_Keycode, bool> events;
	Map* map;
	long long unsigned int now = 0;
	TxtBubble* txt_bubble = nullptr;
};

#endif
