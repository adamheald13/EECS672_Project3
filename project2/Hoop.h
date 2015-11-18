// TEMPLATE_Subclass.h

#ifndef HOOP_H
#define HOOP_H

#include "ModelViewWithPhongLighting.h"

class Hoop : public ModelViewWithPhongLighting
{
public:
	Hoop();
	virtual ~Hoop();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	void create();
	std::vector<ModelView*> models;
	float cylinderAngle;
	float cylinderX;
	float cylinderY;
	float cylinderZ;
	float radius;
	float dAngle;
};

#endif
