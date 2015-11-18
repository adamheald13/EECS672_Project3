// Cylinder.h

#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/gl.h>

#include "ModelViewWithPhongLighting.h"

class Cylinder : public ModelViewWithPhongLighting
{
public:
	Cylinder(float x, float y, float z, float rotx, float roty, float rotz, float length, float radius);
	virtual ~Cylinder();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void handleCommand(unsigned char key, double ldsX, double ldsY);
	void render();
private:
	GLuint vao[1];
	GLuint vbo[2]; // 0: coordinates; 1: normal vectors

	bool displayCylEdges, displayCylFill;

	void defineCylinder(float x, float y, float z, float rotx, float roty, float rotz, float length, float radius);
	void renderCylinder(float* color);
};

#endif
