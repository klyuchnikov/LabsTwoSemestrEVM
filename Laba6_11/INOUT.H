#ifndef inout
#define inout
#include <iostream>

const int MAX = 20;

using namespace std;

int getSize(char *string)
{
	int res;
	char temp[250];
	do
	{
		cout << string;
		cin >> temp;
		res = atoi(temp);

	} while (res < 0  && res > MAX);
	return res;
}

typedef struct 
{
	int size;
	int *arr;
	void newMem(int newsize)
	{
		size = newsize;
		arr = new int[newsize];
	}

	void getArr1D(char *string)
{
	newMem(getSize(string));
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
	void delEl(const int pos)
	{
		memmove(&arr[pos], &arr[pos + 1], sizeof(int) * (size-- - pos - 1));
	}
} arr1D;

#endif