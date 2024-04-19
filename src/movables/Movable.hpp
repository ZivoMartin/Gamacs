#ifndef SAFE_MOVABLE
#define SAFE_MOVABLE
#include "../include.hpp"
#include "../sprite_data.hpp"

#define BASE_SPEED 3
#define BASE_FRAME_SPEED 10

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
	void set_speed(int s);
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
	virtual void attack(int attack_number);
	void update_frame();
	
private:
	Env* env;
	SDL_Texture* sprite_sheet;
	SDL_Point pos;
	int speed;
	SDL_Point current_sprite = {0, 10};
	SDL_FPoint factors;
	int width, height;
	bool has_move = false;
	int frame_speed = BASE_FRAME_SPEED;
	bool is_doing_something = false;
	int attack_sprite_row = 3;
	int nb_sprite_col = 1;
	Direction current_dir = Bot;
	int attack_sprites_number[NB_SPELL][2] = {SPELL_0_SPRITE, SPELL_1_SPRITE, SPELL_2_SPRITE};
};

#endif
