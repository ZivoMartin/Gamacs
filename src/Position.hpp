#ifndef GAME_POSITION_SAFE
#define GAME_POSITION_SAFE

#include "include/global_include.hpp"

class Env;

class Position {

public:
	Position();
	Position(int x, int y);
	Position(int xy);
	Position(SDL_Point);
	
	int x();
	int y();
	void set_x(int x);
	void set_y(int y);
	void inc_x(int dx);
	void inc_y(int dy);
	void set_pos(int x, int y);
	void set_pos(Position p);
	Position clone();

	Position convert_coord_to_pixels(Env* env);
	
private:
	int the_x, the_y;
	
};


#endif
