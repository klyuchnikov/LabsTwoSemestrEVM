
#include "stdafx.h"
/*
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "fstream.h"
#include <time.h>

using namespace std;

#define N 2

struct page;

struct item
{
	int key;
	page *p;
	int count;
};
struct page
{
	int m;
	page *p0;
	item *e[N * 2];
};

page *root, *q;
int x;
bool h;
item *u;

void insert(int x, page *a, bool h, item *&v, int &r)
{
	page *b;
	if (a->m < N)
	{
		a->m++;
		h = false;
		for (int i = a->m; i > r +  2; i++)
			a->e[i] = a->e[i - 1];
		a->e[r + 1] = u;
	}
	else
	{
		b = new page;
		if (r <= N)
		{
			if (r = N)
				v = u;
			else
			{
				v = a->e[N];
				for (int i = a->m; i > r +  2; i++)
					a->e[i] = a->e[i - 1];
				a->e[r + 1] = u;
			}
			for (int i = 1; i < N; i++)
				b->e[i] = a->e[i + N];
		}
		else
		{
			r = r - N;
			v = a->e[N + 1];
			for (int i = 1; i <= r - 1; i++)
				b->e[r] = a->e[i + N + 1];
			b->e[r] = u;
			for (int i = r + 1; i<= N; i++)
				b->e[i] = a->e[i + N];
		}
		a->m = N;
		b->m = N;
		b->p0 = v->p;
		v->p = b;
	}
}
void search(int x, page *a, bool h, item *&v)
{
	int k = 0, l = 0, r = 0;
	page *q;
	item *u;

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
			k = (int)(l + r) / 2;
			if (x <= a->e[k]->key)
				r = k - 1;
			if (x >= a->e[k]->key)
				l = k + 1;
		} while (r >= l);
		if (l - r > 1)
		{
			a->e[k]->count = a->e[k]->count + 1;
			h = false;
		}
		else
		{
			if (r == 0)
				q = a->p0;
			else
				q = a->e[r]->p;
			search(x, q, h, u);
			if (h == true)
				insert(x, q, h, v, r);
		}
	}
}
void printtree(page *p, int l)
{
	if (p != NULL)
	{
		for (int i = 1; i < l; i++)
			cout << " ";
		for (int i = 1; i < p->m; i++)
			cout << p->e[i]->key << "  ";
		cout << endl;
		printtree(p->p0, l + 1);
		for (int i = 1; i < p->m; i++)
			printtree(p->e[i]->p, l + 1);
	}
}
void main()
{
	root = NULL;
	int x;
	cin >> x;
	while (x != 0)
	{
		cout << "search key" << x;
		search(x, root, h, u);
		if (h == true)
		{
			q = root;
			root = new page;
			root->m = 1;
			root->p0 = q;
			root->e[1] = u;
		}
	printtree(root, 1);
	cin >> x;
	}
}

*/