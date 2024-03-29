#ifndef ASTROOBJ 
#define ASTROOBJ

#include <vector>
#include <Godot.hpp>
#include <Spatial.hpp>

/*These constants represent the gravitational constant, the astronomical unit and the mass parameter, scaled down*/
#define G (real_t)(6.6743)
#define MP (real_t)(672006)

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
	real_t mass;
	bool removed = false;
	std::vector<AstroObject*> affectedObjects;

public:
	AstroObject();
	~AstroObject();
	void _init();
	void addObject(Object* object);
	void applyForce(Vector3 force);
	void updateInfluence();
	void updatePosition(real_t data);
	real_t getMass();
	Vector3 getPosition();
	static void _register_methods();
	void absorbObject(AstroObject* toAbsorb);
	void free();
	bool shouldBeRemoved();
	void removeObject(AstroObject* toRemove);

private:
	void iter();
	Vector3 calculateForce(real_t distanceSquared, Vector3 direction, real_t mass);
	void updateRotation();
};

}

#endif
