#include <iostream>
#include <string>
#include "Stack.h"


using namespace std;

DynStack::DynStack(){

	top = nullptr;

}

bool DynStack::isEmpty(){    // if emtpy -> true
	if(top == nullptr)
		return true;
	else
		return false;
}

void DynStack::push(string function, string command, string obj){   // adds new item to top

	top=new stackNode(function, command, obj, top);

}

void DynStack::pop(string& function, string& command, string& object){  /// takes item from top

	if(!isEmpty()){
		function = top->function;
		command= top->command;
		object= top->obj;

		stackNode* temp = top;
		top = top->next;
		delete temp;
	}
	else{

		cout << "Attempting to pop from empty stack, exiting program...\n";
		exit(1);

	}
}