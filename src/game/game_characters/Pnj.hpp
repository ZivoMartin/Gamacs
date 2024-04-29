#ifndef PNJ_SAFE
#define PNJ_SAFE

#include "../../sprites/Static.hpp"
#include "MapEntity.hpp"
#include "../../include/global_include.hpp"


class Env;
class MainGame;

class Pnj : public Static, public MapEntity {
	
public:

	Pnj(Env* env, MainGame* game, const char* img_path, SDL_Point pos, ActionVec actions);
	~Pnj();
	void update() override;
	void interact_with_player() override;
	void collide(GamePlayer* player) override;
	void collide(MapEntity* entity) override;
	std::string* get_dialog();
	void inc_dialog_index();
	void reset_dialog_index();
	void set_dialog(const char* file_path);
	MainGame* get_game();
	
private:

	int timer = -1;
	int dialog_index = 0;
	int current_action = 0;
	std::vector<std::string> dialog_vec;
	ActionVec actions;
	MainGame* game;
	
};


#endif
