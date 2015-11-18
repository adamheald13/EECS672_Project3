// TEMPLATE_Subclass.h

#ifndef GOAL_H
#define GOAL_H

#include "ModelViewWithPhongLighting.h"

class Goal : public ModelViewWithPhongLighting
{
public:
	Goal(bool isNear);
	virtual ~Goal();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	bool isNear;
	void create();
	float xModifier;
	float innerSquareModifier;
	float outerSquareModifier;
	std::vector<ModelView*> models;
};

#endif
