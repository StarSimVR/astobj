#ifndef ASTROOBJ 
#define ASTROOBJ

#include <vector>
#include <Godot.hpp>
#include <Spatial.hpp>

namespace godot{

class AstroObject : public Spatial
{
	GODOT_CLASS(AstroObject, Spatial)
private:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	Vector3 orientation;
	int rotationSpeed;
	int mass;
	int influenceRadius;
	std::vector<AstroObject> affectedObjects;

public:
	//AstroObject(Rnfpp position, Rnfpp orientation, int rotationSpeed, int mass);
	AstroObject();
	void _init();
	void applyForce(Vector3 force);
	void updateInfluence();
	void updatePosition();
	void init(std::vector<AstroObject> affectedObjects);
	int getMass();
	void setMass(int mass);
	Vector3 getPosition();
	void setPosition(Vector3 position);
	static void _register_methods();

private:
	void iter();
	int calculateDistance(Vector3 position);
	void calculateInfluenceRadius();
	Vector3 calculateForce(int distance, Vector3 direction);
	void updateRotation();
};

}

#endif
