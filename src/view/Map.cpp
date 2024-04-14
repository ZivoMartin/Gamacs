#include <stdlib.h>

#include "../Env.hpp"
#define ROCK_IMG_PATH "../res/rock_ground.png"
#define LIGHT_GRASS_IMG_PATH "../res/light_grass.png"
#define DARK_GRASS_IMG_PATH "../res/dark_grass.png"

Map::Map(Env* env) {
	this->env = env;
	for (int i=0; i<MAP_WIDTH; i++)
		for(int j=0; j<MAP_HEIGHT; j++) {
			if (j%3 == 1 && i%3 == 1) map[i][j] = DarkGrass;
			else map[i][j] = LightGrass;
		}
			
	ground_textures[Rock] = (SDL_Texture*) cp(IMG_LoadTexture(env->get_ren(), ROCK_IMG_PATH));
	ground_textures[LightGrass] = (SDL_Texture*) cp(IMG_LoadTexture(env->get_ren(), LIGHT_GRASS_IMG_PATH));
	ground_textures[DarkGrass] = (SDL_Texture*) cp(IMG_LoadTexture(env->get_ren(), DARK_GRASS_IMG_PATH));
	
}
Map::~Map() {
	for (auto &text: ground_textures) SDL_DestroyTexture(text);
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

