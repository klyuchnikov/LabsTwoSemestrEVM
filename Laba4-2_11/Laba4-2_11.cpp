// Laba4-2_11.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "inOut.h"
#include "WorkWithString.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include "fstream.h"
#include <stdlib.h>

#pragma warning( disable : 4996 )

using namespace std;

const char *fileName = "laba4.txt";

int getStr(char *file)
{
	ifstream inf;
	inf.open(file, ios::in);
	if (!inf) cout << "error";
	int res = 0; 
	char ch;
	while (inf.get(ch))
	{
		if (ch == EOF) break;
		if (ch == '\n')
		{
			res++;
			inf.ignore();
			continue;
		}
	}
	inf.close();
	return res + 1;
}

int readFile(char **&a, char *file)
{
	int size = getStr((char *)fileName);;
	char next, temp[150];
	int len = 0, i = 0;
	a = new char *[size]; 

	ifstream inF;
	inF.open(file, ios::in);

	if (!inF) cout << "error";
	while(1)
	{
		inF.getline(temp, 150);
		next = inF.peek();
		a[i] = new char[lenStr(temp) + 1];
		strcpy(a[i], temp);
		i++;
		if (next == EOF) break;
	}
	inF.close();
	return size;
}

void writeFile(char **a, const int size, char *name)
{
	ofstream outF;
	outF.open(name, ios::out);
	if (!outF) cout << "error";
	for (int i = 0; i < size; i++)
		outF << a[i] << '\n';
	outF.close();
}

void getSymbols(char **a, const int size, char *&s)
{
	int max = 0;
	int len = lenStr(a[0]);
	for (int i = 1; i < size; i++)
	{
		int temp = lenStr(a[i]);;
		if (temp > len)	
		{
			len = temp;
			max = i;
		}
	}
	int i = 0;
	char tmp[30] = "";
	while (i < len)
	{
		if (isBeginWord(a[max], i) == false)
		{
			i++;
			continue;
		}
		const int len = findLen(a[max], i);;
		getWord(a[max], tmp, i, len);;
		i += len;
	}
	s = new char[len];
	strcpy(s, tmp);
}

void work(char *&a, char *s)
{
	int i = 0;
	int lenstr = lenStr(a);;
	while (i < lenstr)
	{
		if (isBeginWord(a, i) == false)
		{
			i++;
			continue;
		}
		char tmp[20] = "";
		const int len = findLen(a, i);;
		getWord(a, tmp, i, len);;
		if (strpbrk(tmp, s) == NULL)
		{
			insertBrackets(a, lenstr, i, len);
			i += len + 2;
			continue;
		}
		i += len;
	}
}
void process(char **&a, const int size)
{
	char *st = NULL;
	getSymbols(a, size, st);
	for (int i = 0; i < size; i++)
		work(a[i], st);
	delete st;
}

void _tmain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char **arr = NULL;
	int size = readFile(arr, (char *)fileName);
	process(arr, size);
	print(arr, size);
	writeFile(arr, size, "laba22.txt");
	delArr(arr, size);
	_getch();
}

