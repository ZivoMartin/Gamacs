#include "GamePlayer.hpp"
#include "../../Env.hpp"

#define PLAYER_WIDTH 0.07
#define PLAYER_HEIGHT 0.1
#define BASE_PLAYER_POS {17, 20}

GamePlayer::GamePlayer(Env* env) : Player(env), Movable(env, PLAYER_SHEET, BASE_PLAYER_POS, PLAYER_WIDTH, PLAYER_HEIGHT) {}

GamePlayer::~GamePlayer() {}

void GamePlayer::action() {
    draw();
}


void GamePlayer::draw() {
	int x, y;
	SDL_GetWindowSize(get_env()->get_win(), &x, &y);
	Movable::draw(x/2, y/2);
}

void GamePlayer::collide(MapEntity* entity) {
	if (entity->get_can_interact_with_player()) 
		entity_around.push_back(entity);
	entity->collide(this);
}

void GamePlayer::collide(Monster* monster) {}

void GamePlayer::collide(Pnj* pnj) {}

void GamePlayer::interact() {
	if (entity_around.size() > 0)
		entity_around[0]->interact_with_player();
	entity_around.clear();
}


