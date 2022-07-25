
#ifndef THREEDSHAPE_H
#define THREEDSHAPE_H

#include "Shape.h"

class ThreeDShape : public shape{

public:
	ThreeDShape(string name):shape(name){};
	
	virtual ~ThreeDShape(){};

	float perimeter(){return 0;}

};

class Box : public ThreeDShape{
public:

	Box(string name, float l, float w, float h):ThreeDShape(name), length(l), width(w), height(h){};
	~Box(){};
	
	float volume();
	float area();

private:

	float width, length, height;

};

float Box::volume(){return  width*length*height;}
float Box::area(){return 2*(width*length+width*height+length*height);}

#endif