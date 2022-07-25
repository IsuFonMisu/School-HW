#include <string>
#include <iostream>

using namespace std;

#ifndef SHAPE_H
#define SHAPE_H

class shape{

public:
	shape(string name): myName(name) {};
	virtual ~shape(){};


	virtual float perimeter()  = 0;
	virtual float area()  = 0;
	virtual float volume()  = 0;

	string getName(){return myName;};
	

protected:

	string myName;

};

#endif