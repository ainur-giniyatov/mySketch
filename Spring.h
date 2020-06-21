#pragma once
#include "Obj.h"

class Spring
{
public:
	Spring();
	void setObjects(Obj* obj1, Obj *obj2) {
		this->obj1 = obj1;
		this->obj2 = obj2;
	}

	void setLength(float l) { length = l; }
	void draw();
	void step();
	

private:
	Obj *obj1;
	Obj* obj2;

	//float decay = 0.5;
	float stiffness = 2.5;
	float length = 50;
	float deformation_level = 0;
	bool torn = false;
	float strength = 0;
};

