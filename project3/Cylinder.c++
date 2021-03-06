// Cylinder.c++

#include <iostream>
#include <math.h>

#include "Cylinder.h"

Cylinder::Cylinder(float x, float y, float z, float rotx, float roty, float rotz, float length, float radius) : displayCylEdges(false), displayCylFill(true)
{
	defineCylinder(x, y, z, rotx, roty, rotz, length, radius);
}

Cylinder::~Cylinder()
{
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}

const int N_POINTS_AROUND_SLICE = 18; // number points around a cross-section

void Cylinder::defineCylinder(float x, float y, float z, float rotx, float roty, float rotz, float length, float radius)
{
	typedef float vec3[3];
	int nPoints = 2 * (N_POINTS_AROUND_SLICE + 1);
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];

	cryph::Matrix4x4 translate = cryph::Matrix4x4::translation(cryph::AffVector(x, y, z));
	cryph::Matrix4x4 xRot = cryph::Matrix4x4::xRotationDegrees(rotx);
	cryph::Matrix4x4 yRot = cryph::Matrix4x4::yRotationDegrees(roty);
	cryph::Matrix4x4 zRot = cryph::Matrix4x4::zRotationDegrees(rotz);
	cryph::Matrix4x4 final = translate * xRot * yRot * zRot;

	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;
	double yb = 0, zb = 0;
	double x1 = 0, x2 = length;
	double r = radius;
	// EXERCISE: Use cryph to generalize this to define a cylinder in
	//           an arbitrary position and orientation.
	for (int i=0 ; i<=N_POINTS_AROUND_SLICE ; i++)
	{
		int j = 2 * i;
		double dy = cos(theta);
		double dz = sin(theta);

		normals[j][0] = 0.0; normals[j][1] = dy; normals[j][2] = dz;
		coords[j][0] = x1; coords[j][1] = yb + r*dy; coords[j][2] = zb + r*dz;
		normals[j+1][0] = 0.0; normals[j+1][1] = dy; normals[j+1][2] = dz;
		coords[j+1][0] = x2; coords[j+1][1] = yb + r*dy; coords[j+1][2] = zb + r*dz;

		theta += dTheta;
	}

	for(int i = 0; i < nPoints; i++)
	{
		(final * cryph::AffPoint(normals[i])).aCoords(normals[i]);
		(final * cryph::AffPoint(coords[i])).aCoords(coords[i]);
	}

	// ************************************************************************
	// EXERCISE: Create/fill VAOs and VBOs here.
	//           Also use glVertexAttribPointer and glEnableVertexAttribArray
	// ************************************************************************
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcPosition);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcNormal);

	delete [] coords;
	delete [] normals;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Cylinder::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -1.0;
	xyzLimits[1] = 1.0;
	xyzLimits[2] = -1.0;
	xyzLimits[3] = 1.0;
	xyzLimits[4] = -1.0;
	xyzLimits[5] = 1.0;
}

void Cylinder::handleCommand(unsigned char key, double ldsX, double ldsY)
{
	if (key == 'c')
		displayCylFill = !displayCylFill;
	else if (key == 'C')
		displayCylEdges = !displayCylEdges;
	else
		this->ModelView::handleCommand(key, ldsX, ldsY);
}

void Cylinder::renderCylinder(float* color)
{
	typedef float vec3[3];
	vec3 cylColor = {1, 140 / 255, 0};
	if (color == NULL)
		color = cylColor;
	glUniform3fv(ppuLoc_kd, 1, color);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));
}

void Cylinder::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderProgram);

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(ppuLoc_mc_ec, 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(ppuLoc_ec_lds, 1, false, ec_lds.extractColMajor(mat));

	float black[] = { 0.0, 0.0, 0.0 };

	if (displayCylFill)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderCylinder(NULL);
	}
	if (displayCylEdges)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderCylinder(black);
	}

	glUseProgram(pgm);
}
