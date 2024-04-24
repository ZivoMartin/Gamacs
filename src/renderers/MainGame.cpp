#include "../Env.hpp"
#include "../movables/Player.hpp"
#include "../movables/monsters/Orc.hpp"
#include "../view/Map.hpp"
#include "../Pnj.hpp"
#include "../movables/Sprite.hpp"
#include "../TxtBubble.hpp"
#include "MainGame.hpp"

MainGame::MainGame(Env* env, Lablib* lablib) : Renderer(env, lablib) {
	env->set_game(this);
	sprites.push_back(get_player());
	place_monsters();
	init_pnj();
	map = new Map(env);
	init_lablib(lablib);
}


MainGame::~MainGame() {
	for (auto &sprite : sprites) delete sprite;
	delete map;
	delete txt_bubble;
}

Player* MainGame::get_player() {
	return get_env()->get_player();
}

#define NB_ORC 4
void MainGame::place_monsters() {
	SDL_Point orc_positions[NB_ORC] = {{18, 20}, {18, 23}, {18, 15}, {22, 20}};
	for (auto &p : orc_positions) sprites.push_back(new Orc(get_env(), p));				
}

#define NB_PNJ 1
void MainGame::init_pnj() {
	ActionVec vec;
	vec.push_back(std::pair(&MainGame::talk_and_inc, &MainGame::stop_inc_action));
	Pnj* pnj = new Pnj(get_env(), this, "../res/golem.png", {18, 21}, vec);
	pnj->set_dialog("../res/test_dialog.txt");
	sprites.push_back(pnj);
}

void MainGame::render() {
	handdle_keypress();
	map->draw();
	update_sprites();
	if (txt_bubble) txt_bubble->update();
}

void MainGame::handdle_keypress() {
	int dx = 0, dy = 0;
	int speed = get_player()->get_speed();
	Player* player = get_player();
	if (is_active(SDLK_UP)) 	   player->move(Top);
	else if (is_active(SDLK_DOWN)) player->move(Bot);
	else if (is_active(SDLK_LEFT)) player->move(Left);
	else if (is_active(SDLK_RIGHT)) player->move(Right);
	if (is_active(SDLK_a)) player->attack(0);
	else if (is_active(SDLK_z)) player->attack(1);
	else if (is_active(SDLK_e)) player->attack(2);
	else if (is_active(SDLK_f)) player->interact();
	get_player()->move(dx, dy);
}

void MainGame::update_sprites() {
	int last_col = 0;
	for (int i=0; i<sprites.size(); i++) {
		int x1 = sprites[i]->get_pos()->x, y1 = sprites[i]->get_pos()->y;
		int j = last_col;
		while (j < i) {
			int x2 = sprites[j]->get_pos()->x, y2 = sprites[j]->get_pos()->y;
			if (!((y1 <= (sprites[j]->get_height()+y2) && y1 >= y2) || (y2 <= (sprites[i]->get_height()+y1) && y2 >= y1))) last_col = j+1;
			else if ((x1 <= (sprites[j]->get_width()+x2) && x1 >= x2) || (x2 <= (sprites[i]->get_width()+x1) && x2 >= x1)) {
				sprites[i]->collide(sprites[j]);
				sprites[j]->collide(sprites[i]);
}
			j++;
		}
		sprites[i]->update();
		j = i;
		while (j >= 1 &&
			   (sprites[j-1]->get_pos()->y + sprites[j-1]->get_height()) >
			   (sprites[j]->get_pos()->y   + sprites[j]->get_height())) {
			Sprite* tmp = sprites[j];
			sprites[j] = sprites[j-1];
			sprites[--j] = tmp;
		}
	}
}

void MainGame::talk(Pnj* pnj) {
	if (txt_bubble != nullptr) delete txt_bubble;
	SDL_Point* pos = pnj->get_pos();
	txt_bubble = new TxtBubble(get_env(), pnj->get_dialog()->c_str(), {pos->x/PIXEL_TILE_SIZE, pos->y/PIXEL_TILE_SIZE});
}

void MainGame::talk_and_inc(Pnj* pnj) {
	talk(pnj);
	pnj->inc_dialog_index();
}

void MainGame::talk_and_reset(Pnj* pnj) {
	talk(pnj);
	pnj->reset_dialog_index();
}


void MainGame::init_lablib(Lablib* lablib) {
	Scene* game = create_scene(lablib, 0);
	get_env()->set_scene(game, this);
}
