// Laba4_11.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "inOut.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include "fstream.h"
#include <stdlib.h>

#pragma warning (disable : 4996)

using namespace std;

const char *FileName = "laba5_11.dat";
const int MAXSIZE = 10;

typedef struct 
{
	int size;
	int *arr;
	void newMem(int newsize)
	{
		size = newsize;
		arr = new int[newsize];
	}

	void getArr1D()
{
	newMem(getSize("Please input size array B: "));
	cout << "Please input " << size << " elements:" << endl;
	for (int i = 0; i < size; i++)
		cin >> arr[i];
}

	void freeMem()
	{
		delete arr;
	}
	void write(char ch)
	{
		cout << "Array " << ch << ": " << endl;
		for (int i = 0; i < size; i++)
			cout << arr[i] << ' ';
		cout << endl;
	}
	void saveToFile(ofstream &outF)
	{
		for (int i = 0; i < size; i++)
		{
			outF << arr[i] << ' ';
		}
	}
	void delEl(const int pos)
	{
		memmove(&arr[pos], &arr[pos + 1], sizeof(int) * (size-- - pos - 1));
	}
} arr1D;

typedef struct 
{

	int Nsize;
	bool flag;
	int Msize;
	arr1D *arr;

	void newMemN(int size)
	{
		Nsize = size;
		arr = new arr1D[size];
		flag = true;
	}
	void newMemM(int size)
	{
		Msize = size;
		if (flag == true)
			for (int i = 0; i < Nsize; i++)
				arr[i].newMem(size);
	}
	void freeMem()
	{
		for (int i = 0; i < Nsize; i++)
			arr[i].freeMem();
		delete arr;
	}
	void write(char ch)
	{
		cout << "Array " << ch << ": " << endl;
		for (int i = 0; i < Nsize; i++)
		{
			arr[i].write(ch);
			cout << endl;
		}
	}
	void saveToFile(char *filename)
	{
		ofstream outF;
		outF.open(FileName, ios::out);
		if (!outF) cout << "error";
		outF << Nsize << ' ' << arr[0].size << ' ' << '\n';
		for (int i = 0; i < Nsize; i++)
		{
			arr[i].saveToFile(outF);
			outF << '\n';
		}
		outF.close();
	}
} arr2D;

void getWithFile(arr2D &a)
{
	char e[2], ch, next = 0;
	ifstream inF;
	inF.open(FileName, ios::in);
	if (!inF) cout << "error";
	int len = 0, N = -1, M = -2;
	while (inF.get(ch))
    {
        next = inF.peek();
        if (next == EOF) break;
        if (ch == '\n')
        {
            N++;
            M = 0;
            continue;
        }
        e[len++] = ch;
        if (next == ' ')
        {
            int el = atoi(e);
            if (M == -2) a.newMemN(el); 
            if (M == -1) a.newMemM(el);
			if (M >= 0) a.arr[N].arr[M] = el;
            inF.ignore();
            e[0] = '\0'; e[1] = '\0';
            len = 0;
            M++;
            continue;
        }
    }
	inF.close();
}
void getWithKey(arr2D &a)
{
	cout << "Keyboard:" << endl;
	a.newMemN(getSize("Please input count string array: "));
	a.newMemM(getSize("Please input count qqqqqq array: "));
	cout << "Please input matrix " << a.Nsize << " x " << a.Msize << endl;
	for (int i = 0; i < a.Nsize; i++)
	{
		cout << "Please input " << i << " string:" << endl;
		for (int j = 0; j < a.Msize; j++)
		{
			cout << "Element " << j << ": ";
			cin >> a.arr[i].arr[j];
		}
		cout << endl;
	}
}
void getArr2D(arr2D &a)
{
	char c;
	cout << "Please enter 1 - input from file" << endl << "else - input from keyboard: ";
	cin >> c;
	if (c == '1')
	{
		getWithFile(a);
		return;
	}
	else
	{
		getWithKey(a);
	}
}

int maxEl(const arr2D a, const int pos)
{
	int res = a.arr[0].arr[pos];
	for (int i = 1; i < a.Nsize; i++)
		if (a.arr[i].arr[pos] < res) res = a.arr[i].arr[pos];
	return res;
}


void process(arr2D &a, arr1D &b)
{
	for (int i = 0; i < a.Msize; i++)
	{
		int max = maxEl(a, i);;
		int j = 0;
		while (j < b.size)
		{
			if (b.arr[j] == max) b.delEl(j);
			j++;
		}
	}
}

void _tmain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	arr1D ArrayB;
	arr2D ArrayA;
	ArrayB.getArr1D();
	ArrayB.write('B');
	getArr2D(ArrayA);
	ArrayA.write('A');
	process(ArrayA, ArrayB);
	ArrayB.write('B');
	ArrayA.saveToFile((char *)FileName);
	ArrayA.freeMem();
	ArrayB.freeMem();
	getch();
}