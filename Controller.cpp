#include "Controller.hpp"

Controller::Controller()
{
	this.firstDraw = true;
}


void Controller::updateInfluence()
{
	if(this.firstDraw)
	{
		this.init();
		this.firstDraw = false;
	}
	this.iter();
	this.updatePosition();
}


void Controller::iter()
{
	for(AstroObject & elem : this.objects)
	{
		elem.updateInfluence();
	}
}


void Controller::updatePosition()
{
	for(AstroObject & elem : this.objects)
	{
		elem.updatePosition();
	}
}


void Controller::init()
{
	for(AstroObject & elem : this.objects)
	{
		elem.init(this.objects);
	}
}