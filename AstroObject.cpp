#include "AstroObject.hpp"
#include <sstream>
#include <string>

template <typename T>
std::string ToString(T val)
{
	std::stringstream stream;
    stream << val;
    return stream.str();
}

using namespace godot;

/**
 *	@brief 			The constructor for the AstroObject class, left empty due to godot
 */
AstroObject::AstroObject()
{

}


/**
 *	@brief 			The destructor for the AstroObject class
 */
AstroObject::~AstroObject()
{
	//ToDo: Implement
}


/**
 *	@brief 			Function to register the methods and properties that are relevant for godot
 *	@return 		void
 */
void AstroObject::_register_methods()
{
	/*Register the methods*/
	register_method("_init", &AstroObject::_init);
	register_method("applyForce", &AstroObject::applyForce);
	register_method("updateInfluence", &AstroObject::updateInfluence);
	register_method("updatePosition", &AstroObject::updatePosition);
	register_method("addObject", &AstroObject::addObject);
	register_method("removeObject", &AstroObject::removeObject);
	register_method("shouldBeRemoved", &AstroObject::shouldBeRemoved);

	/*Register the properties*/
	register_property<AstroObject, Vector3>("position", &AstroObject::position, Vector3(0,0,0));
	register_property<AstroObject, Vector3>("velocity", &AstroObject::velocity, Vector3(0, 0, 0));
	register_property<AstroObject, Vector3>("acceleration", &AstroObject::acceleration, Vector3(0, 0, 0));
	register_property<AstroObject, Vector3>("orientation", &AstroObject::acceleration, Vector3(0, 0, 0));
	register_property<AstroObject, int>("rotationSpeed", &AstroObject::rotationSpeed, 0);
	register_property<AstroObject, real_t>("mass", &AstroObject::mass, 0.0);
}


/**
 *	@brief 			The _init() function which is required by godot, left empty
 *	@return 		void
 */
void AstroObject::_init()
{
	//Nothing is needed here
}


/**
 *	@brief 			Function to add an object to the internaly managed object list
 *	@param	object 	Pointer to the object
 *	@return 		void
 */
void AstroObject::addObject(Object* object)
{
	//Safty cast to check if the incoming objet is of type AstroObject
	AstroObject* astroObject = Object::cast_to<AstroObject>(object);
	if(astroObject)
	{
		this->affectedObjects.push_back(astroObject);
	}
}


/**
 *	@brief 			Function to add an external force to the acceleration
 *	@param	force 	The force working on the object
 *	@return 		void
 */
void AstroObject::applyForce(Vector3 force)
{
	//The acceleration is calculated as m/s^2, but the velocity and position is stored in km, so the value has to be adjusted
	this->acceleration += force / this->getMass();
}


/**
 *	@brief 			Function to update the influence this object has on others
 *	@return 		void
 */
void AstroObject::updateInfluence()
{
	this->iter();
	this->updateRotation();
}


/**
 *	@brief 			Function to update the objects position based on its acceleration and velocity
 *	@return 		void
 */
void AstroObject::updatePosition(real_t delta)
{
	this->velocity += this->acceleration * 3600 * 3600;
	this->position += this->velocity;
	this->acceleration = Vector3(0,0,0);
	//The scene works with very small distances internally, that have to be scaled to be visible
	set_translation(this->position / 100000000000);
}


/**
 *	@brief 			Getter for the obejcts mass
 *	@return 		Mass as double
 */
real_t AstroObject::getMass()
{
	return this->mass;
}


/**
 *	@brief 			Getter for the objects position
 *	@return			Position as godot::Vector3
 */
Vector3 AstroObject::getPosition()
{
	return this->position;
}


/**
 *	@brief 			The main function of the class, updates the influence of every other object and itself
 *	@return 		void
 */
void AstroObject::iter()
{
	
	for(AstroObject * elem : this->affectedObjects)
	{
		/*Calculate the force on ourself and the other object*/
		real_t distance = this->position.distance_to(elem->getPosition());
		//If the objects collide, we merge the objects
		if( distance / 100000000 < 1.0f) 
		{
			if(this->getMass() >= elem->getMass()) this->absorbObject(elem);
			else elem->absorbObject(this);
			continue;
		}

		real_t distanceSquared = distance * distance;

		Vector3 direction = elem->getPosition() - this->position;
		direction = direction.normalized();
		Vector3 force = this->calculateForce(distanceSquared, direction, elem->getMass());

		/*Since the force working on our object and the other object is the same, we can simply flip the direction and use it 
		for both*/
		this->applyForce(force);
		elem->applyForce(force * -1);
	}
	
}


/**
 *	@brief 			Function to remove an object from the interally stored list of objects
 *	@param toRemove The object to remove
 *	@return 		void
 */
void AstroObject::removeObject(AstroObject* toRemove)
{
	auto it = std::find(this->affectedObjects.begin(), this->affectedObjects.end(), toRemove);
	if(it != this->affectedObjects.end())
	{
		this->affectedObjects.erase(it);
	}
}


/**
 *	@brief 						Function to calculate the force between the bodies
 *	@param	distanceSquared 	The distance between the two objects squared, as a double
 *	@param 	direction 			The direction from our object to the other object normalized, as Vector3
 *	@param 	mass 				The mass of the other object, as a double
 *	@return 					The force from our object to the other object, as Vector3
 */
Vector3 AstroObject::calculateForce(real_t distanceSquared, Vector3 direction, real_t mass)
{
	//Based on Newtons law of gravity
	real_t forceNoDirection = G * this->getMass() * mass * MP * 10000000 / distanceSquared;
	return direction * forceNoDirection;
}


/**
 *	@brief 			Function to rotate the object around its rotationVector
 *	@return 		void
 */
void AstroObject::updateRotation()
{
	//ToDo: Implement
}


/**
 *	@brief 			Function to absorb another object
 *	@param toAbsorb	Object to absorb
 *	@return 		void
 */
void AstroObject::absorbObject(AstroObject* toAbsorb)
{
	this->mass += toAbsorb->getMass();
	toAbsorb->free();
}


/**
 *	@brief 			Function to free a given object
 *	@return 		void
 */
void AstroObject::free()
{
	this->removed = true;
}


/**
 *	@brief 			Function to state whether the object in question should be removed
 *	@return 		True, if the object should be removed, else False
 */
bool AstroObject::shouldBeRemoved()
{
	return this->removed;
}
