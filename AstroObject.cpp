#include "AstroObject.hpp"

using namespace godot;

AstroObject::AstroObject()
{

}

AstroObject::~AstroObject()
{

}

void AstroObject::_register_methods()
{
	register_method("_init", &AstroObject::_init);
	register_method("applyForce", &AstroObject::applyForce);
	register_method("updateInfluence", &AstroObject::updateInfluence);
	register_method("updatePosition", &AstroObject::updatePosition);
	register_method("addObject", &AstroObject::addObject);

	register_property<AstroObject, Vector3>("position", &AstroObject::position, Vector3(0,0,0));
	register_property<AstroObject, Vector3>("velocity", &AstroObject::velocity, Vector3(0, 0, 0));
	register_property<AstroObject, Vector3>("acceleration", &AstroObject::acceleration, Vector3(0, 0, 0));
	register_property<AstroObject, Vector3>("orientation", &AstroObject::acceleration, Vector3(0, 0, 0));
	register_property<AstroObject, int>("rotationSpeed", &AstroObject::rotationSpeed, 0);
	register_property<AstroObject, double>("mass", &AstroObject::mass, 0.0);
}

void AstroObject::_init()
{

}

void AstroObject::addObject(Object* object)
{
	AstroObject* astroObject = Object::cast_to<AstroObject>(object);
	if(astroObject)
	{
		this->affectedObjects.push_back(astroObject);
	}
}

void AstroObject::applyForce(Vector3 force)
{
	Vector3 result;
	result.x = (double)force.x / this->getMass();
	result.y = (double)force.y / this->getMass();
	result.z = (double)force.z / this->getMass();
	this->acceleration += result;
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
	set_translation(this->position * 10);
}


double AstroObject::getMass()
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
	
	for(AstroObject * elem : this->affectedObjects)
	{
		if(this->position == elem->getPosition()) continue;
		double distanceSquared = this->calculateDistance(elem->getPosition());

		Vector3 direction = elem->getPosition() - this->position;
		direction.normalized();
		Vector3 force = this->calculateForce(distanceSquared, direction, elem->getMass());
		this->applyForce(force);
		elem->applyForce(force * -1);
	}
	
}


double AstroObject::calculateDistance(Vector3 position)
{
	
	double distance = this->position.distance_to(position);
	return distance * distance;
}


Vector3 AstroObject::calculateForce(double distance, Vector3 direction, double mass)
{
	
	double forceNoDirection = G * this->getMass() * mass * MP / (distance * AU);
	Vector3 force;
	force.x = (double)direction.x * forceNoDirection;
	force.y = (double)direction.y * forceNoDirection;
	force.z = (double)direction.z * forceNoDirection;
	return force;
}


void AstroObject::updateRotation()
{

}
