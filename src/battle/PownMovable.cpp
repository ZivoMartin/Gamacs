#include "PownMovable.hpp"
#include "../Env.hpp"
#include "MainBattle.hpp"

#define POWN_SPEED 3

PownMovable::PownMovable(Env* env, SpriteSheet sprite_sheet) : Pown(env->get_battle()),  Movable(env, sprite_sheet, POWN_SIZE) {
    set_speed(0);
    set_frame_speed(15);
 }

PownMovable::~PownMovable() {}

bool cond_stop(int nb1, int nb2, bool swap){
    if (!swap) 
        return nb1 < nb2;
    else
        return nb1 > nb2;
    
}

void PownMovable::walk_to(Position pos) {
    positions.push_back(*get_pos());
    asked_pos = pos;
    int xy[2] = {get_pos()->x(), get_pos()->y()};
    int i = 0;
    int higher = 0;     // Indice de la position du coordoné de la plus grande distance à parcourir (x par défaut)
    int lower = 1;      // Indice de la position du coordoné de la plus petite distance à parcourir (y par défaut)
    int higher_target = pos.x();  // coordoné de la target de la plus grande distance à parcourir (x par défaut)
    int lower_target = pos.y();   // coordoné de la target de la plus petite distance à parcourir (y par défaut)
    int dl = std::abs(lower_target - xy[lower]);    // Plus petite distance (même si le programme ne l'a pas encore verifié)
    int dh = std::abs(higher_target - xy[higher]);  // Plus grande distance (même si le programme ne l'a pas encore verifié)
    if (dh < dl) {  // On verifie si dh est bien plus grand que dl, i.e si x est bien l'axe de la plus grande distance à parcourir
        higher = 1; // Si non on inverse toutes les données
        lower = 0;
        higher_target = lower_target;
        lower_target = pos.x();
        int tmp = dh;
        dh = dl;
        dl = tmp;
    }
    int f_l = xy[lower] - lower_target < 0 ? 1 : -1;    // nombre à ajouter a xy[lower] quand d passe en dessous de 0
    int f_h = xy[higher] - higher_target < 0 ? 1 : -1;  // nombre à ajouter a xy[higher] a chaque iteration
    bool swap = higher_target < xy[higher];  // sera utiliser dans la fonction condStop pour savoir quel est la condition d'arrêt
    int d = 2*dl-dh;
    while(cond_stop(xy[higher], higher_target, swap)) { // Lancement de l'algo après l'initialisation de toutes les variables.
        xy[higher] += f_h;
        if (d < 0) 
            d += 2*dl;
        else {
            positions.push_back(Position(xy[0], xy[1]));
            xy[lower] += f_l;
            d += 2*(dl-dh);
        }
        positions.push_back(Position(xy[0], xy[1]));
    }
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
     Position prev = positions.back();
     positions.pop_back();
    if (positions.empty()) {
        walk_timer = MOTIONLESS;
        get_pos()->set_pos(asked_pos.x(), asked_pos.y());
        reset_move_delta();
    } else {
        int x = get_pos()->x(), y = get_pos()->y();
        Position next = positions.back();
        if (next.x() == prev.x()) {
            walk_timer = std::abs(prev.y() - next.y()) * get_battle()->get_ts();
            current_dir = prev.y() < next.y() ? Top : Bot;
        } else {
            walk_timer = std::abs(prev.x() - next.x()) * get_battle()->get_ts();
            current_dir = prev.x() < next.x() ? Left : Right;
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