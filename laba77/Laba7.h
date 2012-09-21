#ifndef laba7
#define laba7
#include "stdafx.h"
#include <conio.h>
#include <iostream>
using namespace std;

const char enableEN[] = "qwertyuiopasdfghjklzxcvbnm0123456789QWERTYUIOPLKJHGFDSAZXCVBNM ";

struct Elem
{
	int val;
	Elem *next;
};

struct List_1
{
	Elem *head;

	void create()
	{
		head = NULL;
	}

	void add(int _val)
	{
		Elem *newelem = new Elem;
		newelem->val = _val;
		newelem->next = head;
		head = newelem;
	}

	void clear()
	{	
		while(head != NULL)
		{
			Elem *cur = head;
			head = head->next;
			delete cur;
		}
		head = NULL;
	}

	bool delElem(int ind)
	{
		if (ind <= 0 || head == NULL)
			return false;
		if (ind == 1)
		{
			Elem *tmp = head->next;
			delete head;
			head = tmp;
			return true;
		}
		Elem *p = head;
		int i = 2;
		while (p->next != NULL)
		{
			if (i == ind)
			{
				Elem *del = p->next;
				p->next = del->next;
				delete del;
				return true;
			}
			p = p->next;
			i++;
		}
		return false;
	}

	bool task()
	{
		if (head == NULL) 
			return false;
		int i = 1, res = 1, temp = head->val;
		res = (temp % 2 == 0) ? 1 : 0;
		Elem *p = head->next;
		while(p != NULL)
		{
			i++;
			if ((temp % 2 == 0 ? (p->val > temp) : (p->val % 2 == 0)) && (p->val % 2 == 0))
			{
				temp = p->val;
				res = i;
			}
			p = p->next;
		}
		if (temp % 2 == 0)		
			return delElem(res);
		return false;
	}
};
bool str(char *&name)
{
	bool f = false;
	int i = 0;
	while(true)
	{
		if (name[i] == ' ')
			return true;
		if (strchr(enableEN, name[i]) == NULL)
		{
			name[i] = '\0';
			return false;
		}
		i++;
	}
}
#endif