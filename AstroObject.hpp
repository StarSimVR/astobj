#ifndef ASTROOBJ 
#define ASTROOBJ

#include <vector>
#include <Godot.hpp>
#include <Spatial.hpp>
#include "libRnfpp/Rnfpp.hpp"

namespace godot{

class AstroObject : public Spatial
{
	GODOT_CLASS(AstroObject, Spatial)
private:
	Rnfpp position;
	Rnfpp velocity;
	Rnfpp acceleration;
	Rnfpp orientation;
	int rotationSpeed;
	int mass;
	int influenceRadius;
	std::vector<AstroObject> affectedObjects;

public:
	//AstroObject(Rnfpp position, Rnfpp orientation, int rotationSpeed, int mass);
	AstroObject();
	void _init();
	void applyForce(Rnfpp force);
	void updateInfluence();
	void updatePosition();
	void init(std::vector<AstroObject> affectedObjects);
	int getMass();
	Rnfpp getPosition();
	void setPosition(Rnfpp position);
	static void _register_methods();

private:
	void iter();
	int calculateDistance(Rnfpp position);
	void calculateInfluenceRadius();
	Rnfpp calculateForce(int distance, Rnfpp direction);
	void updateRotation();
};

}

#endif
