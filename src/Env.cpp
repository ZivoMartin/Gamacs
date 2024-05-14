#include "game/MainGame.hpp"
#include "main_menu/MainMenu.hpp"
#include "battle/MainBattle.hpp"
#include "Env.hpp"
#include "game/game_characters/monsters/Monster.hpp"
#include "entity_settings/SettingFighter.hpp"
#include "entity_settings/SettingAttack.hpp"
#include "include/sprite_paths.hpp"


extern void iris_new_request(const char* req);
extern void iris_load_file(const char* path);


Env::Env() {
	// std::string path("/home/martin/Travail/Gamacs/Iris/demo.sql");
	// iris_load_file(path.c_str());
	srand(time(NULL));
	cc(SDL_Init(SDL_INIT_VIDEO));
    cc(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN, &this->w, &this->ren));
	running = false;
    init_textures();
    init_attacks();
    player_setting = new SettingFighter(this, PLAYER_KIND);
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
    for (int i = 0; i<NB_SPRITE_PATH; i++) 
        SDL_DestroyTexture(textures[i]);
    
}


SDL_Texture* Env::get_text(Kind i) const {
    if (i == NbKind) {
        fprintf(stderr, "NbKind represents the number of texture not a specific one");
        exit(1);
    }
    return textures[i];
}

SDL_Texture* Env::get_text(AttackType i) const {
    if (i == NbAttack) {
        fprintf(stderr, "NbAttack represents the number of texture not a specific one");
        exit(1);
    }
    return textures[i+NbKind];
}

void Env::init_textures() {
    for (int i = 0; i < NB_SPRITE_PATH; i++) 
        textures[i] = IMG_LoadTexture(get_ren(), sprite_sheet_paths[i]);    
}

void Env::init_attacks() {
    attacks[DefaultAttack] = new SettingAttack(DefaultAttack);
}

SettingAttack* Env::get_attack(AttackType attack) {
    if (attack == NbAttack) {
        fprintf(stderr, "NbAttack isn't an attack\n");
        exit(1);
    }
    return attacks[attack];
}

void Env::init_renderers() {
	new MainMenu(this, lablib);
	new MainGame(this, lablib);
	new MainBattle(this, lablib);
}

void Env::set_scene(Scene* scene, Renderer* renderer) {
	renderers[scene] = renderer;
}


Lablib* Env::get_lablib() const {
	return lablib;
}


int Env::get_now() const {
	return now;
}

SDL_Window* Env::get_win() const {
	return this->w;
}

SDL_Renderer* Env::get_ren() const {
	return this->ren;
}

void Env::set_battle(MainBattle* battle) {
	this->battle = battle;
}

void Env::set_game(MainGame* game) {
	this->game = game;
}

MainGame* Env::get_game() const {
	return game;
}

MainBattle* Env::get_battle() const {
	return battle;
}

bool Env::is_running() const {
	return this->running;
}


Position Env::game_dim() const {
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

int Env::win_width() const {
	int w, h;
	SDL_GetWindowSize(get_win(), &w, &h);
	return w;
}

int Env::win_height() const {
	int w, h;
	SDL_GetWindowSize(get_win(), &w, &h);
	return h;
}

void Env::go_game() {
	lablib_change_scene(lablib, Game);
}

void Env::go_battle(SettingFighter* monster_setting) {
	battle->fight(monster_setting);
	lablib_change_scene(lablib, Battle);
}

SettingFighter* Env::get_player_setting() {
    return player_setting;
}

int Env::random(int min, int max) const {
	return rand() % (max+1) + min;
}
