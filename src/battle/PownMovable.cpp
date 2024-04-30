#include "PownMovable.hpp"
#include "../Env.hpp"
#include "MainBattle.hpp"

#define POWN_SPEED 3

PownMovable::PownMovable(Env* env, SpriteSheet sprite_sheet) : Pown(env->get_battle()),  Movable(env, sprite_sheet, POWN_SIZE) {
    set_speed(0);
    set_frame_speed(15);
 }

PownMovable::~PownMovable() {}

void PownMovable::walk_to(Position pos) {
    asked_pos = pos;
    int x = get_pos()->x(), y = get_pos()->y();
    positions.push_back(Position(x + pos.x() - x, y));
    positions.push_back(Position(x, y + pos.y() - y));
    reach_square();
}

bool PownMovable::is_moving() {
    return walk_timer > MOTIONLESS;
}

void PownMovable::actualise_walk_timer() {
    walk_timer -= is_moving();
    if (walk_timer == REACHED) 
        reach_square();
}

void PownMovable::reach_square() {
    if (positions.empty()) {
        walk_timer = MOTIONLESS;
        get_pos()->set_pos(asked_pos.x(), asked_pos.y());
        reset_move_delta();
    } else {
        int x = get_pos()->x(), y = get_pos()->y();
        Position next = positions.back();
        positions.pop_back();
        if (next.x() == x) {
            walk_timer = std::abs(y - next.y()) * get_battle()->get_ts();
            if (y < next.y()) current_dir = Bot;
            else current_dir = Top;
        } else {
            walk_timer = std::abs(x - next.x()) * get_battle()->get_ts();
            if (x < next.x()) current_dir = Right;
            else current_dir = Left;
        }
        walk_timer /= POWN_SPEED;
    }
}



void PownMovable::action() {
    actualise_walk_timer();
    if (is_moving()) {
        if      (current_dir == Left) get_move_delta()->inc_x(-POWN_SPEED);
        else if (current_dir == Right) get_move_delta()->inc_x(POWN_SPEED);
        else if (current_dir == Top) get_move_delta()->inc_y(-POWN_SPEED);
        else if (current_dir == Bot) get_move_delta()->inc_y(POWN_SPEED);
        move(current_dir);
    }
    Pown::draw();
}
