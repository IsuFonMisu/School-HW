#ifndef SERVICES_H
#define SERVICES_H

#include <iostream>
#include <string>
using namespace std;
struct commandNode {

	string command, object, function;

	commandNode* next;

	commandNode(string xCommand, string xObject, string xFunction, commandNode * nextNode){
		
		command = xCommand;
		object = xObject;
		function = xFunction;
		next= nextNode;
	}
};

struct functionNode{

	string functionName;

	functionNode *next;
	commandNode *commands;

	functionNode(string name, functionNode *nextNode, commandNode *command){

		functionName = name;
		next= nextNode;
		commands=command;
	}
};


class Services{

private:
	
	functionNode *head;
	functionNode *rear;


public:

	Services();
	void addFunction(string); // adds new function with given input file
	void display(); //displays services(functions) with commands in it

	void clearServices(); /// clears dynamically allocated memory

	functionNode *findFunction(string);  //  return adress of given function
};



#endif