#include "MainMenu.hpp"
#include "../Env.hpp"

void go_game(Button* b) {
	Env* env = (Env*) button_get_env(b);
	env->go_game();
}

MainMenu::MainMenu(Env* env, Lablib* lablib) : Renderer(env, lablib) {
	init_lablib(lablib);
}

MainMenu::~MainMenu() {}
void MainMenu::render() {}
void MainMenu::handdle_keypress() {}

void MainMenu::init_lablib(Lablib* lablib) {
	Scene* menu = create_scene(lablib, 1);
	scene_add_button(menu, 0.4, 0.4, 0.2, 0.2, "Start", go_game);
	set_scene_background(lablib, menu, MENU_BG);
	get_env()->set_scene(menu, this);
}
