#ifndef ENV_SAFE
#define ENV_SAFE

#include "include.hpp"
#include "movables/Player.hpp"
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
	
private:
	bool running;
	SDL_Window* w;
	SDL_Renderer* ren;
	Player* player;
	bool events[MAX_KEYCODE];
};

#endif
