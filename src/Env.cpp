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
	place_golem();
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


#define NB_GOLEM 2
void Env::place_golem() {
	SDL_Point positions[NB_GOLEM] = {{17, 20}, {15, 15}};
	for (auto &p : positions) golems.push_back(new Golem(this, p));				
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

void Env::spawn_golem() {}

SDL_Point Env::game_dim() {
	SDL_Point res;
	SDL_GetWindowSize(get_win(), &res.x, &res.y);
	return res;
}

int Env::compute_ts() {
	int width = win_width(), height = win_height();
	return std::max(width/VISION_RANGE, height/VISION_RANGE);
}

SDL_Point Env::convert_coord_to_pixels(SDL_Point p) {
	Player* player = get_player();
	int tile_size = compute_ts();
	int x = player->get_pos()->x;   // Local coordonate of the player
	int y = player->get_pos()->y;
	SDL_Point res = {VISION_RANGE*TILE_SIZE + (p.x-x), VISION_RANGE*TILE_SIZE + (p.y-y)};
	res = {(res.x*tile_size)/TILE_SIZE, (res.y*tile_size)/TILE_SIZE};
	return res;
}

#define DELAY 15

void Env::game_loop() {
    this->running =  true;
    while (is_running()) {
        handdle_events();
		handdle_keypress();
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
	move_golems();
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
