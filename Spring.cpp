#include "ofGraphics.h"
#include "ofMath.h"
#include "Spring.h"

Spring::Spring()
{
	strength = ofRandom(4) + 1;
}

void Spring::draw()
{
	if (torn)
		return;

	float r = deformation_level > 1.0 ? 1.0 : deformation_level;
	ofSetColor(100 + r * 155, 100, 100);
	ofDrawLine(obj1->getCoord(), obj2->getCoord());
}

void Spring::step()
{
	if (torn)
		return;

	auto v = (obj1->getCoord() - obj2->getCoord());
	float dl = v.length() - length;
	ofVec2f force = v.getNormalized() * dl * stiffness;

	obj1->applyForce(-force);
	obj2->applyForce(force);

	deformation_level = dl / length;

	//if (fabs(deformation_level) > strength)
	//	torn = true;
}
