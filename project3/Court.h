// TEMPLATE_Subclass.h

#ifndef COURT_H
#define COURT_H

#include "ModelViewWithPhongLighting.h"
#include <vector>

class Court : public ModelViewWithPhongLighting
{
public:
	Court();
	virtual ~Court();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;

	void setMinsMaxes(float cx, float cy, float cz, float lx, float ly, float lz);

	void create();
	std::vector<ModelView*> models;

};

#endif
