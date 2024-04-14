#include "Env.hpp"

void* cp(void* p) {
	if (!cp) {
		fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
		exit(1);
	}
	return p;
}

void cc(int c) {
	if (c < 0) {
		fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
		exit(1);
	}
}

Env::Env() {
	cc(SDL_Init(SDL_INIT_VIDEO));
    cc(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &this->w, &this->ren));
	init_regular_actions();
	running = false;
	map = new Map(this);
	this->player = new Player(this);
}

Env::~Env() {
	SDL_DestroyRenderer(get_ren());
	SDL_DestroyWindow(get_win());
    SDL_Quit();
	for (auto &golem : golems) delete golem;
	for (auto &act : regular_actions) delete act;
	delete player;
	delete map;
}

int Env::get_now() {
	return now;
}

#define GOLEM_SPAWN_CD 200

void Env::init_regular_actions() {}

void Env::place_golem() {
	
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

void Env::spawn_golem() {
	golems.push_back(new Golem(this, {0.0, 0.5}));
}

#define DELAY 15

void Env::game_loop() {
    this->running =  true;
    while (is_running()) {
        handdle_events();
		handdle_keypress();
		move_golems();
		test_regular_actions();
		render();
		SDL_Delay(DELAY);
		now += 1;
	}
	delete this;
}

void Env::move_golems() {
	for (auto &golem : golems) golem->action();
}

void Env::render() {
	map->draw();
	get_player()->draw();
	SDL_RenderPresent(get_ren());
	SDL_SetRenderDrawColor(get_ren(), BACKGROUND_COLOR);
	SDL_RenderClear(get_ren());
}

void Env::handdle_events() {
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
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
	if (c < MAX_KEYCODE) events[c] = true;
}

void Env::disable_key(SDL_Keycode c) {
	if (c < MAX_KEYCODE) events[c] = false;
}

bool Env::is_active(SDL_Keycode c) {
	return events[c];
}

void Env::handdle_keypress() {
	int dx = 0, dy = 0;
	int speed = get_player()->get_speed();
	Player* player = get_player();
	if (is_active(SDLK_z)) player->move(0, -speed);
	if (is_active(SDLK_s)) player->move(0, speed);
	if (is_active(SDLK_q)) player->move(-speed, 0);
	if (is_active(SDLK_d)) player->move(speed, 0);
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
