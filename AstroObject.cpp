#include "AstroObject.hpp"
#include "libRnfpp/Rnfpp.hpp"

using namespace godot;

AstroObject::AstroObject()
{

}

void AstroObject::_register_methods()
{
	register_method("_init", &AstroObject::_init);
	register_method("applyForce", &AstroObject::applyForce);
	register_method("updateInfluence", &AstroObject::updateInfluence);
	register_method("updatePosition", &AstroObject::updatePosition);
	//register_method("init", &AstroObject::init);
	register_property<AstroObject, int>("mass", &AstroObject::setMass, &AstroObject::getMass, 0);

	register_property<AstroObject, Vector3>("position", &AstroObject::setPosition, &AstroObject::getPosition, Vector3(0,0,0));
}

/*
AstroObject::AstroObject(Rnfpp position, Rnfpp orientation, int rotationSpeed, int mass)
{
	this->position = position;
	this->velocity = Vector3{0,0,0};
	this->acceleration = Vector3{0,0,0};
	this->orientation = orientation;
	this->rotationSpeed = rotationSpeed;
	this->mass = mass;
	this->calculateInfluenceRadius();
}*/

void AstroObject::_init()
{

}

void AstroObject::applyForce(Vector3 force)
{
	//this->acceleration += force;
}


void AstroObject::updateInfluence()
{
	this->iter();
	this->updateRotation();
}


void AstroObject::updatePosition()
{
	
	this->velocity += this->acceleration;
	this->position += this->velocity;
	this->acceleration = Vector3(0,0,0);
	
}


void AstroObject::init(std::vector<AstroObject> affectedObjects)
{
	this->affectedObjects = affectedObjects;
}


int AstroObject::getMass()
{
	return this->mass;
}

void AstroObject::setMass(int mass)
{
	this->mass = mass;
}


Vector3 AstroObject::getPosition()
{
	return this->position;
}


void AstroObject::setPosition(Vector3 position)
{
	this->position = position;
}


void AstroObject::iter()
{
	
	for(AstroObject & elem : this->affectedObjects)
	{
		if(this->position == elem.getPosition()) continue;
		int distance = this->calculateDistance(elem.getPosition());
		if (distance > this->influenceRadius)
			continue;

		Vector3 direction = elem.getPosition() - this->position;
		direction.normalized();
		Vector3 force = this->calculateForce(distance, direction);
		elem.applyForce(force);
	}
	
}


int AstroObject::calculateDistance(Vector3 position)
{
	
	float distance = this->position.distance_to(position);
	//calculate actual distance
	//...
	return (int)distance;
}


void AstroObject::calculateInfluenceRadius()
{
	//calculate the gravitational influence based on the mass
	this->influenceRadius = 0;
}


Vector3 AstroObject::calculateForce(int distance, Vector3 direction)
{
	//calculate the force influencing an object based on the mass and distance
	return Vector3{0,0,0};
}


void AstroObject::updateRotation()
{

}
