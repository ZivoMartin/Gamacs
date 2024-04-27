#include "MapEntity.hpp"



void MapEntity::set_interactible() {
	can_interact_with_player = true;
}

bool MapEntity::get_can_interact_with_player() {
	return can_interact_with_player;
}
