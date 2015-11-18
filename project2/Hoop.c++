#include "Goal.h"
#include "ShaderIF.h"
#include "Block.h"
#include "Cylinder.h"
#include "Hoop.h"

Hoop::Hoop()
{
	dAngle = .25;
	create();
}

Hoop::~Hoop()
{
}

void Hoop::create()
{
	cylinderAngle = 0;
	cylinderZ = 3.0;
	radius = 0.017;
	//elbow joint
	for(int i = 0; i < 1480; i++)
	{
		cylinderAngle += dAngle;
		cylinderX = 1.7;
		cylinderY = 7.62;

		cylinderX += .45 * cos(cylinderAngle * M_PI / 180);
		cylinderY += .45 * sin(cylinderAngle * M_PI / 180);

		Cylinder* cylinder = new Cylinder(cylinderX, cylinderY, cylinderZ, cylinderAngle, 0, 0, .01, radius);
		models.push_back(cylinder);
	}
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Hoop::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = 0;
	xyzLimits[1] = 28.56;
	xyzLimits[2] = 0;
	xyzLimits[3] = 15.24;
	xyzLimits[4] = 0;
	xyzLimits[5] = .01;
}

void Hoop::render()
{
	for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
		(*it)->render();
}
