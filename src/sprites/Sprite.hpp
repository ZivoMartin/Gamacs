#ifndef SPRITE_SAFE
#define SPRITE_SAFE

#include "../include/global_include.hpp"
#include "../interfaces/Updatable.hpp"

class Env;

class Sprite : virtual public Updatable {

public:
	Sprite(Env* env, SpriteSheet sprite_sheet, float fx, float fy);
    Sprite(Env* env, const char* text, float fx, float fy);
	~Sprite();
    virtual void set_pos(Position pos) override;
	Env* get_env() const override;
	SDL_Renderer* get_ren() const;
	SDL_Window* get_win() const;
	virtual void update() override;
	Position get_pos() const override;
	int get_width() const override;
	int get_height() const override;
	void set_width(int w);
	void set_height(int h);
	void set_size(int w, int h);
	SDL_Texture* get_text() const;
	SpriteSheet get_sprite_sheet() const;
	
	float fx() const;
	float fy() const;
	
private:
    void init(Env* env, float fx, float fy);    
	Env* env;
	int width, height;
	SDL_Texture* sprite_sheet;
	SDL_FPoint factors;
	Position pos;
	SpriteSheet type_sprite_sheet;

};



#endif
