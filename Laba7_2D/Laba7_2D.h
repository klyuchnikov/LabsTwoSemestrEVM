#ifndef laba
#define laba
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;


struct Person
{
	char *FirstName;
	char *Name;
};

struct Elem2
{
	Elem2 *prev;
	Elem2 *next;
	Person key;
};

class List_2
{
public:
	Elem2 *head;
	Elem2 *tail;
	List_2()
	{
		head = NULL;
		tail = NULL;
	}

	void addToHead(char *fname, char *name)
	{
		Elem2 *el = new Elem2;
		el->key.FirstName = fname;
		el->key.Name = name;

		el->prev = NULL;
		el->next = head;		

		if (head == NULL)
			tail = el;
		else
		{
			head->prev = el;
		}
		head = el;

	}
	void addToTail(char *fname, char *name)
	{
		Elem2 *el = new Elem2;
		el->key.FirstName = fname;
		el->key.Name = name;

		el->prev = tail;
		el->next = NULL;		

		if (tail == NULL)
			head = el;
		else
		{
			tail->next = el;
		}
		tail = el;

	}


	void delFromTail()
	{
		if (tail == NULL) 
			return;
		Elem2 *del = tail;
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			tail = tail->prev;
			tail->next = NULL;
		}
		delete del;
	}

	void delFromHead()
	{
		if (head == NULL) 
			return;
		Elem2 * del = head;
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			head = head->next;
			head->prev = NULL;
		}
		delete del;
	}
	bool delInd(int value)
	{
		if ((value < 1) || (head == NULL))  
			return false;
		if (value == 1)
		{
			delFromHead();
			return true;
		}
		int n = 1;
		Elem2 *p = head;
		while (p != NULL)
		{
			if (n == value)
			{
				if (p == tail)
				{
					delFromTail();
					return true;
				}
				Elem2 *prev = p->prev;
				Elem2 *next = p->next;

				prev->next = next;
				next->prev = prev;

				delete p;

				return true;
			}
			p = p->next;
			n++;
		}
		return false;
	}

	void printNext()
	{
		Elem2 *p = head;
		if (p == NULL)
		{
			cout << "end";
			getch();
			return;
		}
		else
			cout << "Print:" << endl;
		while (p != NULL)
		{
			cout << p->key.FirstName << "  " << p->key.Name << endl;
			p = p->next;
		}
	}	
	void printBack()
	{
		Elem2 *p = tail;
		if (p == NULL)
		{
			cout << "end";
			getch();
			return;
		}
		else
			cout << "Print:" << endl;
		while (p != NULL)
		{
			cout << p->key.FirstName << "  " << p->key.Name << endl;
			p = p->prev;
		}
	}
	void clear()
	{
		Elem2 *p = head;
		while (p != NULL)
		{
			Elem2 *del = p;
			p = p->next;
			delete del;
		}
		head = NULL;
		tail = NULL;
	}
};
#endif