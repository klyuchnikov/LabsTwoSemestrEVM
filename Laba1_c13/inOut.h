#define const
#ifndef
void writeArray1D(int *arr, int sizeArr, char *caption) 
{
	cout << caption << endl;
	for (int i = 0; i < sizeArr; i++) 
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int getSize(char *string)
{
	int res;
	do
	{
		cout << string;
		cin >> res;
	} while (res <= 0);
	return res;
}

void getArray1D(int *&arr, int &size, char *strInSize) 
{
	size = getSize(strInSize);;
	assert(size > 0);
	arr = new int[size];
	cout << "Please input " << size << " elements:" << endl;
	for (int i = 0; i < size; i++) 
	{
		cout << "Element " << i << " : ";
		cin >> arr[i];
	}
	cout << endl;
}
#endif