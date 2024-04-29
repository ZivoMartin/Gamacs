#ifndef MAP_SAFE
#define MAP_SAVE

#include "../include/global_include.hpp"

class MainGame;

enum GroundType {
	Rock,
	LightGrass,
	DarkGrass,
	LightGrassNorth,
	LightGrassSouth,
	NbGround
};

class Map {
public:
	Map(MainGame* game);
	~Map();
	void draw();
	void draw_square(int x, int y, int i, int j);
		
private:
	void save_texture(const char* path, int index);

	MainGame* game;
	SDL_Texture* ground_textures[NbGround];
	GroundType map[MAP_WIDTH][MAP_HEIGHT];
	void load_game();
};


#endif
