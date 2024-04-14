#ifndef SAFE_REGULAR_ACTION
#define SAFE_REGULAR_ACTION
#define X_LINE 0
#define Y_LINE 1

class Env;

class RegularAction {

public:
	RegularAction(Env* env, int cd, void (Env::*action)());
	void try_do();

private:
	Env* env;
	int cd;
	void (Env::*action)();
	
};


#endif
