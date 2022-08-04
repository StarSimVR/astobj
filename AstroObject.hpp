#ifndef ASTROOBJ 
#define ASTROOBJ

#include <vector>
#include <Godot.hpp>
#include <Spatial.hpp>

#define G (double)(6.6743)
#define AU (double)(2.23795)
#define MP (double)(6.72006)

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
	double calculateDistance(Vector3 position);
	Vector3 calculateForce(double distance, Vector3 direction, double mass);
	void updateRotation();
};

}

#endif
