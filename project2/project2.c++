// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "MandM.h"
#include "Block.h"
#include "Court.h"
#include "Goal.h"
#include "Cylinder.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);
	// Set values for eye-center-up to produce a reasonable off-axis
	// view of your scene, then:

	// Notify the ModelView of our MC->EC viewing requests:

	double ecZpp, ecZmin, ecZmax;

	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);
	cryph::AffPoint center(15.5, 7.62, 2.5);

	// 2:
	double maxDelta = xyz[1] - xyz[0];
	double delta = xyz[3] - xyz[2];
	if (delta > maxDelta)
		maxDelta = delta;
	delta = xyz[5] - xyz[4];
	if (delta > maxDelta)
		maxDelta = delta;

	double distEyeCenter = 2.0 * maxDelta;
	cryph::AffPoint eye(30, -30, 15);

	// 3:
	cryph::AffVector up(0, 0, 1);

	ecZpp = -(distEyeCenter - 0.5*maxDelta);
	// ecZmin = ecZpp - maxDelta;
	// ecZmax = ecZpp + 0.5*maxDelta;

	ecZmin = -(distEyeCenter + 30);
	ecZmax = -0.01;

	ModelView::setEyeCenterUp(eye, center, up);
	// Set values for ecZpp, ecZmin, ecZmax that make sense in the context of
	// the EC system established above, then:

	ModelView::setProjection(PERSPECTIVE);
	ModelView::setProjectionPlaneZ(ecZpp);
	ModelView::setECZminZmax(ecZmin, ecZmax);
}

int main(int argc, char* argv[])
{
	GLFWController c("The place of ballers", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	// create your scene, adding things to the Controller....

	// float courtColor[] = { 230.0 / 255.0, 183.0 / 255.0, 55.0 / 255.0 };
	// Block* court = new Block(0, 0, 0, 28.65, 15.24, .01, courtColor);
	// c.addModel(court);
	//
	// float black[] = {0, 0, 0};
	// Block* centerLine = new Block(14.325, 0, 0.01, .0508, 15.24, .01, black);
	// c.addModel(centerLine);

	Court* court = new Court();
	c.addModel(court);

	Goal* nearGoal = new Goal(true);
	c.addModel(nearGoal);

	Goal* farGoal = new Goal(false);
	c.addModel(farGoal);



	glClearColor(.7, .7, .7, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
