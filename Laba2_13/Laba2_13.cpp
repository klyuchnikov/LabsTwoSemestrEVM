// Laba2_13.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "inOut.h"
#include <assert.h>
#include <conio.h>
#include <iostream>

using namespace std;

void getC(const int *a, const int *b, int *c, const int sizeA, const int sizeB, int &k) 
{
	for (int i = 0; i < sizeA; i++)
	{
		bool flag = false;
		for (int j = 0; j < sizeB; j++)
		{
			if (a[i] == b[j]) {
				flag = true;
				break;
			}
		}
		if (flag == false) 
			c[k++] = a[i];
	}
}
int *getArrayC(const int *a, const int *b, const int &sizeA, const int &sizeB, int &sizeC) 
{
	int temp = 0;
	for (int i = 0; i < sizeA; i++)
	{
		for (int j = 0; j < sizeB; j++)
		{
			if (a[i] == b[j]) 
				temp++;
		}
	}
	sizeC = sizeA + sizeB - (2 * temp);
	int *c = new int[sizeC];
	int k = 0;
	getC(a, b, c, sizeA, sizeB, k);
	getC(b, a, c, sizeA, sizeB, k);
	assert(k == sizeC);
	return c;
}

void change(int *a, const int i1, const int i2)
{
	int temp = a[i1];
	a[i1] = a[i2];
	a[i2] = temp;
}

void sort(int *a, const int size)
{
	bool flag = false;
	do
	{
	    for (int i = 0; i < size - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				for (int j = i; j < size; i++)
				{
					if (a[j] > a[j + 1])
					{
						change(a, j, j + 1);
						flag = true;
					}
				}
			}
		}
	} while (flag == true);
}

int _tmain()
{  
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    system("cls");
	int *arrayA = NULL, *arrayB = NULL;
	int sizeA, sizeB;
	getArray1D(arrayA, sizeA, "Please input size array A : ");
	getArray1D(arrayB, sizeB, "Please input size array B : ");
	int sizeC;
	int *arrayC = getArrayC(arrayA, arrayB, sizeA, sizeB, sizeC);;
	writeArray1D(arrayA, sizeA, "Array A :");
	writeArray1D(arrayB, sizeB, "Array B :");
	writeArray1D(arrayC, sizeC, "Array C :");
	delete arrayA;
	delete arrayB;
	delete arrayC;
	_getch();
	return 0;
}