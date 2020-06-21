#include <ofGraphics.h>
#include "Obj.h"


const float dt = 0.015;
const float g = 9.8;
const ofVec2f gravity = ofVec2f(0, 9.78);


Obj::Obj(){

}

void Obj::draw(){
	if (anchored)
		ofSetColor(100, 200, 100);
	else if (dragged)
		ofSetColor(200, 100, 100);
	else
		ofSetColor(200);

	ofDrawCircle(coord, radius);
}

void Obj::step(){
	if (!anchored & !dragged){
		accel = applied_force / mass + gravity;
		velocity += accel * dt;
		coord += velocity * dt;
	}

}

void Obj::moveTo(const ofVec2f& coord)
{

	auto old_coord = this->coord;
	this->coord = coord + drag_offset;
	velocity = (this->coord - old_coord) / dt;
}

void Obj::applyForce(const ofVec2f& force){
	applied_force += (force - velocity * 0.001);
}

void Obj::startDragging(const ofVec2f &offset){
	drag_offset = offset;
	dragged = true;
}

void Obj::endDragging(){
	dragged = false;
}

