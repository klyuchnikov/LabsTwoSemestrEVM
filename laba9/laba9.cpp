// laba9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;

const char enableEN[] = "1234567890-";

struct Tree
{ 
	int  key;
	Tree *left;
	Tree *right;
};

Tree *root;

void init()
{
	root = NULL;
}

void clearElem(Tree *&root)
{
	if (root == NULL)
		return;
	clearElem(root->left);
	clearElem(root->right);
	delete root;
}

void clear()
{
	clearElem(root);
	root = NULL;
}

void viewElem(Tree *&tree, int level)
{
	if (tree == NULL)  
		return;
	viewElem(tree->right, level + 1);
	for (int i = 0; i < level * 4 + 2; i++)
		cout << " ";
	cout << "--" << tree->key << endl;
	viewElem(tree->left, level + 1);
}

void view()
{
	viewElem(root, 0);
	getch();
}

void addElem(Tree **root, int elem)
{
	if (*root == NULL)
	{
		Tree *ins = new Tree;
		ins->key = elem;
		ins->left = NULL;
		ins->right = NULL;
		*root = ins;
	}
	else if (elem < (*root)->key)
		addElem(&(*root)->left, elem);
	else if (elem > (*root)->key)
		addElem(&(*root)->right, elem);
}
void twip(char *&str)
{
	if (str[0] != '0')
	{
		if (str[0] != '-' && str[1] == '0')
			return;
		if (str[1] != '0')
			return;
	}
	int size = strlen(str);
	char *temp = new char[size];
	int i;
	int k;
	if (str[0] == '-')
	{
		i = 1;
		k = 1;
		temp[0] = '-';
	}
	else
	{
		i = 0;
		k = 0;
	}
	bool flag = false;
	while (i < size)
	{
		if (flag == false)
		{
			if (str[i] == '0')
			{

				i++;
				continue;
			}
		}
		flag = true;
		temp[k] = str[i++];
		k++;
	}
	temp[k] = '\0';
	delete str;
	str = temp;
}
void add()
{
	int  n = 0;
	
	char ch = 0;
	int k = 0;
	do 
	{
		char *str = new char[15];
		bool flag = false;
		cout << "Add: input element: ";
		while (true)
		{
			ch = _getch();
			if (ch == 13)
			{
				str[k] = '\0';
				cout << endl;
				k = 0;
				twip(str);
				if (strlen(str) > ((str[0] == '-') ? 10 : 9))
					break;
				n = atoi(str);
				break;
			}
			if (strchr(enableEN, ch) != NULL)
			{
				if (ch == '-' && (flag == true || k != 0))
					continue;
				if (ch == '-')
					flag = true;
				str[k++] = ch; 
				cout << ch;
			}			
		}
		delete str;
	} while (n == 0);

	addElem(&root, n);
}

void replaceRightmost(Tree **root, Tree **right)
{
	if ((*right)->right != NULL)
		replaceRightmost(root, &(*right)->right);
	else
	{
		Tree *newRoot = *right;
		*right = (*right)->left;

		newRoot->left = (*root)->left;
		newRoot->right = (*root)->right;
		delete *root;
		*root = newRoot;
	}
}

void delElem(Tree **root, int elem)
{
	if (*root == NULL) 
		return;
	if ((*root)->key == elem)
	{
		if (((*root)->left == NULL) && ((*root)->right == NULL)  ) {
    		delete *root;
	    	*root = NULL;
		} else if ((*root)->right == NULL){
			Tree *del = *root;
			*root = (*root)->left;
			delete del;
		} else if ((*root)->left == NULL){
			Tree *del = *root;
			*root = (*root)->right;
			delete del;
		} else {
			replaceRightmost(root, &(*root)->left);
		}
		return;

	}
	if (elem < (*root)->key)
		delElem(&(*root)->left, elem);
	else if (elem > (*root)->key)
		delElem(&(*root)->right, elem);
}

void del()
{
	int  n = 0;

	char ch = 0;
	int k = 0;
	do 
	{
		char *str = new char[150];
		bool flag = false;
		cout << "Del: input element: ";
		while (true)
		{
			ch = _getch();
			if (ch == 13)
			{
				str[k] = '\0';
				cout << endl;
				k = 0;
				twip(str);
				if (strlen(str) > ((str[0] == '-') ? 10 : 9))
					break;
				n = atoi(str);
				break;
			}
			if (strchr(enableEN, ch) != NULL)
			{
				if (ch == '-' && (flag == true || k != 0))
					continue;
				if (ch == '-')
					flag = true;
				str[k++] = ch; 
				cout << ch;
			}
		}
		delete str;
	} while (n == 0);
	delElem(&root, n);
}

bool findElem(Tree *&root, int elem)
{
	if (root == NULL) 
		return  false;
	if (elem == root->key)
		return true;
	if (elem < root->key)
		return findElem(root->left, elem);
	else
		return findElem(root->right, elem);
}

void find()
{
	int  n = 0;

	char ch = 0;
	int k = 0;
	do 
	{	
		char *str = new char[150];
		bool flag = false;
		cout << "Find: input element: ";
		while (true)
		{
			ch = _getch();
			if (ch == 13)
			{
				str[k] = '\0';
				cout << endl;
				k = 0;
				twip(str);
				if (strlen(str) > ((str[0] == '-') ? 10 : 9))
					break;
				n = atoi(str);
				break;
			}
			if (strchr(enableEN, ch) != NULL)
			{
				if (ch == '-' && (flag == true || k != 0))
					continue;
				if (ch == '-')
					flag = true;
				str[k++] = ch; 
				cout << ch;
			}
		}
		delete str;
	} while (n == 0);
	if (findElem(root, n))
		printf("Element find!\n");
	else
		printf("Element not find!\n");
	getch();
}

void  menu()
{
	char c;
	do
	{
		printf("1: View\n");
		printf("2: Find\n");
		printf("3: Add\n");
		printf("4: Del\n");
		printf("5: Clear\n");
		printf("\nEsc: Exit\n");
		c = getch();
		switch(c)
		{
		case '1': view(); break;
		case '2': find(); break;
		case '3': add(); break;
		case '4': del(); break;
//		case '5': clear(); break;
		}
	} while(c != 27);
}

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	init();
	menu();
	clear();
}
