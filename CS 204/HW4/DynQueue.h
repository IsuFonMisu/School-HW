#ifndef DYNQUEUE_H
#define DYNQUEUE_H
#include <iostream>
#include <string>
//// taken from lecture codes (modified)

using namespace std;
struct QueueNode
{
	int ID;
	string function, name;
	QueueNode *next;
	QueueNode(int studentID, string studentName, string request, QueueNode *ptr = NULL)
	{
		ID = studentID;
		name = studentName;
		function = request;
		next = ptr;
	}
};

class DynQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	DynQueue();
	
	// Member functions.
	void enqueue(int,string, string);
	void dequeue(int &,string &, string &);
	bool isEmpty() const;     
	void clear();
};
#endif