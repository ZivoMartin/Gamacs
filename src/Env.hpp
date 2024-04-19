#ifndef ENV_SAFE
#define ENV_SAFE

#include "view/Map.hpp"
#include "movables/Player.hpp"
#include "movables/monsters/Monster.hpp"
#include "movables/monsters/Orc.hpp"
#include "RegularAction.hpp"

#include <vector>
#define BACKGROUND_COLOR 100, 80, 160, 255

#define MAX_KEYCODE 322


class Env {

public:
	Env();
	~Env();
	void game_loop();
	SDL_Window* get_win();
	SDL_Renderer* get_ren();
	bool is_running();
	void handdle_events();
	void render();
	Player* get_player();
	void handdle_keypress();
	bool is_active(SDL_Keycode c);
	void enable_key(SDL_Keycode c);
	void disable_key(SDL_Keycode c);
	void move_monsters();
	int win_width();
	int win_height();
	void init_regular_actions();
	void test_regular_actions();
	int get_now();
	void place_monsters();
	SDL_Point convert_coord_to_pixels(SDL_Point c);
	SDL_Point game_dim();
	int compute_ts();
	bool player_is_running();
	
private:
	bool running;
	SDL_Window* w;
	SDL_Renderer* ren;
	Player* player;
	bool events[MAX_KEYCODE];
	std::vector<Monster*> monsters;
	std::vector<RegularAction*> regular_actions;
	Map* map;
	long long unsigned int now = 0;
};

#endif
