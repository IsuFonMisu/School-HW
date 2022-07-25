#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct queueNode{
	string prof, request;
	int ID;

	queueNode(){

		prof = "";
		request = "";
		ID = -1;
	}

	queueNode(string name, string function, int profID){

		prof = name;
		request = function;
		ID = profID;

	}
};

class Queue{

private:
	int front, rear,  elements, size;
	queueNode* queueArray;

public:

	Queue(int);

	void enqueue(string, string, int); /// add new item to rear
	void dequeue(string&, string&, int&);   /// take item from front
	bool isEmpty(); /// true if if empty
	bool isFull(); /// true if full
	void clear();  // clear dynamically allocated memory
};

