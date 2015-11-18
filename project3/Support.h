// TEMPLATE_Subclass.h

#ifndef SUPPORT_H
#define SUPPORT_H

#include "ModelViewWithPhongLighting.h"

class Support : public ModelViewWithPhongLighting
{
public:
	Support(bool isNear);
	virtual ~Support();

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
	float horizModifier;
	float dAngle;
};

#endif
