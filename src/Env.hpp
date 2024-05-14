#ifndef ENV_SAFE
#define ENV_SAFE

#include "include/global_include.hpp"

#define BACKGROUND_COLOR 100, 80, 160, 255

#define MAX_KEYCODE 322

class Renderer;
class SettingFighter;
class MainBattle;
class MainGame;
class SettingAttack;

class Env {

public:
	Env();
	~Env();

	void init_renderers();
    void init_attacks();
	void game_loop();
	SDL_Window* get_win() const;
	SDL_Renderer* get_ren() const;
    void init_textures();
	bool is_running() const;
	void handdle_events();
	void render_menu();
	bool is_active(SDL_Keycode c);
	void enable_key(SDL_Keycode c);
	void disable_key(SDL_Keycode c);
	
	Lablib* get_lablib() const;
    SDL_Texture* get_text(Kind i) const;
    SDL_Texture* get_text(AttackType i) const;
	int win_width() const;
	int win_height() const;
	int get_now() const;
	Position game_dim() const;
	void go_battle(SettingFighter* monster_setting);
	void go_game();
	void set_scene(Scene* scene, Renderer* renderer);
	MainBattle* get_battle() const;
	MainGame* get_game() const;
	void set_battle(MainBattle* battle);
	void set_game(MainGame* game);
	void talk(Pnj* pnj);
	void talk_and_inc(Pnj* pnj);
	void talk_and_reset(Pnj* pnj);
	int random(int min, int max) const;
    SettingAttack* get_attack(AttackType attack);
    SettingFighter* get_player_setting();
    
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

    SettingAttack* attacks[NbAttack];
    SDL_Texture* textures[4];
    SettingFighter* player_setting;
};


#endif
