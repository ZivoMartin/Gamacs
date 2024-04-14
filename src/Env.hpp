#ifndef ENV_SAFE
#define ENV_SAFE

#include "include.hpp"
#include "movables/Golem.hpp"
#include "movables/Player.hpp"
#include "RegularAction.hpp"
#include "view/Map.hpp"
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
	void move_golems();
	int win_width();
	int win_height();
	void spawn_golem();
	void init_regular_actions();
	void test_regular_actions();
	int get_now();
	void place_golem();
	
private:
	bool running;
	SDL_Window* w;
	SDL_Renderer* ren;
	Player* player;
	bool events[MAX_KEYCODE];
	std::vector<Golem*> golems;
	std::vector<RegularAction*> regular_actions;
	Map* map;
	long long unsigned int now = 0;
};

#endif
