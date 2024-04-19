#ifndef SAFE_MAIN_INCLUDE
#define SAFE_MAIN_INCLUDE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define MAP_WIDTH 50
#define MAP_HEIGHT 50
#define VISION_RANGE 10
#define TILE_SIZE 100

void* cp(void* p);

void cc(int c);

enum Direction {
	Top,
	Bot,
	Left,
	Right
};

#endif