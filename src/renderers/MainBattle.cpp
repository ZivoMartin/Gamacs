#include "MainBattle.hpp"
#include "../Env.hpp"

MainBattle::MainBattle(Env* env, Lablib* lablib) : Renderer(env, lablib) {
	env->set_battle(this);
	init_lablib(lablib);
}

MainBattle::~MainBattle() {}

void MainBattle::render() {}

void MainBattle::handdle_keypress() {}

void display_board(Button* grid) {
	default_display_button(grid);
	Env* env = (Env*) button_get_env(grid);
	int tileSize = BATTLE_TILE_SIZE;
	SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(env->get_lablib()), "", lablib_create_color(0, 0, 0, 255));
	SDL_Texture* text = SDL_CreateTextureFromSurface(env->get_ren(), surf);
	SDL_FreeSurface(surf);
	for(int i = 0; i < BATTLE_WIDTH; i++){
		for(int j = 0; j < BATTLE_HEIGHT; j++){
			SDL_Rect r = lablib_init_rect(i*tileSize, j*tileSize, tileSize);
			SDL_FillRect(NULL, &r);
			SDL_RenderCopy(env->get_ren(), text, NULL, &r);
		}
	} 
}

#define NB_BUTTON 1
void MainBattle::init_lablib(Lablib* lablib) {
	Scene* battle = create_scene(lablib, NB_BUTTON);
	Button* grid = scene_add_button(battle, 0, 0, 1, 1, "test", NULL);
	button_set_display(grid, &display_board);
	button_change_texture(grid, "../res/battle_bg.png");
	get_env()->set_scene(battle, this);
}
