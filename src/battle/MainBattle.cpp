#include "MainBattle.hpp"
#include "../Env.hpp"
#include "../sprites/Sprite.hpp"
#include "../interfaces/Player.hpp"
#include "powns/PownPlayer.hpp"
#include "powns/PownMonster.hpp"
#include "powns/Pown.hpp"
#include "powns/PownMovable.hpp"
#include "BattleSquare.hpp"

#define SQUARE_COLOR 100, 200, 100, 100

MainBattle::MainBattle(Env* env, Lablib* lablib) : Renderer(env, lablib) {
	env->set_battle(this);
	SDL_Surface* surf = IMG_Load(BATTLE_SQUARE_PATH);
	square_text = SDL_CreateTextureFromSurface(env->get_ren(), surf);
	SDL_FreeSurface(surf);
	init_lablib(lablib);	
	for(int i = 0; i < BATTLE_WIDTH; i++)
		for(int j = 0; j < BATTLE_HEIGHT; j++) 
			board[i][j] = new BattleSquare(this, Position(i, j));
    player = new PownPlayer(env);
	powns.push_back(player);
	set((Pown*) player);
}

MainBattle::~MainBattle() {
	for(int i = 0; i < BATTLE_WIDTH; i++)
		for(int j = 0; j < BATTLE_HEIGHT; j++) 
			delete board[i][j];
	SDL_DestroyTexture(square_text);
}

BattleSquare* MainBattle::get_square(Position pos) const {
	return board[pos.x()][pos.y()];
}

void MainBattle::render() {
	int w = win_width(), h = win_height();
	tile_size = std::min(w, h) * BATTLE_TILE_SIZE;
	decal_w = w*0.5 - (tile_size*BATTLE_WIDTH)/2;
	decal_h = GRID_DECAL_TOP*h;
	for(int i = 0; i < BATTLE_WIDTH; i++)
		for(int j = 0; j < BATTLE_HEIGHT; j++) 
			if (!is_empty_square(i, j)) get(i, j)->update();
}

void MainBattle::handdle_keypress() {}

SDL_Texture* MainBattle::get_square_txt() const {
	return square_text;
}

bool MainBattle::is_valid_pos(Position pos) const {
    return pos.x() >= 0 && pos.y() >= 0 && pos.x() < BATTLE_WIDTH && pos.y() < BATTLE_HEIGHT;
}

int MainBattle::get_dw() const {
	return decal_w;
}

int MainBattle::get_dh() const {
	return decal_h;
}

int MainBattle::get_ts() const {
	return tile_size;
}

void MainBattle::set(Pown* pown) {
	get_square(pown->get_pos())->set_pown(pown);
}

Pown* MainBattle::get(int i, int j) const {
	return get(Position(i, j));
}

Pown* MainBattle::get(Position pos) const {
	return get_square(pos)->get_pown();
}

void b_display_board(Button* grid) {
	MainBattle* battle = ((Env*) button_get_env(grid))->get_battle();
	int tile_size = battle->get_ts();
	button_set_height(grid, BATTLE_HEIGHT*tile_size);
	button_set_width(grid, BATTLE_WIDTH*tile_size);
	Env* env = (Env*) button_get_env(grid);
	button_set_rx(grid, ((float) battle->get_dw())/button_get_win_w(grid));
	env->get_battle()->display_board();
}


bool MainBattle::is_empty_square(Position pos) const {
	return get_square(pos)->is_empty();
}

bool MainBattle::is_empty_square(int i, int j) const {
	return is_empty_square(Position(i, j));
}

#define EXTRACT_COLOR(c) c.r, c.g, c.b, c.a

void MainBattle::display_board() {
	for(int i = 0; i < BATTLE_WIDTH; i++){
		for(int j = 0; j < BATTLE_HEIGHT; j++){
            SDL_SetRenderDrawColor(get_ren(), EXTRACT_COLOR(get_square(Position(i, j))->get_color()));
			SDL_Rect r = lablib_init_rect(i*tile_size + decal_w, j*tile_size + decal_h, tile_size);
            SDL_RenderDrawRect(get_ren(), &r);         
            SDL_RenderFillRect(get_ren(), &r);
		}
	} 
}

void MainBattle::click_on_grid() {
	Lablib* lablib = get_lablib();
	SDL_Point p = lablib_get_last_coordinate(lablib);
	int w = win_width(), h = win_height();
    Position pos = Position((p.x - decal_w)/tile_size, (p.y - decal_h)/tile_size);
    get_square(pos)->clicked();
    get_player()->click_on_grid(pos);
}

void MainBattle::click_on_empty_square(Position p) {}

MainBattle* extract_battle(Button* b) {
	return ((Env*) button_get_env(b))->get_battle();
}

void move_click(Button* b) {
	MainBattle* battle = extract_battle(b);
	if (battle->is_player_turn())battle->set_select(Move);
}

void cancel_click(Button* b) {
	MainBattle* battle = extract_battle(b);
	battle->set_select(Nothing);
}

void attack_click(Button* b) {
	MainBattle* battle = extract_battle(b);
	if (battle->is_player_turn()) {
		battle->set_select(Attack);
		battle->set_selected_attack(battle->get_player()->get_attack(DefaultAttack));
	}
}

void MainBattle::set_empty(Position pos) {
	get_square(pos)->set_empty();
}

void MainBattle::set_selected_attack(SettingAttack* attack) {
	selected_attack = attack;
}

void MainBattle::set_player_turn() {
	player_turn = true;
}

void MainBattle::disable_player_turn() {
	player_turn = false;
}

bool MainBattle::is_player_turn() const {
	return player_turn;
}

void MainBattle::set_select(Selected select) {
	this->select = select;
}

#define NB_BUTTON 4
#define B_SIZE 0.1
#define BUTTON_SIZE B_SIZE, B_SIZE
#define BUTTON_Y 1-B_SIZE
void MainBattle::init_lablib(Lablib* lablib) {
	Scene* battle = create_scene(lablib, NB_BUTTON);
	set_scene_background(lablib, battle, BATTLE_BG);
	Button* grid = scene_add_button(battle, 0.5, GRID_DECAL_TOP, 0, 0, "", &b_click_on_grid);
	button_set_display(grid, &b_display_board);
	scene_add_button(battle, 0.3, BUTTON_Y, BUTTON_SIZE, "move",  &move_click);
    scene_add_button(battle, 0.5, BUTTON_Y, BUTTON_SIZE, "cancel", &cancel_click);
	scene_add_button(battle, 0.7, BUTTON_Y, BUTTON_SIZE, "attack", &attack_click);
	get_env()->set_scene(battle, this);
}


void b_click_on_grid(Button* grid) {
	Env* env = (Env*) button_get_env(grid);
	env->get_battle()->click_on_grid();
}

PownPlayer* MainBattle::get_player() const {
    return player;
}

void MainBattle::fight(SettingFighter* setting_monster) {
	PownMovable* monster = new PownMonster(get_env(), setting_monster);
	powns.push_back(monster);
	set(monster);
	player->reset_pos();
	powns[0]->your_turn();
}

Selected MainBattle::get_select() const {
	return select;
}

void MainBattle::end_of_pown_turn() {
	current_pown = (current_pown+1)%powns.size();
	powns[current_pown]->your_turn();
}

SettingAttack* MainBattle::get_selected_attack() {
	return selected_attack;
}
