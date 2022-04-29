#pragma once
class Stack
{
	struct Node
	{
		class CheckersBoard* data;
		Node *pNext;
    
	};

	

	public:
		Stack();					// Construct stack
    ~Stack();
		void push(class CheckersBoard* inData);	// Add element to top of stack
		class CheckersBoard* pop();				// Return element at top of stack and remove from top
		class CheckersBoard* top();				// Return element at top of stack
		bool empty();
		void display();
     int length = 0;
Node* pTop;

};


