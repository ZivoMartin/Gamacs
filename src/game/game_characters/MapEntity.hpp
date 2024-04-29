#ifndef MAPENTITY_SAFE
#define MAPENTITY_SAFE

#include "../../include/global_include.hpp"
#include "../../interfaces/Collider.hpp"
#include "../../interfaces/Updatable.hpp"

class MapEntity : virtual public Updatable, virtual public Collider {

public:
	virtual void interact_with_player() {}
	void set_interactible();
	bool get_can_interact_with_player();
    virtual void draw() override;
    
private:
	bool can_interact_with_player = false;
};

#endif