#include <iostream>
#include <fstream>
#include <string>
#include "Services.h";
#include "Stack.h";

using namespace std;

Services::Services(){
	head =nullptr;
	rear=nullptr;
}

void Services::clearServices(){ /// destructor but as function

	if(head!=nullptr){
		commandNode *currCommand = head->commands, *temp;

		while(head!=nullptr){
			while(currCommand!= nullptr){
				temp=currCommand;
				currCommand=currCommand->next;
				delete temp;
			}
			rear=head; /// since already deleting data, rear used as temp
			head=head->next;   /// going next function
			delete rear;
		}
	}
}

void Services::addFunction(string filename){ ///// adds the function (service) in the given file (file already checked)
	fstream input;
	string function, command, object;
	commandNode *ptr; // current command node;
	input.open(filename.c_str());
	
	input >> function; /// taking first function name
	function.pop_back();

	input >> command; // first command
	input >> object;
	object.pop_back();

	ptr=new commandNode(command, object, function, nullptr);

	if(head==nullptr){ // if first function
		head = new functionNode(function ,nullptr ,ptr);
		rear= head;
	}
	else{
		rear->next= new functionNode(function, nullptr,ptr);
		rear=rear->next;
	}

	while(input >> command){ /// taking command and object and adding 
		input >> object;
		object.pop_back();

		ptr->next = new commandNode(command, object, function, nullptr);
		ptr=ptr->next;
	}

	input.close(); /// close input document
}

void Services::display(){ //// displays all services

	cout <<"-------------------------------------------------------------------"<<endl;
	cout <<"PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS"<<endl;
	cout <<"-------------------------------------------------------------------"<<endl<<endl<<endl;

	functionNode *currFunction = head;
	commandNode *currCommand;

	while(currFunction!=nullptr){
		cout << currFunction->functionName<<endl;
		currCommand=currFunction->commands;
		while(currCommand!=nullptr){
			cout << currCommand->command <<" " << currCommand->object;
			if(currCommand->next != nullptr)
				cout << ", ";
			else
				cout << "."<<endl<<endl;
			currCommand=currCommand->next;
		}
		currFunction=currFunction->next;
	}
}



functionNode * Services::findFunction(string function){ 
	// pre condition function name
	// post condition location of function in data structure
	
	functionNode *currFunc=head;

	while (currFunc!= nullptr){
		if(currFunc->functionName == function){
			return currFunc;
		}
		currFunc=currFunc->next;
	}
	return nullptr;
}