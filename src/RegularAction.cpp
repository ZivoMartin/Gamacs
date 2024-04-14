#include "RegularAction.hpp"
#include "Env.hpp"

RegularAction::RegularAction(Env* env, int cd, void (Env::*action)()) {
	this->env = env;
	this->cd = cd;
	this->action = action;
}

void RegularAction::try_do() {
	if (!(env->get_now() % cd)) ((env)->*(this->action))();  
}
