#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "fstream.h"
#include <time.h>

using namespace std;

#define N 10 // степень дерева

class B_tree
{
public:
	B_tree()
	{
		root = new Page;
		root->n = 0;
		for (int i = 0; i < 2 * N; i++)
			root->son[i] = NULL;
		pagenum = 0;
	}
	bool add(int key)
	{
		if (root->n == 0)
		{
			root->n++;
			root->key[0] = key;
			pagenum++;
			return true;
		}
		Page *p = root;
		bool find = false;
		while (!find)
		{
			if (p->key[0] == key)
				return false;
			if (key < p->key[0])
			{
				if (p->son[0] != NULL)
				{
					p = p->son[0];
					continue;
				}
				else
				{
					find = true;
					break;
				}
			}
			for (int i =  1; i < p->n; i++)
			{
				if (key == p->key[i])
					return false;
				if (key > p->key[i - 1] && key > p->key[i])
				{
					if (p->son[i] != NULL)
						p = p->son[i];
					else
						find = true;
				}
			}
			int last = p->n - 1;
			if (key > p->key[last]) 
			{
				if (p->son[last + 1] != NULL)
				{
					p = p->son[last + 1]; 
					continue;
				}
				else 
				{
					find = true;
					break;
				}
			}		
		}
		addRec(p, NULL, key);
		pagenum++;
		return true;
	}
	
	void search(int key)
	{}

private:
	struct Page
	{
		Page *son[2 * N + 1];
		int key[2 * N];
		int n;
	};
	int pagenum;
	Page *root;
	void addRec(Page *p, Page *shift, int key)
	{
		int ind = 0;
		for (int i = 0; i < p->n - 1; i++) 
		{
			if (key > p->key[i] && key < p->key[i + 1]) 
			{
				ind = i + 1;
				break;
			}
		}
		if (key > p->key[p->n - 1]) 
			ind = p->n;
		p->son[p->n + 1] = p->son[p->n]; 
		for (int i = p->n; i >= ind + 1; i--) 
		{ 
			p->key[i] = p->key[i - 1];
			p->son[i] = p->son[i - 1];
		}
		p->key[ind] = key;
	//	p->son[ind] = pleft;
		p->n++;
		//if (p->n > )

	}
};
