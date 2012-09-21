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
void clear(elem *&head)
{
	while(head != NULL)
	{
		elem *cur = head;
		head = head->next;
		delete cur;
  }
}

void destroy(elem *head)
{
	clear(head);
	delete head;
}

void print(elem *&head)
{
	for(elem *p = head; p != NULL; p = p->next)
		cout << p->val << " ";
}

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	elem *head = NULL;
	char ch;
	do
	{
		int el;
		cout << "input:";
		cin >> el;
		add(head, el);
		ch = getch();
	} while (ch != 27);
	print(head);
	int e;
	cin >> e;
	add(head, 2345);
	print(head);
	clear(head);
	destroy(head);
	getch();
}