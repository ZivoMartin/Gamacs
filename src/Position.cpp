#include "Position.hpp"
#include "game/MainGame.hpp"
#include "game/game_characters/GamePlayer.hpp"
#include "battle/MainBattle.hpp"

Position::Position() {
	set_pos(0, 0);
}

Position::Position(int x, int y) {
	set_pos(x, y);
}

Position::Position(int xy) {
	set_pos(xy, xy);
}

Position::Position(SDL_Point p) {
	set_pos(p.x, p.y);
}
	
int Position::x() const {
	return the_x;
}

int Position::y() const {
	return the_y;
}

void Position::set_x(int x) {
	the_x = x;
}

void Position::set_y(int y) {
	the_y = y;
}

void Position::set_pos(int x, int y) {
	set_x(x);
	set_y(y);
}

void Position::set_pos(Position p) {
	set_pos(p.x(), p.y());
}

Position Position::clone() {
	return Position(x(), y());
}

void Position::inc_y(int dy) {
	set_y(y()+dy);
}

void Position::inc_x(int dx) {
	set_x(x()+dx);
}

Position Position::convert_coord_to_pixels(MainGame* game) const {
	GamePlayer* player = game->get_player();
	int w, h;
	SDL_GetWindowSize(game->get_win(), &w, &h);
	return Position(
		w/2 - (player->get_pos().x() - x()),
		h/2 - (player->get_pos().y() - y())
		);
}


int Position::range_with(Position pos) const {
	return std::abs(x() - pos.x()) + std::abs(y() - pos.y());
}

Position Position::battle_get_screen_coord(MainBattle* battle) const {
	int ts = battle->get_ts();
    return Position(
        battle->get_dw()+x() * ts,
        battle->get_dh()+y() * ts
    );
}
