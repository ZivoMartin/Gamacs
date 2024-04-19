#ifndef SAFE_MOVABLE
#define SAFE_MOVABLE
#include "../sprite_data.hpp"
#include "../include.hpp"

#define WALK_MOD 10
#define RUN_MOD 20

class Env;

class Movable {

public:
	Movable(Env* env, const char* img_path, SDL_Point pos, float fx, float fy);
	~Movable();
	void update();
	virtual void action() = 0 ;
	
	Env* get_env();
	virtual void draw();
	void draw(int x, int y);
	SDL_Texture* get_text();
	SDL_Renderer* get_ren();
	SDL_Point* get_pos();
	virtual void move(int dx, int dy);
	int get_speed();
	void recompute_position();

	
	int get_sprite_col();
    int get_sprite_row();
	void set_current_sprite(int x, int y);
	void set_sprite_col(int x);
	void set_sprite_row(int y);
	void inc_sprite_col();
	
	int get_width();
	int get_height();
	void set_width(int w);
	void set_height(int h);
	void set_size(int w, int h);

	float fx();
	float fy();

	virtual void move(Direction dir);
	void set_frame_speed(int new_frame_speed);
	
private:
	Env* env;
	SDL_Texture* sprite_sheet;
	SDL_Point pos;
	int speed;
	SDL_Point current_sprite;
	SDL_FPoint factors;
	int width, height;
	bool has_move = false;
	int frame_speed = WALK_MOD;
	
};

#endif
