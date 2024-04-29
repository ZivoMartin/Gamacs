#ifndef ENV_SAFE
#define ENV_SAFE

#include "include/global_include.hpp"

#define BACKGROUND_COLOR 100, 80, 160, 255

#define MAX_KEYCODE 322

class Renderer;
class Monster;
class MainBattle;
class MainGame;

class Env {

public:
	Env();
	~Env();

	void init_renderers();
	void game_loop();
	SDL_Window* get_win();
	SDL_Renderer* get_ren();
    void init_textures();
	bool is_running();
	void handdle_events();
	void render_menu();
	bool is_active(SDL_Keycode c);
	void enable_key(SDL_Keycode c);
	void disable_key(SDL_Keycode c);
	
	Lablib* get_lablib();
    SDL_Texture* get_text(SpriteSheet i);
	int win_width();
	int win_height();
	int get_now();
	Position game_dim();
	void go_battle(Monster* monster);
	void go_game();
	void set_scene(Scene* scene, Renderer* renderer);
	MainBattle* get_battle();
	MainGame* get_game();
	void set_battle(MainBattle* battle);
	void set_game(MainGame* game);
	void talk(Pnj* pnj);
	void talk_and_inc(Pnj* pnj);
	void talk_and_reset(Pnj* pnj);
	
private:
	Lablib* lablib;
	bool running;
	SDL_Window* w;
	SDL_Renderer* ren;
	MainBattle* battle;
	MainGame* game;
	std::map<Scene*, Renderer*> renderers;
	std::map<SDL_Keycode, bool> events;
	long long unsigned int now = 0;

    SDL_Texture* textures[NbSpriteSheet];
};

#endif
