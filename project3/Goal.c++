#include "Goal.h"
#include "ShaderIF.h"
#include "Block.h"
#include "Cylinder.h"
#include "Support.h"
#include "Hoop.h"

Goal::Goal(bool isNear)
{
	this->isNear = isNear;
	if(isNear)
	{
		xModifier = 26.21;
		innerSquareModifier = .0137;
		outerSquareModifier = .0227;
	} else
	{
		xModifier = 0;
		innerSquareModifier = 0;
		outerSquareModifier = 0;
	}
	create();
}

Goal::~Goal()
{
}

void Goal::create()
{
	float white[] = {1, 1, 1};
	float red[] = {1, 0, 0};
	float backboardThickness = 0.0127;

	Block* backboard = new Block(1.22 + xModifier, 6.705, 2.84, backboardThickness, 1.83, 1.07, white);
	models.push_back(backboard);

	Block* outerSquare = new Block(1.22 + xModifier + backboardThickness - outerSquareModifier, 7.315, 2.84, .001, .61, .46, red);
	models.push_back(outerSquare);

	Block* innerSquare = new Block(1.22 + xModifier + backboardThickness - innerSquareModifier, 7.3404, 2.84, .01, .5592, .4346, white);
	models.push_back(innerSquare);

	Support* support = new Support(isNear);
	models.push_back(support);

	Hoop* hoop = new Hoop();
	models.push_back(hoop);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Goal::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = 0;
	xyzLimits[1] = 28.56;
	xyzLimits[2] = 0;
	xyzLimits[3] = 15.24;
	xyzLimits[4] = 0;
	xyzLimits[5] = .01;
}

void Goal::render()
{
	for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
		(*it)->render();
}
