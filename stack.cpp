#include<stdio.h>
#include<iostream>
#include<math.h>
#include "game.h"
#include "stack.h"
#include "game.h"
using namespace std;

Stack::Stack()
{

}

Stack::~Stack()
{
	//while (top())
  //{
    //delete pop();
  //y}
}


void Stack::push(CheckersBoard* inData)
{
  Node* temp;
  temp = pTop;
  pTop = new Node;
  pTop->pNext = temp;
  pTop->data = inData;
  length++;
  //cout<<"Pushed: "<<current->pNext->data<<"\n";
}
CheckersBoard* Stack::pop()
{
  Node* fart;
	fart = pTop;
  pTop = pTop->pNext;
  length--;
  return fart->data;
  //cout<<"Popped\n";
}

CheckersBoard* Stack::top()
{
	return pTop->data;
}

bool Stack::empty()
{
	if(pTop == NULL)
    return true;
  else
    return false;
}

/*void Stack::display()
{
	//cout<<endl;
	Node *p1;
	p1 = pTop;
	while (p1 != NULL)
	{
		cout<< ((Board*)(p1->data))->getSize()<<"; ";
		p1 = p1->pNext;
	}
	cout<<endl;
}*/

