#include <string>
#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue(int sizex){

	front = 0; //// will have data in it
	rear = 0;   /// wont have
	
	queueArray = new queueNode[10];
	size=sizex;
	elements=0;

}

bool Queue::isEmpty(){ // post: true if queue is empty
	return (elements==0);
}

bool Queue::isFull(){ // post: true if queue is full

	return (elements==size);

}

void Queue::enqueue(string profName, string function, int profID){ /// adding new item to queue
		
	queueArray[rear].ID=profID;
	queueArray[rear].request=function;
	queueArray[rear].prof=profName;

	rear=(rear+1)%size;

	elements+=1;


}

void Queue::dequeue(string& profName, string& function, int& profID){  /// taking first item from front

	profName=queueArray[front].prof;
	function=queueArray[front].request;
	profID=queueArray[front].ID;

	front= (front+1)% size;

	elements-=1;

}

void Queue::clear(){ /////

	delete[] queueArray; /// deleting dynamically allocated memory

}
