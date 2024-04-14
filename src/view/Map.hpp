#ifndef MAP_SAFE
#define MAP_SAVE

#include "../include.hpp"

class Env;

enum GroundType {
	Rock,
	LightGrass,
	DarkGrass,
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
