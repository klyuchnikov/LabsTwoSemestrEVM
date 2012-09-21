#include "stdafx.h"
#include <conio.h>
#include <iostream>
using namespace std;

struct elem
{
	int val;
	elem *next;
};

void add(elem *&head, int _val)
{
	elem *newelem = new elem;
	newelem->val = _val;
	newelem->next = head;
	head = newelem;
}
void destroy(elem *&head)
{
	while(head != NULL)
	{
		elem *cur = head;
		head = head->next;
		delete cur;
  }
}

void main()
{
		 
}