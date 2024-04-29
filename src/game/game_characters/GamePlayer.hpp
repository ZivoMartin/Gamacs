#ifndef SAFE_GAME_PLAYER
#define GAME_PLAYER

#include "MapEntity.hpp"

#include "../../include/global_include.hpp"
#include "../../interfaces/Player.hpp"
#include "../../sprites/Movable.hpp"

class Env;

class GamePlayer : public Movable, public Player, public MapEntity {

public:
    GamePlayer(Env* env);
    ~GamePlayer();
    void action() override;
    void draw() override;
    void interact();
	void collide(Monster* monster) override;
	void collide(MapEntity* entity) override;
	void collide(Pnj* pnj) override;
    
private:
    std::vector<MapEntity*> entity_around;

};



#endif
