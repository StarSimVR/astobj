#include <vector>

#include "AstroObject.h"
#include "../libRnfpp/Rnfpp.hpp"

class Controller
{
private:
	std::vector<AstroObject> objects;
	bool firstDraw;

public:
	Controller();
	void registerObject(GodotObject object);
	void removeObject(GodotObject object);
	void updateInfluence();
	void updatePosition();
	Rnfpp getUpdate(GodotObject object);

private:
	void init();
	void iter();
	int findObject(GodotObject object);
}