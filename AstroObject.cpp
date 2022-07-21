#include "AstroObject.hpp"

using namespace godot;

AstroObject::AstroObject()
{

}

void AstroObject::_register_methods()
{

}

/*
AstroObject::AstroObject(Rnfpp position, Rnfpp orientation, int rotationSpeed, int mass)
{
	this->position = position;
	this->velocity = std::vector<float>{0,0,0};
	this->acceleration = std::vector<float>{0,0,0};
	this->orientation = orientation;
	this->rotationSpeed = rotationSpeed;
	this->mass = mass;
	this->calculateInfluenceRadius();
}*/

void AstroObject::_init()
{

}

void AstroObject::applyForce(Rnfpp force)
{
	this->acceleration += force;
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
	this->acceleration = std::vector<float>{0,0,0};
}


void AstroObject::init(std::vector<AstroObject> affectedObjects)
{
	this->affectedObjects = affectedObjects;
}


int AstroObject::getMass()
{
	return this->mass;
}


Rnfpp AstroObject::getPosition()
{
	return this->position;
}


void AstroObject::setPosition(Rnfpp position)
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

		Rnfpp direction = elem.getPosition() - this->position;
		direction.normalise();
		Rnfpp force = this->calculateForce(distance, direction);
		elem.applyForce(force);
	}
}


int AstroObject::calculateDistance(Rnfpp position)
{
	float distance = this->position.distance(position);
	//calculate actual distance
	//...
	return distance;
}


void AstroObject::calculateInfluenceRadius()
{
	//calculate the gravitational influence based on the mass
	this->influenceRadius = 0;
}


Rnfpp AstroObject::calculateForce(int distance, Rnfpp direction)
{
	//calculate the force influencing an object based on the mass and distance
	return std::vector<float>{0,0,0};
}


void AstroObject::updateRotation()
{

}
