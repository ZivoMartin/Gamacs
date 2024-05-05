#include "Pown.hpp"
#include "../MainBattle.hpp"

Pown::Pown(MainBattle* battle) {
    this->battle = battle;
}

Pown::~Pown() {}

MainBattle* Pown::get_battle() const {
    return battle;
}

void Pown::set_initial_pos(Position pos) {
	set_pos(pos);
}

void Pown::inc_md_y(int y) {
    move_delta.inc_y(y);
}

void Pown::inc_md_x(int x) {
    move_delta.inc_x(x);
}

void Pown::draw() {
    Position pixel_pos = get_pos().battle_get_screen_coord(battle);
    Updatable::draw(
		pixel_pos.x() + get_battle()->get_ts()/2 - get_width()/2 + move_delta.x(),
		pixel_pos.y() - get_height()/3 + move_delta.y()
   );
}

void Pown::reset_move_delta() {
    move_delta.set_pos(0, 0);
}


void Pown::clicked() {

}

Position Pown::get_move_delta() const {
    return move_delta;
}

void Pown::get_attacked_by(SettingAttack* attack) {}
