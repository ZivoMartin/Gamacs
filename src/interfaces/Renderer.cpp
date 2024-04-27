#include "Renderer.hpp"
#include "../Env.hpp"

Renderer::Renderer(Env* env, Lablib* lablib) {
	this->env = env;
}

Env* Renderer::get_env() {
	return env;
}

SDL_Renderer* Renderer::get_ren() {
	return get_env()->get_ren();
}

SDL_Window* Renderer::get_win() {
	return get_env()->get_win();
}

bool Renderer::is_active(SDL_Keycode c) {
	return get_env()->is_active(c);
}

Lablib* Renderer::get_lablib() {
	return get_env()->get_lablib();
}
