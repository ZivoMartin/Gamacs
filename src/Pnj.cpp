#include "Pnj.hpp"
#include "Env.hpp"
#include "movables/Player.hpp"

#define ACTION_TIME 30
#define BASE_FX 0.07
#define BASE_FY 0.11

Pnj::Pnj(Env* env, const char* img_path, SDL_Point pos,  ActionVec actions) : Sprite(env, img_path, pos, BASE_FX, BASE_FY){
	this->actions = actions;
	set_interactible();
}


Pnj::~Pnj() {}


void Pnj::update() {
	Sprite::update();
	this->draw();
}


void Pnj::interact_with_player() {
	if (timer < get_env()->get_now() && current_action < actions.size()) {
		(get_env()->*(actions[current_action].first))(this);
		if (!actions[current_action].second || (get_env()->*(actions[current_action].second))()) {
			current_action += 1;
		}
		timer = get_env()->get_now() + ACTION_TIME;
	}
}

void Pnj::collide(Player* player) {}

void Pnj::collide(Sprite* sprite) {
	sprite->collide(this);
}

std::string* Pnj::get_dialog() {
	if (dialog_index >= dialog_vec.size()) {
		fprintf(stderr, "Dialog index out of range\n");
		exit(1);
	}
	return &dialog_vec[dialog_index];
}
void Pnj::inc_dialog_index() {
	dialog_index = (dialog_index+1)%dialog_vec.size();
}
void Pnj::reset_dialog_index() {
	dialog_index = 0;
}

#define END_CHAR '$'

void Pnj::set_dialog(const char* file_path) {
	std::ifstream f(file_path);
	std::string current;
	char c;
	while (f.good()) {
		f.get(c);
		if (c == END_CHAR) {
			dialog_vec.push_back(current);
			current.clear();
			do {f.get(c);} while (f.good() && c == 10);
		}
		current.push_back(c);
	}
}

	
