#include "Env.hpp"
#include "movables/Player.hpp"
#include "movables/monsters/Orc.hpp"
#include "view/Map.hpp"
#include "view/Sprite.hpp"
#include "RegularAction.hpp"

enum SceneIndex {
	Menu,
	Game
};

void go_game(Button* b) {
	lablib_change_scene(button_lablib(b), Game);
}


Env::Env() {
	cc(SDL_Init(SDL_INIT_VIDEO));
    cc(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &this->w, &this->ren));
	init_regular_actions();
	place_monsters();
	running = false;
	this->init_lablib();
	map = new Map(this);
	this->player = new Player(this);
	sprites.push_back(player);
}

Env::~Env() {
	SDL_DestroyRenderer(get_ren());
	SDL_DestroyWindow(get_win());
    SDL_Quit();
	for (auto &movable : sprites) delete movable;
	for (auto &act : regular_actions) delete act;
	delete map;
	lablib_destroy(lablib);
}

void Env::init_lablib() {
	lablib = lablib_init(get_win(), get_ren(), 2);
	Scene* menu = create_scene(lablib, 1);
	scene_add_button(menu, 0.2, 0.2, 0.2, 0.2, "Start", false, go_game);
	render_function.insert(std::pair(menu, &Env::render_menu));
	Scene* game = create_scene(lablib, 1);
	scene_add_button(game, 0.4, 0.4, 0.2, 0.2, "OK", false, NULL);
	render_function.insert(std::pair(game, &Env::render_game));
}

int Env::get_now() {
	return now;
}

void Env::init_regular_actions() {}

#define NB_ORC 1
void Env::place_monsters() {
	SDL_Point orc_positions[NB_ORC] = {{18, 20}};
	for (auto &p : orc_positions) sprites.push_back(new Orc(this, p));				
}

void Env::test_regular_actions() {
	for (auto &act : regular_actions) act->try_do();
}

SDL_Window* Env::get_win() {
	return this->w;
}

SDL_Renderer* Env::get_ren() {
	return this->ren;
}

bool Env::is_running() {
	return this->running;
}


SDL_Point Env::game_dim() {
	SDL_Point res;
	SDL_GetWindowSize(get_win(), &res.x, &res.y);
	return res;
}

// Compute the pixels coord of the point p, depends of the player position.
SDL_Point Env::convert_coord_to_pixels(SDL_Point p) {
	Player* player = get_player();
	int w, h;
	SDL_GetWindowSize(get_win(), &w, &h);
	return {
		w/2 - (player->get_pos()->x - p.x),
		h/2 - (player->get_pos()->y - p.y)
	};
}

#define DELAY 15

void Env::game_loop() {
    this->running =  true;
    while (is_running()) {
        handdle_events();
		lablib_render(lablib);
		(this->*render_function[lablib_get_current_scene(lablib)])();
		SDL_RenderPresent(get_ren());
		SDL_SetRenderDrawColor(get_ren(), BACKGROUND_COLOR);
	   	SDL_RenderClear(get_ren());
		SDL_Delay(DELAY);
		now += 1;
	}
	delete this;
}

void Env::update_sprites() {
	for (int i=0; i<sprites.size(); i++) {
		sprites[i]->update();
		int j = i;
		while (j >= 1 &&
			   (sprites[j-1]->get_pos()->y + sprites[j-1]->get_height()) >
			   (sprites[j]->get_pos()->y   + sprites[j]->get_height())) {
			Sprite* tmp = sprites[j];
			sprites[j] = sprites[j-1];
			sprites[--j] = tmp;
		}
	}
}

void Env::render_game() {
	handdle_keypress_game();
	map->draw();
	update_sprites();
}


void Env::render_menu() {
	// Todo: rien pour l'instant
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

bool Env::player_is_running() {
	return is_active(0);
}

void Env::handdle_keypress_game() {
	int dx = 0, dy = 0;
	int speed = get_player()->get_speed();
	Player* player = get_player();
	if (is_active(SDLK_UP)) player->move(Top);
	else if (is_active(SDLK_DOWN)) player->move(Bot);
	else if (is_active(SDLK_LEFT)) player->move(Left);
	else if (is_active(SDLK_RIGHT)) player->move(Right);
	if (is_active(SDLK_a)) player->attack(0);
	else if (is_active(SDLK_z)) player->attack(1);
	else if (is_active(SDLK_e)) player->attack(2);
	else if (is_active(SDLK_f)) player->interact();
	get_player()->move(dx, dy);
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

Player* Env::get_player() {
	return this->player;
}
