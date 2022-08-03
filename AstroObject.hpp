#ifndef ASTROOBJ 
#define ASTROOBJ

#include <vector>
#include <Godot.hpp>
#include <Spatial.hpp>

namespace godot{

class AstroObject : public Spatial
{
	GODOT_CLASS(AstroObject, Spatial)
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	Vector3 orientation;
	int rotationSpeed;
	double mass;
	std::vector<AstroObject*> affectedObjects;
	const int sD = 13927;
	const double eM = 5.972;
	const double G = 6.672;

public:
	AstroObject();
	~AstroObject();
	void _init();
	void addObject(Object* object);
	void applyForce(Vector3 force);
	void updateInfluence();
	void updatePosition();
	double getMass();
	void setMass(int mass);
	Vector3 getPosition();
	void setPosition(Vector3 position);
	static void _register_methods();

private:
	void iter();
	int calculateDistance(Vector3 position);
	Vector3 calculateForce(int distance, Vector3 direction, double mass);
	void updateRotation();
};

}

#endif
