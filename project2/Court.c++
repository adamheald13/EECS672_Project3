#include "Court.h"
#include "ShaderIF.h"
#include "Block.h"

Court::Court()
{
	create();
}

Court::~Court()
{
}

void Court::create()
{
	float black[] = {0, 0, 0};
	float courtColor[] = { 230.0 / 255.0, 183.0 / 255.0, 55.0 / 255.0 };
	float blue[] = {0, 0, 1};
	float red[] = {1, 0, 0};

	Block* courtBase = new Block(0, 0, 0, 28.65, 15.24, .01, courtColor);
	models.push_back(courtBase);

	Block* centerLine = new Block(14.3, 0, 0.01, .0508, 15.24, .01, black);
	models.push_back(centerLine);

	Block* outOfBoundsLines = new Block(-1, -1, -.02, 30.65, 17.24, .01, blue);
	models.push_back(outOfBoundsLines);

	Block* farLane = new Block(0, 5.18, 0.01, 4.57, 4.88, .01, red);
	models.push_back(farLane);

	Block* nearLane = new Block(24.08, 5.18, .01, 4.6, 4.88, .01, red);
	models.push_back(nearLane);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Court::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = 0;
	xyzLimits[1] = 28.56;
	xyzLimits[2] = 0;
	xyzLimits[3] = 15.24;
	xyzLimits[4] = 0;
	xyzLimits[5] = .01;
}

void Court::render()
{
	for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
		(*it)->render();
}

void Court::setMinsMaxes(float cx, float cy, float cz, float lx, float ly, float lz)
{
	if(xmin > cx)
	{
		xmin = cx;
	}
	if(xmax < (cx + lx))
	{
		xmax = cx + lx;
	}
	if(ymin > cy)
	{
		ymin = cy;
	}
	if(ymax < (cy + ly))
	{
		ymax = cy + ly;
	}
	if(zmin > cz)
	{
		zmin = cz;
	}
	if(zmax < (cz + lz))
	{
		zmax = cz + lz;
	}
}
