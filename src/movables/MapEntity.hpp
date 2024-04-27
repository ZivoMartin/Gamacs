#ifndef MAPENTITY_SAFE
#define MAPENTITY_SAFE

#include "../include.hpp"
#include "Collider.hpp"
#include "../Updatable.hpp"

class MapEntity : virtual public Updatable, public Collider {

public:
	virtual void interact_with_player() {}
	void set_interactible();
	bool get_can_interact_with_player();

private:
	bool can_interact_with_player = false;
	
};

#endif
