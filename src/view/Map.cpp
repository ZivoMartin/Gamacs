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
	int mx = ((pos->x%TILE_SIZE - TILE_SIZE/2) * PIXEL_TILE_SIZE) / TILE_SIZE,
		my = ((pos->y%TILE_SIZE - TILE_SIZE/2) * PIXEL_TILE_SIZE) / TILE_SIZE;
	int x=0, y=0;
	int width = env->win_width(), height = env->win_height();
	for (int il=width/2-mx - PIXEL_TILE_SIZE, ir = width/2-mx - PIXEL_TILE_SIZE; (il+PIXEL_TILE_SIZE) > 0 || (ir-PIXEL_TILE_SIZE) < width; il-=PIXEL_TILE_SIZE, ir+=PIXEL_TILE_SIZE){
		for (int jl=height/2-my - PIXEL_TILE_SIZE, jr=height/2-my - PIXEL_TILE_SIZE; (jl+PIXEL_TILE_SIZE) > 0 || (jr-PIXEL_TILE_SIZE) < height; jl-=PIXEL_TILE_SIZE, jr+=PIXEL_TILE_SIZE) {
			SDL_Rect r1 = {.x=il, .y=jl, .w=PIXEL_TILE_SIZE, .h=PIXEL_TILE_SIZE};
			SDL_Rect r2 = {.x=ir , .y=jr, .w=PIXEL_TILE_SIZE, .h=PIXEL_TILE_SIZE};
			cc(SDL_RenderCopy(env->get_ren(), ground_textures[map[player_x-x][player_y-y]], NULL, &r1));
			cc(SDL_RenderCopy(env->get_ren(), ground_textures[map[player_x+x][player_y+y]], NULL, &r2));
			SDL_Rect r3 = {.x=il, .y=jr, .w=PIXEL_TILE_SIZE, .h=PIXEL_TILE_SIZE};
			SDL_Rect r4 = {.x=ir , .y=jl, .w=PIXEL_TILE_SIZE, .h=PIXEL_TILE_SIZE};
			cc(SDL_RenderCopy(env->get_ren(), ground_textures[map[player_x-x][player_y+y]], NULL, &r3));
			cc(SDL_RenderCopy(env->get_ren(), ground_textures[map[player_x+x][player_y-y]], NULL, &r4));
			y += 1;
		}
		y = 0;
		x += 1;
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
