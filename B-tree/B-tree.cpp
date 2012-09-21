#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "fstream.h"
#include <time.h>
#include <math.h>

using namespace std;

#define N 10

struct page;

struct item
{
	double key;
	page *p;
	int count;
};

struct page 
{
	long int m;
	item *e[N * 2 + 1];
};

void insert(page *&a, bool &h, item *&v, int &r, item *&u)
{
	if (a->m < N * 2) 
	{
		a->m++;
		h = false;
		for (int i = a->m; i >= r + 2; i--)
			a->e[i] = a->e[i - 1];
		a->e[r + 1] = u;
	}
	else
	{
		delete v;
		page *b = new page;
		if (r <= N)
		{
			if (r == N)
				v = u;
			else
			{
				v = a->e[N];
				for (int i = N; i >= r + 2; i--)
					a->e[i] = a->e[i - 1];
				a->e[r + 1] = u;
			}
			for (int i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
		}
		else
		{
			r = r - N;
			v = a->e[N + 1];
			for (int i = 1; i <= r - 1; i++)
				b->e[i] = a->e[i + N + 1];
			b->e[r] = u;
			for (int i = r + 1; i<= N; i++)
				b->e[i] = a->e[i + N];
		}
		a->m = N;
		b->m = N;
		b->e[0] = new item;
		b->e[0]->p = v->p;
		v->p = b;
	}
}

void search(int x, page *a, bool &h, item *&v)
{
	int k = 0, l = 0, r = 0;
	if (a == NULL)
	{
		h = true;
		v->key = x;
		v->count = 1;
		v->p = NULL;
	}
	else
	{
		l = 1;
		r = a->m;
		do 
		{
			k = (int)((l + r) / 2);
			if (x <= a->e[k]->key)
				r = k - 1;
			if (x >= a->e[k]->key)
				l = k + 1;
		} while (r >= l);
		if (l - r > 1)
		{
			a->e[k]->count++;
			h = false;
		}
		else
		{
			page *q;
			if (r == 0)
				q = a->e[0]->p;
			else
				q = a->e[r]->p;
			item *u = new item;
			search(x, q, h, u);
			if (h == true)
				insert(a, h, v, r, u);
			else
				delete u;
		}
	}
}

int res = 0;
void printtree(page *p, int l)
{
	if (p != NULL)
	{
		res += p->m;
		for (int i = 1; i <= l; i++)
				cout << "  ";
		for (int i = 0; i <= p->m; i++)
			printtree(p->e[i]->p, l + 1);
		cout << endl;
		for (int i = 1; i <= p->m; i++)
		{
		//	printtree(p->e[i - 1]->p, l + 1);
			cout << "(" << l << ") " << p->e[i]->key << "  ";
			
		//	if (i == p->m)
		//		printtree(p->e[i]->p, l + 1);
		}
	}
}

void clear(page *p)
{
	if (p != NULL)
	{
		for (int i = 0; i <= p->m; i++)
		{
			clear(p->e[i]->p);
			delete p->e[i];
			p->e[i] = NULL;
		}
		delete p;
	}
}

void add(long int key, page *&root)
{
	bool h = false;
	item *u = new item;
	//cout << "search key" << " " << key << endl;
	search(key, root, h, u);
	if (h == true)
	{
		page *q = root;
		root = new page;
		root->m = 1;
		root->e[0] = new item;
		root->e[0]->p = q;
		root->e[1] = u;
	}
	else
	{
		delete u;
		u = NULL;
	}
//	printtree(root, 1);
	//cout << endl;
}
long int random(int min, int max)
{
	return rand() * max / RAND_MAX + min;
}
void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	page *root = NULL;
	cout << endl;
	for (int i = 0; i < 100000; i++)
		add((i * i) * rand(), root);
  printtree(root, 1);
	//for (int i = 0; i < 10; i++)
	//	dell(i, root);
	cout << res;
	_getch();
	clear(root);
	root = NULL;
	
}
