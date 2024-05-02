#ifndef UPDATABLE_SAFE
#define UPDATABLE_SAFE

class Position;

class Updatable {

public:
    virtual Env* get_env() const = 0;
    virtual void clicked() {}
	virtual void set_initial_pos(Position pos) = 0;
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
	virtual Position get_pos() const = 0;
    virtual void set_pos(Position pos) = 0;
    void translate(int dx, int dy) {
        set_pos(get_pos() + Position(dx, dy));
    }
	int get_x() const {
		return get_pos().x();
	}
	int get_y() const {
		return get_pos().y();
	}
	virtual int get_width() const = 0;
	virtual int get_height() const = 0;

private:
    bool stop = false;

};


#endif
