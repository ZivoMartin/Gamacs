#ifndef SAFE_GAME_PLAYER
#define GAME_PLAYER

#include "MapEntity.hpp"

#include "../../include/global_include.hpp"
#include "../../interfaces/Player.hpp"

class Env;

class GamePlayer : public Player, public MapEntity {

public:
    GamePlayer(Env* env);
    ~GamePlayer();
    void draw() override;
    void interact();
	void collide(Monster* monster) override;
	void collide(MapEntity* entity) override;
	void collide(Pnj* pnj) override;
    
private:
    std::vector<MapEntity*> entity_around;

};



#endif
