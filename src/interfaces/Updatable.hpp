#ifndef UPDATABLE_SAFE
#define UPDATABLE_SAFE

class Position;

class Updatable {

public:
	virtual void draw() = 0;
	virtual void draw(int x, int y) = 0;
	virtual void update() = 0;
	virtual Position* get_pos() = 0;
	virtual int get_width() = 0;
	virtual int get_height() = 0;


};


#endif
