#include <SDL2/SDL.h> 
#include <cstdlib>
#include "Env.hpp"




int main(int argc, char* argv[])
{
	Env* env = new Env();
	env->game_loop();
	return EXIT_SUCCESS;
}


