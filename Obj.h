#pragma once
#include <ofVec2f.h>

class Obj
{
public:
	Obj();

	void draw();
	void step();
	void setCoord(const ofVec2f& coord) {
		this->coord = coord;
	}

	void moveTo(const ofVec2f& coord);

	const ofVec2f &getCoord() { return coord; }
	void setAnchored(bool anchored) { this->anchored = anchored; }
	void setRadius(float r) { radius = r; }
	void applyForce(const ofVec2f& force);
	void resetForce() { applied_force = ofVec2f(); }
	bool contains(const ofVec2f& point) { return point.distance(coord) < radius; }
	void startDragging(const ofVec2f& offset);
	void endDragging();

private:
	float mass = 0.012;
	bool anchored = false;
	bool dragged = false;
	ofVec2f coord;
	ofVec2f velocity;
	ofVec2f accel;
	float radius = 10;
	ofVec2f applied_force;
	ofVec2f drag_offset;
};

