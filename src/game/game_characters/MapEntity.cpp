#include "MapEntity.hpp"
#include "../../Env.hpp"
#include "../MainGame.hpp"

void MapEntity::set_interactible() {
	can_interact_with_player = true;
}

bool MapEntity::get_can_interact_with_player() {
	return can_interact_with_player;
}


void MapEntity::draw() {
	Position p = get_pos()->convert_coord_to_pixels(get_env()->get_game());
	Position map_dim = get_env()->game_dim();
	if (p.x() > -get_width() && p.y() > -get_height() && p.x() < map_dim.x() && p.y() < map_dim.y())
        Updatable::draw(p.x(), p.y());
}
