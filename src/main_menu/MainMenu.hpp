#ifndef SAFE_MENU
#define SAFE_MENU

#include "../interfaces/Renderer.hpp"
#include "../include/global_include.hpp"

#define MENU_BG "res/menu_bg.png"

class MainMenu : public Renderer {

public:
	MainMenu(Env* env, Lablib* lablib);
	~MainMenu();
	void init_lablib(Lablib* lablib) override;
	void render() override;
	void handdle_keypress() override;
	
private:
	
};


#endif
