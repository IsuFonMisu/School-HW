#ifndef TWODSHAPE_H
#define TWODSHAPE_H

#include "Shape.h"


class TwoDShape: public shape{

public:
	TwoDShape(string name) : shape(name) {};

	virtual ~TwoDShape(){};

};

class Rectangle: public TwoDShape{
public:

	Rectangle(string name, float l, float w): TwoDShape(name), length(l), width(w){};
	~Rectangle(){};

	float area();
	float perimeter();
	float volume() ;


private:
	float width, length;
};

float Rectangle::area(){return width*length;};
float Rectangle::perimeter(){return 2*(width+length);};
float Rectangle::volume() {return 0;};

#endif