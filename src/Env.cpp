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
    cc(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &this->w, &this->ren));
	running = false;
	this->player = new Player(this);
}

Env::~Env() {
	SDL_DestroyRenderer(get_ren());
	SDL_DestroyWindow(get_win());
    SDL_Quit();
	delete get_player();
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

void Env::game_loop() {
    this->running =  true;
    while (is_running()) {
        handdle_events();
		render();
	}
	delete this;
}

void Env::render() {
	SDL_SetRenderDrawColor(get_ren(), BACKGROUND_COLOR);
	SDL_RenderClear(get_ren());
	SDL_RenderPresent(get_ren());
	get_player()->draw();
}

void Env::handdle_events() {
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
    	switch (events.type) {
			case SDL_QUIT:
				this->running = false;
				break;
		}
	}
}

Player* Env::get_player() {
	return this->player;
}
