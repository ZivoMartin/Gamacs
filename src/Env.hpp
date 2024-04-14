#ifndef ENV_SAFE
#define ENV_SAFE
#include <SDL2/SDL.h>
#include "Player.hpp"
#define BACKGROUND_COLOR 100, 80, 160, 255


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
	
private:
	bool running;
	SDL_Window* w;
	SDL_Renderer* ren;
	Player* player;
};

#endif
