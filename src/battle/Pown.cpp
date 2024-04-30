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
    printf("%d %d\n", pos.x(), pos.y());
	get_pos()->set_pos(pos.x(), pos.y());
}

void Pown::draw() {
    int ts = battle->get_ts();
    Updatable::draw(
        battle->get_dw()+get_pos()->x() * ts + ts/2 - get_width()/2 + move_delta.x(),
        battle->get_dh()+get_pos()->y() * ts - get_height()/3 + move_delta.y()
    );
}

void Pown::reset_move_delta() {
    move_delta.set_pos(0, 0);
}

void Pown::clicked() {
    printf("Pown clicked on %d, %d\n", get_pos()->x(), get_pos()->y());
}

Position* Pown::get_move_delta() {
    return &move_delta;
}
