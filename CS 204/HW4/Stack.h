#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>
using namespace std;
struct stackNode{
	string function;
	string command;
	string obj;
	stackNode *next;  
	stackNode::stackNode(string functionName,string commandName, string objx, stackNode *ptr=nullptr){
		function = functionName;
		command=commandName;
		next=ptr;
		obj=objx;
	}
};


class DynStack{

private:
	stackNode *top;

public:

	DynStack();

	void push(string, string, string);    //// adding new item to the top
	void pop(string&, string&, string&);  //// raking item from the top

	bool isEmpty();   // true if empty
};

#endif