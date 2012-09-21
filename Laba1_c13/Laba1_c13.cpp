// Laba1_c13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
using namespace std;

const int maxSize = 10;
 
int getSize() 
{	
	int size;
    cout << "Please input size array: ";
	do
	{
		cin >> size; 
	} while (size <= 0 || size > maxSize);
	return size;
}

void readArray(int a[], const int size)
{ 
	for (int i = 0; i < size; ++i)
	{
		cout << "Please input element " << i << ": ";
		cin >> a[i];
	}
}

void writeArray(const int a[], const int size)
{
	cout << endl;
	for (int i = 0; i < size; ++i)
	{
		cout << "Element " << i << ": " << a[i] << endl;
	}
}

bool isBeginChane(const int a)
{
	return (a%2 != 0);
}

int lenChane(const int a[], const int current, const int size)
{
	int len = 0;
	for (int i = current; i < size; i++)
	{		
		if (a[i]%2 == 0) break;
		len++;
	}
	return len;
}

int getMax(const int a[], const int size)
{
	int max = a[0];
	for (int i = 1; i < size; i++)
	{
		if (a[i] > max) max = a[i];
	}
	return max;
}

int delElements(int a[], int size, int begin, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = begin; j < size - 1; j++) 
		{
			a[j] = a[j + 1];
		}
		size--;
	}
	return size;
}


int process(int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (isBeginChane(a[i]) == true)
		{
			int len = lenChane(a, i, size);;
			int max = getMax(a, size);;
			if (len > 2)
			{
				a[i] = max;
				size = delElements(a, size, i + 1, len - 1);
			}
		}
	}
	return size;
}

void _tmain()
{
	int size = getSize();;
	int myArray[maxSize];
	readArray(myArray, size);
	writeArray(myArray, size);
	size = process(myArray, size);
	writeArray(myArray, size);
	_getch();
}