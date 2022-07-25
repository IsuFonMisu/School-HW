#include <iostream>
#include <string>
#include "DynQueue.h"
using namespace std;

//// taken from lecture codes (modified)


//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynQueue::DynQueue()
{
	front = nullptr;
	rear = nullptr;   

}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynQueue::enqueue(int ID, string name, string function)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(ID, name, function);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(ID, name, function);
		rear = rear->next;
	} 

}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynQueue::dequeue(int &ID, string &name, string &function)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		ID = front->ID;
		function=front->function;
		name = front -> name;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynQueue::isEmpty() const
{
	if (front == nullptr)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynQueue::clear()
{
	int value;   // Dummy variable for dequeue
	string a , b;
	while(!isEmpty())
		dequeue(value, a,b); //delete all elements

}