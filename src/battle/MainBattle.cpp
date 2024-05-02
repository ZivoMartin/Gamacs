#include "MainBattle.hpp"
#include "../Env.hpp"
#include "../sprites/Sprite.hpp"
#include "../interfaces/Player.hpp"
#include "PownPlayer.hpp"
#include "PownMonster.hpp"
#include "Pown.hpp"
#include "PownMovable.hpp"

#define SQUARE_COLOR 100, 200, 100, 100

MainBattle::MainBattle(Env* env, Lablib* lablib) : Renderer(env, lablib) {
	env->set_battle(this);
	SDL_Surface* surf = IMG_Load(BATTLE_SQUARE_PATH);
	square_text = SDL_CreateTextureFromSurface(env->get_ren(), surf);
	SDL_FreeSurface(surf);
	init_lablib(lablib);
	
	for(int i = 0; i < BATTLE_WIDTH; i++)
		for(int j = 0; j < BATTLE_HEIGHT; j++) 
			set_empty(i, j);
    player = new PownPlayer(env);
	powns.push_back(player);
	set((Pown*) player);
}

MainBattle::~MainBattle() {
	SDL_DestroyTexture(square_text);
}

void MainBattle::render() {
	int w = get_env()->win_width(), h = get_env()->win_height();
	tile_size = std::min(w, h) * BATTLE_TILE_SIZE;
	decal_w = w*0.5 - (tile_size*BATTLE_WIDTH)/2;
	decal_h = GRID_DECAL_TOP*h;
	for(int i = 0; i < BATTLE_WIDTH; i++)
		for(int j = 0; j < BATTLE_HEIGHT; j++) {
			Pown* pown = get(i, j);
			if (pown != nullptr) pown->update();
		}
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

void MainBattle::set(Pown* p) {
	if (p != nullptr) board[p->get_pos().x()][p->get_pos().y()] = p;
}

void MainBattle::set_empty(int i, int j) {
    board[i][j] = nullptr;
}

Pown* MainBattle::get(int i, int j) const {
	return board[i][j];
}

Pown* MainBattle::get(Position pos) const {
	return board[pos.x()][pos.y()];
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

SDL_Color MainBattle::get_current_square_color(Position pos) {
    if (get_select() == Move) 
        if (get_player()->is_valid_move(pos))
            return {100, 100, 200, 100};
        else
            return {200, 100, 100, 100};
    else 
        return {100, 100, 100, 100};       
}

#define EXTRACT_COLOR(c) c.r, c.g, c.b, c.a

void MainBattle::display_board() {
	SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(get_env()->get_lablib()), "", lablib_create_color(0, 0, 0, 255));
	SDL_Texture* text = SDL_CreateTextureFromSurface(get_ren(), surf);
	SDL_FreeSurface(surf);
	for(int i = 0; i < BATTLE_WIDTH; i++){
		for(int j = 0; j < BATTLE_HEIGHT; j++){
            SDL_SetRenderDrawColor(get_ren(), EXTRACT_COLOR(get_current_square_color(Position(i, j))));
			SDL_Rect r = lablib_init_rect(i*tile_size + decal_w, j*tile_size + decal_h, tile_size);
            SDL_RenderDrawRect(get_ren(), &r);         
            SDL_RenderFillRect(get_ren(), &r);
		}
	} 
}

void MainBattle::click_on_grid() {
	Lablib* lablib = get_lablib();
	SDL_Point p = lablib_get_last_coordinate(lablib);
	int w = get_env()->win_width(), h = get_env()->win_height();
    Position pos = Position((p.x - decal_w)/tile_size, (p.y - decal_h)/tile_size);
    Pown* pown = get(pos.x(), pos.y());
    if (pown == nullptr)
        click_on_empty_square(pos);
    else
        pown->clicked();
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

#define NB_BUTTON 3
#define B_SIZE 0.1
#define BUTTON_SIZE B_SIZE, B_SIZE
#define BUTTON_Y 1-B_SIZE
void MainBattle::init_lablib(Lablib* lablib) {
	Scene* battle = create_scene(lablib, NB_BUTTON);
	set_scene_background(lablib, battle, BATTLE_BG);
	Button* grid = scene_add_button(battle, 0.5, GRID_DECAL_TOP, 0, 0, "", &b_click_on_grid);
	button_set_display(grid, &b_display_board);
	scene_add_button(battle, 0.3, BUTTON_Y, BUTTON_SIZE, "move", &move_click);
    scene_add_button(battle, 0.5, BUTTON_Y, BUTTON_SIZE, "cancel",&cancel_click);
	get_env()->set_scene(battle, this);
}


void b_click_on_grid(Button* grid) {
	Env* env = (Env*) button_get_env(grid);
	env->get_battle()->click_on_grid();
}

PownPlayer* MainBattle::get_player() const {
    return player;
}

void MainBattle::fight(SpriteSheet monster_sheet) {
	PownMovable* monster = new PownMonster(get_env(), monster_sheet);
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
