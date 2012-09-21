// Laba10_Hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include "fstream.h"

#pragma warning (disable : 4996)

using namespace std;

#define SLEN 50
#define NHASH  13
#define MULTIPLIER 39
struct Item
{
	char s[SLEN];
	Item *next;
};
class Hash
{
public:
	Item *htable[NHASH];

	Hash()
	{
		for (int i = 0; i < NHASH; i++)
			htable[i] = NULL;
	}

	void clear()
	{
		for (int i = 0; i < NHASH; i++)
			dell(htable[i]);
		cout << "Hash is clean!";
		getch();
	}

	~Hash()
	{
		clear();
	}

	void view()
	{
		for (int i = 0; i < NHASH; i++)
			print(htable[i]);
		getch();
	}

	void add()
	{
		char s[SLEN];
		cout << "\n\n\n\nAdd: ";
		fgets(s, SLEN, stdin);
		addItem(s);
	}

	void del()
	{
		char s[SLEN];

		cout << "\n\n\n\nDel: ";
		fgets(s, SLEN, stdin); 
		delItem(s);
	}

	void find()
	{
		char s[SLEN];
		cout << "\n\n\n\nFind: ";
		fgets(s, SLEN, stdin);
		if (s[strlen(s)-1] == '\n') 
			s[strlen(s)-1] = '\0';
		if (findItem(s))
			cout <<"Element is found:" <<  s;
		else
			cout << "Is not found!";
		getch();
	}

	void load()
	{
		ifstream inf;
		inf.open("input2.txt", ios::in);
		if (!inf) cout << "error";
		clear();
		cout << endl;
		char s[SLEN];
		int n = 0;
		while (1)
		{
			inf.getline(s, SLEN, '\n');
			int next = inf.peek();
			addItem(s);
			n++;	
			if (next == EOF)
				break;
		}
		cout << n;
		inf.close();
		ofstream outF;
		outF.open("out.txt", ios::out);
		if (!outF) cout << "error";
		int i;
		for (i = 0; i < NHASH; i++)
		{
			Item *p;
			if (i == 0)
				outF <<"->";
			else
				outF << "\n->";
			for (p = htable[i]; p != NULL; p = p->next)
			{
				outF << "->" << p->s;
			}
			outF <<"--|";
		}
		outF.close();
		n = 0;
		for (int i = 0; i < NHASH; i++)
		{
			Item *p = htable[i];
			if (p == NULL)
				n++;
		}
		cout << "\n" << n;
		printf("\n\nData from file INPUT.TXT loaded!\n");
		getch();
	}

private:
	void dell(Item *&p)
	{
		while (p != NULL)
		{
			Item *del = p;
			p = p->next;
			delete del;
		}
		p = NULL;
	}

	void print( Item *pp)
	{
		cout << "\n->";
		for (Item *p = pp; p != NULL; p = p->next)
		{
			cout << " -> " << p->s ;
		}
		cout << "--|";
	}

	unsigned int hash(char *str)
	{
		unsigned int h = 0;
		for (unsigned char *p = (unsigned char *) str; *p != '\0'; p++)
			h = MULTIPLIER * h + *p;
		return h % NHASH;
	}

	void addItem(char *s)
	{
		char *temp = strchr(s, '\n');
		if (temp != NULL)
			*temp = '\0';

		if (s[strlen(s)-1] == '\n')
			s[strlen(s)-1] = '\0';
		int h = hash(s);
		for (Item *p = htable[h]; p != NULL; p = p->next)
		{
			if (strcmp(s, p->s) == 0) 
				return;
		}
		Item *ins = new Item;
		strcpy(ins->s, s);
		ins->next = htable[h];
		htable[h] = ins;
	}

	bool findItem(char *s)
	{
		int h = hash(s);
		for (Item *p = htable[h]; p != NULL; p = p->next)
		{
			if (strcmp(s, p->s) == 0) 
				return true;
		}
		return false;
	}

	void delItem(char *s)
	{
		if (s[strlen(s)-1] == '\n') 
			s[strlen(s)-1] = '\0';
		int h = hash(s);
		for (Item *prev = NULL, *p = htable[h]; p != NULL; prev = p, p = p->next)
		{
			if (strcmp(s, p->s) == 0)
			{
				if (prev == NULL)	
					htable[h] = p->next;
				else                 
					prev->next = p->next;
				delete p;
				cout << "Element is deleted!";
				getch();
				return;
			}
		}
		cout << "Element is not found!";
		getch();
	}
};

void  menu()
{
	Hash *h = new Hash();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char c;
	do
	{
		system("cls");
		printf("1: View\n");
		printf("2: Find\n");
		printf("3: Add\n");
		printf("4: Del\n");
		printf("5: Clear\n");
		printf("6: Load\n");
		printf("\nEsc: Exit\n");
		c = getch();
		switch(c)
		{
		case '1': h->view(); break;
		case '2': h->find(); break;
		case '3': h->add(); break;
		case '4': h->del(); break;
		case '5': h->clear(); break;
		case '6': h->load(); break;
		}
	} while(c != 27);
	delete h;
}

void main()
{
	menu();
}