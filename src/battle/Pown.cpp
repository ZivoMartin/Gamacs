#include "Pown.hpp"
#include "MainBattle.hpp"

Pown::Pown(MainBattle* battle) {
    this->battle = battle;
}

Pown::~Pown() {}

MainBattle* Pown::get_battle() {
    return battle;
}

void Pown::set_initial_pos(Position pos) {
	get_pos()->set_pos(pos.x(), pos.y());
}

void Pown::draw() {
    int ts = battle->get_ts();
    Updatable::draw(
        battle->get_dw()+get_pos()->x() * ts + ts/2 - get_width()/2,
        battle->get_dh()+get_pos()->y() * ts - get_height()/3
    );
}

