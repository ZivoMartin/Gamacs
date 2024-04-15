#include <stdlib.h>

using namespace std;

#include "../Env.hpp"
#include <iostream>
#include <fstream>
#include <string>
#define ROCK_IMG_PATH "../res/rock_ground.png"
#define LIGHT_GRASS_IMG_PATH "../res/light_grass.png"
#define DARK_GRASS_IMG_PATH "../res/dark_grass.png"
#define LIGHT_GRASS_S_IMG_PATH "../res/light_grassSouth.png"
#define LIGHT_GRASS_N_IMG_PATH "../res/light_grassNorth.png"
#define MAP_FILE_PATH "../res/map.txt"

Map::Map(Env* env) {
	this->env = env;
	load_game();
	save_texture(ROCK_IMG_PATH, Rock);
	save_texture(LIGHT_GRASS_IMG_PATH, LightGrass);
	save_texture(LIGHT_GRASS_S_IMG_PATH, LightGrassSouth);
	save_texture(LIGHT_GRASS_N_IMG_PATH, LightGrassNorth);
}

Map::~Map() {
	for (auto &text: ground_textures) SDL_DestroyTexture(text);
}

void Map::save_texture(const char* path, int index) {
	ground_textures[index] =  (SDL_Texture*) cp(IMG_LoadTexture(env->get_ren(), path));
}

void Map::draw() {
	SDL_Point* pos = env->get_player()->get_pos();
	int player_x = pos->x/TILE_SIZE, 
		player_y = pos->y/TILE_SIZE;
   SDL_Point xy = env->convert_coord_to_pixels({
		   pos->x-VISION_RANGE*TILE_SIZE - (pos->x - player_x*TILE_SIZE),
		   pos->y-VISION_RANGE*TILE_SIZE - (pos->y - player_y*TILE_SIZE)
	   });
	int tile_size = env->compute_ts();
	int start_y = xy.y;
	for (int i=player_x-VISION_RANGE-1; i<player_x+VISION_RANGE+1; i++){
		xy.y = start_y;
		for(int j=player_y-VISION_RANGE-1; j<player_y+VISION_RANGE+1; j++) {
			SDL_Rect r = {.x= xy.x, .y= xy.y, .w= tile_size, .h= tile_size};
			cc(SDL_RenderCopy(env->get_ren(), ground_textures[map[i][j]], NULL, &r));
			xy.y += tile_size;
		}
		xy.x += tile_size;
	}
 }

void Map::load_game() {
	int i = 0, j = 0;
	ifstream f(MAP_FILE_PATH);
    char c;
    while(f.good()) {
		f.get(c);
		if (c == 10) {
			i += 1;
			j = 0;
		} else {
			if (c == 'L') map[j][i] = LightGrass;
			else if (c == 'R') map[j][i] = Rock;
			else if (c == 'S') map[j][i] = LightGrassSouth;
			else if (c == 'N') map[j][i] = LightGrassNorth;
			j += 1;
		} 
    }
    f.close();
}
