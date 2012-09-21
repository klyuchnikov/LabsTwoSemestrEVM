#ifndef workwithstring
#define workwithstring
#include <iostream>
#pragma warning( disable : 4996 )
using namespace std;

const char separators[] = " ,./:";
const char enableEN[] = "qwertyuiopasdfghjklzxcvbnm0123456789QWERTYUIOPLKJHGFDSAZXCVBNM";
const char vowel[] = "eyuioa";

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
	res[len] = '\0';
}

void print(char **a, const int size)
{
	for (int j = 0; j < size; j++)
		cout << a[j] << endl;
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
	for (int i = 0; i < len; i++)
	{
		temp[pos + 1 + i] = a[pos + i];
		if (strchr(vowel ,a[pos + i]) != NULL)
			temp[pos + 1 + i] = up(a[pos + i]);
		
	}
	temp[pos + len  + 1] = ')';
	memmove(&temp[pos + len + 2], &a[pos + len], sizeof(char) * (sizeA - len - pos));
	temp[sizeA + 2] = '\0';
	delete a;
	a = temp;
	sizeA += 2;
}

#endif