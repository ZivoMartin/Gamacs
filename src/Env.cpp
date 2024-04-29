#include "game/MainGame.hpp"
#include "main_menu/MainMenu.hpp"
#include "battle/MainBattle.hpp"
#include "Env.hpp"
#include "game/game_characters/GamePlayer.hpp"
#include "game/game_characters/monsters/Monster.hpp"


Env::Env() {
	cc(SDL_Init(SDL_INIT_VIDEO));
    cc(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &this->w, &this->ren));
	running = false;
	player = new GamePlayer(this);
	lablib = lablib_init(this, get_win(), get_ren(), TotalScene);
	init_renderers();
}

Env::~Env() {
	SDL_DestroyRenderer(get_ren());
	SDL_DestroyWindow(get_win());
    SDL_Quit();
	lablib_destroy(lablib);
	std::for_each(renderers.begin(), renderers.end(),  [](std::pair<Scene*, Renderer*> p) { 
		delete p.second;
	}); 
}

void Env::init_renderers() {
	new MainMenu(this, lablib);
	new MainGame(this, lablib);
	new MainBattle(this, lablib);
}

void Env::set_scene(Scene* scene, Renderer* renderer) {
	renderers[scene] = renderer;
}


Lablib* Env::get_lablib() {
	return lablib;
}


int Env::get_now() {
	return now;
}

SDL_Window* Env::get_win() {
	return this->w;
}

SDL_Renderer* Env::get_ren() {
	return this->ren;
}

void Env::set_battle(MainBattle* battle) {
	this->battle = battle;
}

void Env::set_game(MainGame* game) {
	this->game = game;
}

MainGame* Env::get_game() {
	return game;
}

MainBattle* Env::get_battle() {
	return battle;
}

bool Env::is_running() {
	return this->running;
}


Position Env::game_dim() {
	int x, y;
	SDL_GetWindowSize(get_win(), &x, &y);
	return Position(x, y);
}

#define DELAY 15

void Env::game_loop() {
    this->running =  true;
    while (is_running()) {
        handdle_events();
		lablib_render(lablib);
		renderers[lablib_get_current_scene(lablib)]->render();
		SDL_RenderPresent(get_ren());
		SDL_SetRenderDrawColor(get_ren(), BACKGROUND_COLOR);
	   	SDL_RenderClear(get_ren());
		SDL_Delay(DELAY);
		now += 1;
	}
	delete this;
}

void Env::handdle_events() {
	SDL_Event events;
	while (Lablib_PollEvent(lablib, &events)) {
    	switch (events.type) {
			case SDL_QUIT:
				this->running = false;break;
			case SDL_KEYDOWN:
				enable_key(events.key.keysym.sym);break;
			case SDL_KEYUP:
				disable_key(events.key.keysym.sym);break;
		}
	}
}

void Env::enable_key(SDL_Keycode c) {
	events[c] = true;
}

void Env::disable_key(SDL_Keycode c) {
	events[c] = false;
}

bool Env::is_active(SDL_Keycode c) {
	return events[c];
}



int Env::win_width() {
	int w, h;
	SDL_GetWindowSize(get_win(), &w, &h);
	return w;
}

int Env::win_height() {
	int w, h;
	SDL_GetWindowSize(get_win(), &w, &h);
	return h;
}


void Env::go_game() {
	lablib_change_scene(lablib, Game);
}

void Env::go_battle(Monster* monster) {
	lablib_change_scene(lablib, Battle);
}

GamePlayer* Env::get_player() {
	return this->player;
}
