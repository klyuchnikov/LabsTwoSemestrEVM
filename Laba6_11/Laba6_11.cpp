//#include <graphics.h>
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "INOUT.H"
using namespace std;



//void graphicPicture()
//{
//  int dr = DETECT, gmode, errorcode;
//  initgraph(&dr, &gmode, "c:\\turboc\\bgi");
//
//  if (graphresult() != grOk)
//  {
//    printf("Graphics error: %s\n", grapherrormsg(graphresult()));
//    printf("Press any key to halt:");
//    getch();
//    exit(1);
//  }
//  setcolor(7);
//  setfillstyle(1,8);
//  for (int i = 254; i > 250; i--)
//    fillellipse(310, i, 60, 20);
//  setcolor(15);
//  setfillstyle(1,0);
//  for (i = 1; i < 5; i++)
//    rectangle(290, 200, 320 + i, 245 - i);
//  bar(291, 200, 320, 243);
//  setfillstyle(9, 8);
//  setlinestyle(0, 4, 2);
//  bar3d(200, 50, 420, 200, 5, 0);
//  setfillstyle(10, 9);
//  bar3d(210, 60, 410, 190, 0, 0);
//  setfillstyle(1, 2);
//  bar3d(210, 180, 410, 190, 0, 0);
//  setfillstyle(1, 41);
//  bar3d(253, 190, 367, 180, 0, 0);
//  outtextxy(300, 192, "LG");
//  outtextxy(370, 182, "00:00");
//  outtextxy(212, 182, "Start");
//  getch();
//  setgraphmode(getgraphmode());
//  closegraph();
//}
int getSizeC(arr1D &a, arr1D &b)
{
	int k = 0;
	for (int i = 0; i < a.size; i++ )
		for (int j = 0; j < b.size; j++)
			if (a.arr[i] == b.arr[j])
				k++;
	return k;
}
arr1D getArrC(arr1D &a, arr1D &b)
{
	arr1D temp;
	int size = getSizeC(a,b);;
	temp.newMem(size);
	int k = 0;
	for (int i = 0; i < a.size; i++ )
		for (int j = 0; j < b.size; j++)
			if (a.arr[i] == b.arr[j])
				temp.arr[k++] = a.arr[i];
	return temp;
}

void delElements(arr1D &a)
{
	int i = 0;
	while (i < a.size)
	{
		if (a.arr[i] % 2 == 0)
		{
			a.delEl(i);
			continue;
		}
		i++;
	}
}

void change(arr1D a, const int i1, const int i2)
{
	int temp = a.arr[i1];
	a.arr[i1] = a.arr[i2];
	a.arr[i2] = temp;
}

int min(const arr1D arr, int pos)
{
	int res = pos;
	for (int i = pos + 1; i < arr.size; i++)
		if (arr.arr[i] < arr.arr[res]) res = i;
	return res;
}

void sort(arr1D &a)
{
	int m;
	for (int i = 0; i < a.size; i++)
	{
		m = min(a, i);
		change(a, i, m);
	}
}

void main()
{
//  clrscr();
  //graphicPicture();
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  arr1D ArrayA, ArrayB, ArrayC;
  ArrayA.getArr1D("Please input size array A: ");
  ArrayB.getArr1D("Please input size array B: ");
  ArrayA.write('A');
  ArrayB.write('B');
  ArrayC = getArrC(ArrayA, ArrayB);;
  delElements(ArrayB);
  ArrayB.write('B');
  sort(ArrayB);
  ArrayB.write('B');
  ArrayC.write('C');
  ArrayA.freeMem();
  ArrayB.freeMem();
  ArrayC.freeMem();
  _getch();
}

