#ifndef UPDATABLE_SAFE
#define UPDATABLE_SAFE

class Position;

class Updatable {

public:
    virtual Env* get_env() const = 0;
	virtual void draw() = 0;
    virtual void draw(int x, int y) {
        if (stop) {
            fprintf(stderr, "You didn't defined draw(int int)");
            exit(1);
        }
        stop = true;
        this->draw(x, y);
        stop = false;
    };
	virtual void update() = 0;
	virtual Position* get_pos() = 0;
	virtual int get_width() = 0;
	virtual int get_height() = 0;

private:
    bool stop = false;

};


#endif