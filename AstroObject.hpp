#include <vector>

#include "../libRnfpp/Rnfpp.hpp"

class AstroObject
{
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
	AstroObject(Rnfpp position, Rnfpp orientation, int rotationSpeed, int mass);
	void applyForce(Rnfpp force);
	void updateInfluence();
	void updatePosition();
	void init(std::vector<AstroObject> affectedObjects);
	int getMass();
	Rnfpp getPosition();
	void setPosition(Rnfpp position);

private:
	void iter();
	int calculateDistance(Rnfpp position);
	void calculateInfluenceRadius();
	Rnfpp calculateForce(int distance, Rnfpp direction);
	void updateRotation();
};