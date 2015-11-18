#include "Goal.h"
#include "ShaderIF.h"
#include "Block.h"
#include "Cylinder.h"
#include "Support.h"

Support::Support(bool isNear)
{
	if(isNear)
	{
		cylinderX = 29.65;
		horizModifier = - 2.2192;
		dAngle = -.5;
	} else
	{
		cylinderX = -1;
		horizModifier = 0;
		dAngle = .5;
	}
	create();
}

Support::~Support()
{
}

void Support::create()
{
	cylinderAngle = 270;
	cylinderY = 7.62;
	cylinderZ = 0;
	radius = 0.1524;

	Cylinder* vertSupport = new Cylinder(cylinderX, cylinderY, cylinderZ, 0, cylinderAngle, 0, 3, .1524);
	models.push_back(vertSupport);

	//elbow joint
	for(int i = 0; i < 180; i++)
	{
		// cylinderX = -1;
		// cylinderZ = 3;
		cylinderAngle += dAngle;

		// ??? does not work ???
		// cylinderX += radius - (radius * cos(cylinderAngle * M_PI / 180));
		// cylinderZ += radius * sin(cylinderAngle * M_PI / 180);

		Cylinder* cylinder = new Cylinder(cylinderX, cylinderY, cylinderZ, 0, cylinderAngle, 0, .01, .1524);
		models.push_back(cylinder);
	}

	Cylinder* horizSupport = new Cylinder(cylinderX + horizModifier, 7.62, 3, 0, 0, 0, 2.2192, .1524);
	models.push_back(horizSupport);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Support::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = 0;
	xyzLimits[1] = 28.56;
	xyzLimits[2] = 0;
	xyzLimits[3] = 15.24;
	xyzLimits[4] = 0;
	xyzLimits[5] = .01;
}

void Support::render()
{
	for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
		(*it)->render();
}
