#ifndef MAP_SAFE
#define MAP_SAVE
#include "../include.hpp"

#define MAP_WIDTH 30
#define MAP_HEIGHT 30


class Env;

enum GroundType {
	Rock,
	NbGround
};

class Map {
public:
	Map(Env* env);
	~Map();
	void draw();
		
private:
	Env* env;
	SDL_Texture* ground_textures[NbGround];
	GroundType map[MAP_WIDTH][MAP_HEIGHT];
};


#endif
