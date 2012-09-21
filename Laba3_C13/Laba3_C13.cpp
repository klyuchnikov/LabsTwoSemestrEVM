
#include "stdafx.h"
#include "inOut.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#pragma warning( disable : 4996 )

using namespace std;

const int MAX = 10;
const char separators[] = " ,./:";
const char enableEN[] = "qwertyuiopasdfghjklzxcvbnm0123456789QWERTYUIOPLKJHGFDSAZXCVBNM";
const char enableRU[] = "éöóêåíãøùçõúıæäëîğïàâûôÿ÷ñìèòüáşÉÖÓÊÅÍÃØÙÇÕÚİÆÄËÎĞÏÀÂÛÔß×ÑÌÈÒÜÁŞ¸¨";

bool isBeginWord(const char *a, const int pos)
{
	if (strchr(separators, a[pos]) != NULL)
		return false;
	if (pos == 0)
		return true;
	return (strchr(separators, a[pos - 1]) != NULL);
}

int lenStr(const char *a)
{
	int i = 0;
	while (true)
	{
		if (a[i] == '\0')
			return i;
		i++;
	}
}

int findLen(const char *a, const int pos)
{
	int res = 0;
	int size = lenStr(a);;
	for (int i = pos; i < size; i++)
	{
		if (strchr(separators, a[i]) != NULL)
			break;
		res++;
	}
	return res;
}

void getWord(const char *a, char *res, const int pos, const int len)
{
	for (int i = 0; i < len; i++)
	{
		res[i] = a[pos + i];
	}
	res[pos + len] = '\0';
}

int getArrWords(char *a, const bool flag, char **&b)
{
	int col = 0;
	int i = 0;
	int size = lenStr(a);;
	while (i < size)
	{
		if (isBeginWord(a, i) == false)
		{
			i++;
			continue;
		}
		const int len = findLen(a, i);;
		if (flag == true)
		{
			char tmp[30] = "";
			getWord(a, tmp, i, len);;
			b[col] = new char[len + 1];
			strcpy(b[col], tmp);
		}
		col++;
		i += len;
	}
	return col;
}

void print(char **a, const int size)
{
	for (int j = 0; j < size; j++)
		cout << a[j] << endl;
	cout << '\n';
}

void readStr(char **&a, const int sizeStr)
{
	char str[150];
	char ch = 0;
	int k = 0;
	int i = 0;
	while (i < sizeStr) 
	{
		ch = _getch();
		if (ch == 13)
		{
			str[k] = '\0';
			a[i] = new char[++k];
			strcpy(a[i], str);			
			k = 0;
			i++;
			cout << endl;
			continue;
		}
		if (strchr(separators, ch) != NULL || strchr(enableEN, ch) != NULL)
		{
			str[k++] = ch; 
			cout << ch;
		}
	}
	cout << '\n';
}

void delArr(char **&a, const int size)
{
	for(int i = 0; i < size; i++)
	{
		delete a[i];
	}
	delete a;
}

bool equalWords(char *a, const char *b, const int pos)
{
	int sizeB = lenStr(b);
	int sizeA = lenStr(a);
	if (pos == 0)
	{	
		if (strchr(enableEN, a[pos + sizeB]) != NULL)
		{
			return false;
		}
	} 
	else if (pos + sizeB == sizeA)
	{
		if (strchr(enableEN, a[pos - 1]) != NULL)
		{
			return false;
		}
	}
	else if (strchr(enableEN, a[pos - 1]) != NULL || strchr(enableEN, a[pos + sizeB]) != NULL) 
	{
		return false;
	}
	for (int i = 0; i < sizeB; i++)
	{
		if (a[pos + i] != b[i]) 
		{
			return false;
		}
	}
	return true;
}

char up(char ch)
{
	char temp[2];
	temp[0] = ch;
	temp[1] = '\0';
	strupr(temp);
	return temp[0];
}
void insertBrackets(char *&a, int &sizeA, const int pos, const int len)
{
	char *temp = new char[sizeA + 3];
	memmove(temp, a, sizeof(char) * pos);	
	temp[pos] = '(';	
	temp[pos + 1] = up(a[pos]);;

	memmove(&temp[pos + 2], &a[pos + 1], sizeof(char) * len - 2);

	temp[pos + len] = up(a[pos + len - 1]);;
	temp[pos + len  + 1] = ')';

	memmove(&temp[pos + len + 2], &a[pos + len], sizeof(char) * (sizeA - len - pos));
	temp[sizeA + 2] = '\0';
	delete a;
	a = temp;
	sizeA += 2;
}
void process2(char *&arrA, const char *arrB)
{
	int i = 0;
	int sizeA = lenStr(arrA);;
	while (i < sizeA)
	{
		if (arrA[i] == arrB[0])
		{
			if (equalWords(arrA, arrB, i) == true)
			{
				int len = lenStr(arrB);;
				insertBrackets(arrA, sizeA, i, len);
				i += len + 2;
			}
		}
		i++;
	}
}
void process(char **&a, char **b, const int sizeB, const int size)
{
 	for (int k = 1; k < size; k++)
	{
		
		for (int j = 0; j < sizeB; j++)
		{
			process2(a[k], b[j]);
			
		}
	}
}

void main() 
{	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int sizeA;
	cout << "Enter count string : ";
	cin >> sizeA;
    char **a = new char *[sizeA];;
	readStr(a, sizeA);
	print(a, sizeA);
	char **b;
	int sizeB = getArrWords(a[0], false, b);
	b = new char *[sizeB];
	getArrWords(a[0], true, b);
	print(b, sizeB);
	process(a, b, sizeB, sizeA);
	print(a, sizeA);
	delArr(b, sizeB);
	delArr(a, sizeA);
	_getch();
}