// laba77.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "laba77.h"
#include "laba7.h"
#include "laba7_2D.h"
#include "STDLIB.H"
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <istream>
#include "WinDef.h"


using namespace std;

#pragma warning(disable : 4996)
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
List_1 *list1;
List_2 *list2;
HBITMAP Bmp;
HDC ghdc, chdc;

typedef struct
{
	char name[10];
	float x[100];
	float y[100];
} FUNC;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	List1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	List2(HWND, UINT, WPARAM, LPARAM);
BOOL DrawLine(HDC hdc, int x0, int y0, int x, int y)
{
	MoveToEx(hdc, x0, y0, NULL);
	return LineTo(hdc, x, y);
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LABA77, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA77));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_BYTEALIGNWINDOW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA77));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LABA77);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	hWnd = CreateWindow(szWindowClass, "", WS_DLGFRAME ,
		200, 200, 1000, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
bool ShowFileDialog(HWND HWndOwner, LPCWSTR *fileName, LPCWSTR Title,
    LPCWSTR InitialDir, LPCSTR Filter, bool openDialogTrue_saveDialogFalse)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

	TCHAR szFile[MAX_PATH];
	ZeroMemory(&szFile, MAX_PATH);

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = HWndOwner;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = Filter;
    ofn.nFilterIndex = 0;
    ofn.lpstrTitle = (LPCSTR)Title;
    ofn.lpstrInitialDir = (LPCSTR)InitialDir;
    ofn.Flags = OFN_EXPLORER; //| OFN_FILEMUSTEXIST;
	
	if(openDialogTrue_saveDialogFalse)
	{
		if (GetOpenFileName(&ofn))
		{
			*fileName = (LPCWSTR)ofn.lpstrFile;
			return true;
		}
	}
	else
	{
		if (GetSaveFileName(&ofn))
		{
			*fileName = (LPCWSTR)ofn.lpstrFile;
			return true;
		}
	}
	return false;
}


HBITMAP loadBMPFromFileWithOpenDialog(HWND hWnd)
{
	HBITMAP hBmp;
	LPCWSTR bmpFileName = NULL;

	if (ShowFileDialog(hWnd,
                       &bmpFileName,
                       L"Open file",
                       L"",
                       "BMP Files (*.bmp)\0*.bmp\0",
					   true))
    { 
		hBmp = (HBITMAP)LoadImage( NULL, (LPCSTR)bmpFileName, IMAGE_BITMAP, 0, 0,
               LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		return hBmp;
	}
	else
	{
		return NULL;
	}
}

void Picture(HWND hWnd, int q)
{
	HDC hdc = GetDC(hWnd);
/*
	const double a[] = {1.6,1.7,1.3,1.5};
	const double b[] = {-0.6,1.7,1.7,-1.8};
	const double c[] = {-1.2,0.06,0.5,1.6};
	const double d[] = {1.6,1.2,1.4,0.9};
	double x = 0, y = 0, t;
	int x2, y2;
	long i = 0;
	while(i < 100000)
	{
		t = x;
		x = sin(a[q] * y) + c[q] * cos(a[q] * x);
		y = sin(b[q] * t) + d[q] * cos(b[q] * y);
		x2 = (int)floor(x * 100) + 500;
		y2 = (int)floor(y * 100) + 300;
		SetPixel(hdc, x2, y2, GetPixel(hdc, x2, y2) + 1);
		i++;
	}
	Status
	*/
	BITMAP bm;
	PAINTSTRUCT paintstruct;
	LPCWSTR name = L"C:\Temp\false.bmp";
	HDC h = CreateCompatibleDC(hdc);
	Bmp = loadBMPFromFileWithOpenDialog(hWnd);
	if (Bmp){
		GetObject( Bmp, sizeof(BITMAP), &bm );
		HDC hMemDc = CreateCompatibleDC(hdc);
		
		SelectObject(hMemDc, Bmp);
		for (float i = 0; i < 800; i+=0.01)
		{		
			HDC hh = CreateCompatibleDC(chdc);
			//BitBlt(hdc, 100 - 0.01 + i, 100 - 0.01 + i, bm.bmWidth, bm.bmHeight, hMemDc, 0, 0, WHITENESS);
			BitBlt(hh, 100 + i, 100 + i, bm.bmWidth, bm.bmHeight, hMemDc, 0, 0, SRCCOPY);
			hdc = CreateCompatibleDC(hh);
			//SelectObject(hdc, h);
			//BitBlt(hdc, 0, 0, 500, 500, hh, 0, 0, SRCCOPY);
			DeleteDC(hh);
			
		}
		
		DeleteDC(hMemDc);
				
	}
	ghdc = hdc;
	DeleteDC(h);
	ReleaseDC(hWnd, hdc);
	//
}
class CC
{
public:
	int x0, y0, r; 
	int buttom, right, left, top;
	HDC hdc;
	COLORREF color;
	CC(HDC hdc, int x0, int y0, int r)
	{
		this->hdc = hdc;
		right = x0 - r;
		left = x0 + r;
		buttom = y0 - r;
		top = y0 + r;
		this->x0 = x0;
		this->y0 = y0;
		this->r = r;
	}
	void is(int x, int y, int &flag, int &vector, int &lastX, int &lastY)
	{
		x += x0;
		y += y0;
		if (y + r == 600)
		{
			vector = (x > lastX) ? 0 : 1;
			if (vector == 0)
				Circle(x - r - 2, y - 2*r - 2, RGB(255, 255, 255));
			else
				Circle(x - r + 2, y - 2*r - 2, RGB(255, 255, 255));
			lastX = x;
			lastY = y;
			flag = 1;
			return;
		} else if (x + r == 1000)
		{
			vector = (y > lastY) ? 1 : 0;
			if (vector == 0)
				Circle(x - r - 2, y - 2*r + 2, RGB(255, 255, 255));
			else
				Circle(x - r - 2, y - 2*r - 2, RGB(255, 255, 255));
			lastX = x;
			lastY = y;
			flag = 2;
			return;
		}else if (y - r == 0)
		{
			vector = (x > lastX) ? 1 : 0;
			if (vector == 0)
				Circle(x - r + 2, y - 2*r + 2, RGB(255, 255, 255));
			else
				Circle(x - r - 2, y - 2*r + 2, RGB(255, 255, 255));
			lastX = x;
			lastY = y;
			flag = 3;
			return;
		} else if (x - r == 0)
		{
			vector = (y > lastY) ? 0 : 1;
			if (vector == 0)
				Circle(x - r + 2, y - 2*r - 2, RGB(255, 255, 255));
			else
				Circle(x - r + 2, y - 2*r + 2, RGB(255, 255, 255));
			lastX = x;
			lastY = y;
			flag = 0;
			return;
		}
	}
	void Circle(int xx, int yy, COLORREF color)
	{
		for (float i = 0; i < 2 * 3.14175; i+=0.01)
		{
			int x = r * cos(i);
			int y = r * sin(i);
			SetPixel(hdc, x0 + x + xx, y0 + y + yy, color);
		}
	}
};

void f(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	int amp = 2;
	int flag = 0;
	int vector = 0;
	CC *c = new CC(hdc, 100, 200, 100);
	int x = 0, y = 0, i = 0, lastX, lastY;
	while(i < 4000)
	{
		if (flag == 0)
		{
			if (vector == 0)
			{
				c->Circle(x - amp, y - amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x+=amp;
				y+=amp;
			} else
			{
				c->Circle(x - amp, y + amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x+=amp;
				y-=amp;
			}

		} else if (flag == 1)
		{
			if (vector == 0)
			{
				c->Circle(x - amp, y + amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x+=amp;
				y-=amp;					
			} else
			{
				c->Circle(x + amp, y + amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x-=amp;
				y-=amp;
			}
		} else if (flag == 3)
		{
			if (vector == 0)
			{
				c->Circle(x + amp, y - amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x-=amp;
				y+=amp;
			} else
			{
				c->Circle(x - amp, y - amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x+=amp;
				y+=amp;
			}
		} else if (flag == 2)
		{
			if (vector == 0)
			{
				c->Circle(x + amp, y + amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x-=amp;
				y-=amp;
			} else
			{
				c->Circle(x + amp, y - amp, RGB(255, 255, 255));
				c->Circle(x, y, RGB(255, 0, 0));
				i+=amp;
				x-=amp;
				y+=amp;
			}
		}
		c->is(x, y, flag, vector, lastX, lastY);
	}
	delete c;
	ghdc = hdc;
	ReleaseDC(hWnd, hdc);
}

double Fsin(double x, int r)
{
	return r * sin(x);
}

double Fcos(double x, int r)
{
	return r * cos(x);
}
double Ftan(double x, int r)
{
	return r * tan(x);
}

int count(int a)
{
	int res = 1;
	while (true)
	{
		if (a / 10 == 0)
			break;
		a /= 10;
		res++;

	}
	return res;

}
char *enable = "1234567890";
int lenstr(char *str)
{
	int res = 0;
	int i = 0;
	while (strchr(enable, str[i]) != NULL && str[i] != 0)
	{
		res++;
		i++;
	}
	return res;
}
typedef double (*PTRFunc)(double, int);
void Function(HWND hWnd, int g)
{	
	HDC hdc = GetDC(hWnd);
	SetMapMode(hdc, MM_LOENGLISH);
	SetWindowOrgEx(hdc, 150, 250, NULL);
	SetViewportOrgEx(hdc, 300, 100, NULL);
	SetWindowExtEx(hdc, 10, 2, NULL);
	SetViewportExtEx(hdc, 100, 2, NULL);
	DrawLine(hdc, 0, 200, 0, -200);
	DrawLine(hdc, 0, 200, -10, 175);
	DrawLine(hdc, 0, 200, 10, 175);	
	DrawLine(hdc, 800, 0, 775, 15);
	DrawLine(hdc, 800, 0, 775, -15);		
	DrawLine(hdc, 0, 0, 800, 0); 
	TextOut(hdc, 20, 200, "y", 1);
	TextOut(hdc, 790, 30, "x", 1);	
	TextOut(hdc, 5, -10, "0", 1);		
	PTRFunc func[] = {Fsin, Fcos, Ftan};

	if (g == 0)
		MoveToEx(hdc, 0, 50, NULL);
	else if (g == 1)
		MoveToEx(hdc, 0, -50, NULL);
	else if (g == 2)
		MoveToEx(hdc, 0, 0, NULL);	
	double s = 0.5, last = 0, w = 1.57;
	for (double i = 0; i < 20; i += 0.01)
	{
		LineTo(hdc, i * 40, (*func[g])(i, 50));
		if (floor((*func[g])(i * 2, 50)) == 0)
		{
			
			if (i == last + 0.01)
				continue;
			last = i;	
			int ss = 10 * s;
			char *st = new char[12];
			int size = count(ss);
			itoa(ss, st, 10);
			char *sr = new char[13];
			if (size == 1)
				strcpy(sr, "0");
			else 
				strncpy(sr, st, size - 1);
			sr[lenstr(sr)] = 0;
			char *str = new char[11];
			strcpy(str, sr);
			strcat(str, ".");
			itoa(ss % 10, st, 10);
			strcat(str, st);
			s += 0.5;
			strcat(str, "п");
			TextOut(hdc, w * 40 - 15, -10, str, 4);
			w += 1.57;
			delete sr;
			delete st;
			delete str;

		}
	}
	ghdc = hdc;
	ReleaseDC(hWnd, hdc);
}

int flash = -1;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char *arr[] = {"sin(x)", "cos(x)", "tan(x)"};
	int wmId, wmEvent;
	static HWND hB1, hB2, hB3, hB4, hB5, Combo, hStatic, hButton;  
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	/*case  WM_MOVING:
		{
			if (flash >= 0 && flash < 4)
			{
				Function(hWnd, flash);
			}
			else if (flash >= 4)
			{
				Picture(hWnd, flash - 4);
			}
			//GetUpdateRect(hWnd, NULL, TRUE);
			//InvalidateRect(hWnd, NULL, FALSE);
			//SendMessage(hWnd, WM_PAINT, 0, 0);
			RedrawWindow(NULL, NULL, NULL, RDW_UPDATENOW);
			//UpdateWindow(hWnd);
			break;
		}*/

	case WM_CREATE:
		{
			hdc = GetDC(hWnd);
			chdc = CreateCompatibleDC(hdc);
			ReleaseDC(hWnd, hdc);
			hB1 = CreateWindow("button", "Clifford Attractor", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				10, 10, 150, 30, hWnd, (HMENU)ID_B1, hInst, NULL);
			hB2 = CreateWindow("button", "Картинка №2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				160, 10, 100, 30, hWnd, (HMENU)ID_B2, hInst, NULL);
			hB3 = CreateWindow("button", "Картинка №3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				260, 10, 100, 30, hWnd, (HMENU)ID_B3, hInst, NULL);
			hB4 = CreateWindow("button", "Картинка №4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				360, 10, 100, 30, hWnd, (HMENU)ID_B4, hInst, NULL);
			hB5 = CreateWindow("button", "Шарик", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				460, 10, 100, 30, hWnd, (HMENU)ID_B5, hInst, NULL);	
			hStatic = CreateWindow("static", "Выберете функцию :", WS_CHILD | WS_VISIBLE,
				10, 40, 150, 20, hWnd, (HMENU)ID_STAT, hInst, NULL);
			Combo = CreateWindow("ComboBox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST |  WS_VSCROLL | CBS_AUTOHSCROLL ,
				160, 40, 200, 100, hWnd, (HMENU)ID_COMBO, hInst, NULL);
			for (int i = 0; i < 3; i++)
				SendMessage(Combo, CB_ADDSTRING, 0 , (LPARAM)arr[i]);
			hButton =  CreateWindow("button", "Рисовать", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				360, 40, 100, 20, hWnd, (HMENU)ID_BUTTON, hInst, NULL);	
			break;
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_LIST1:
			{
				list1 = new List_1;
				list1->create();
				DialogBox(hInst, MAKEINTRESOURCE(IDD_LIST1), hWnd, List1);
				break;
			}
		case ID_BUTTON:
			{
				InvalidateRect(hWnd, NULL, TRUE);
				SendMessage(hWnd, WM_PAINT, 0, 0);
				if (SendMessage(Combo, CB_GETCURSEL, 0, 0L) == -1)
				{
					MessageBox(hWnd, "Вы не выбрали функцию.\nПожалуйста выберите функцию.", "Ошибка", MB_OK);
					break;
				}
				Function(hWnd, SendMessage(Combo, CB_GETCURSEL, 0, 0L));
				flash =  SendMessage(Combo, CB_GETCURSEL, 0, 0L);
				break;
			}
		case IDM_LIST2:
			{
				list2 = new List_2();
				DialogBox(hInst, MAKEINTRESOURCE(IDD_LIST2), hWnd, List2);
				break;
			}	
		case ID_B5:
			{
				InvalidateRect(hWnd, NULL, TRUE);
				SendMessage(hWnd, WM_PAINT, 0, 0);
				f(hWnd);
				break;
			}
		case ID_B1:
			{
				InvalidateRect(hWnd, NULL, TRUE);
				SendMessage(hWnd, WM_PAINT, 0, 0);
				Picture(hWnd, 0);
				flash = 4;
				break;
			}
		case ID_B2:
			{
				InvalidateRect(hWnd, NULL, TRUE);
				SendMessage(hWnd, WM_PAINT, 0, 0);
				Picture(hWnd, 1);
				flash = 5;
				break;
			}
		case ID_B3:
			{
				InvalidateRect(hWnd, NULL, TRUE);
				SendMessage(hWnd, WM_PAINT, 0, 0);
				Picture(hWnd, 2);
				flash = 6;
				break;
			}
		case ID_B4:
			{
				InvalidateRect(hWnd, NULL, TRUE);
				SendMessage(hWnd, WM_PAINT, 0, 0);
				Picture(hWnd, 3);
				flash = 7;
				break;
			}
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), ghdc, 0, 0, SRCCOPY);

				//SendMessage(hWnd, WM_PAINTCLIPBOARD, 0, 0);
		/*RECT *tt = new RECT();
		tt->bottom = CW_USEDEFAULT;
		tt->left = 0;
		tt->right = CW_USEDEFAULT;
		tt->top = 0;
		delete tt;*/
		
		EndPaint(hWnd, &ps);
		break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK List1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND Edit = GetDlgItem(hDlg, IDC_EDIT);
	HWND List = GetDlgItem(hDlg, IDC_LIST);
	char buff[300];
	int wmId;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		{
			wmId = LOWORD(wParam);
			switch (wmId)
			{	
			case IDC_TASK:
				{
					if (list1->task())
						MessageBox(hDlg, "Value deleted", "", MB_OK);
					else
						MessageBox(hDlg, "Value don't deleted", "", MB_OK);
					break;
				}		
			case IDC_PRINT:
				{
					SendMessage(List, LB_RESETCONTENT, 0, 0); 
					char *c = new char[300];
					for(Elem *p = list1->head; p != NULL; p = p->next)
					{
						itoa(p->val, c, 10);
						SendMessage(List, LB_ADDSTRING, 0, (LPARAM)c);
					}
					delete c;
					break;
				}
			case IDC_CLEAR:
				{
					list1->clear();	
					break;
				}
			case IDC_DESTROY:
				{
					list1->clear();
					delete list1;
					EndDialog(hDlg, LOWORD(wParam));
					break;
				}
			case IDC_ADD:
				{
					SendMessage(Edit, EM_GETLINE, 0, (LPARAM)buff);
					if (strlen(buff) != 0)
					{
						int el = atoi(buff);
						list1->add(el);
					}
					SetWindowText(Edit, "\0");
					SetFocus(Edit);
					break;
				}

			}
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				list1->clear();
				delete list1;
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}

	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK List2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND edFName = GetDlgItem(hDlg, IDC_FNAME);
	HWND edName = GetDlgItem(hDlg, IDC_NAME);
	HWND List2 = GetDlgItem(hDlg, IDC_LIST2);
	SendMessage(edFName, EM_SETLIMITTEXT, 50, 0);
	SendMessage(edName, EM_SETLIMITTEXT, 50, 0);

	int wmId;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		{
			wmId = LOWORD(wParam);
			switch (wmId)
			{	
			case IDC_ADDTOHEAD:
				{
					char *name = new char[100];
					char *fname = new char[100];
					SendMessage(edFName, EM_GETLINE, 0, (LPARAM)fname);
					SendMessage(edName, EM_GETLINE, 0, (LPARAM)name);
					if (str(fname))
					{			
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;
					}
					if(str(name))
					{		
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;		
					}
					if ((strlen(fname) != 0) && (strlen(name) != 0))
						list2->addToHead(fname, name);
					SetWindowText(edName, "\0");
					SetWindowText(edFName, "\0");
					delete name;
					delete fname;

					SendMessage(List2, LB_RESETCONTENT, 0, 0); 
					for(Elem2 *p = list2->head; p != NULL; p = p->next)
					{
						char *cc = new char[100];
						strcpy(cc, p->key.FirstName);
						strcat(cc, " , ");
						strcat(cc, p->key.Name);						
						SendMessage(List2, LB_ADDSTRING, 0, (LPARAM)cc);
						delete cc;
					}
					break;
				}
			case IDC_ADDTOTAIL:
				{
					char *name = new char[100];
					char *fname = new char[100];
					SendMessage(edFName, EM_GETLINE, 0, (LPARAM)fname);
					SendMessage(edName, EM_GETLINE, 0, (LPARAM)name);
					if (str(fname))
					{			
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;
					}
					if(str(name))
					{		
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;		
					}
					if ((strlen(fname) != 0) && (strlen(name) != 0))
						list2->addToTail(fname, name);
					SetWindowText(edName, "\0");
					SetWindowText(edFName, "\0");
					delete name;
					delete fname;

					SendMessage(List2, LB_RESETCONTENT, 0, 0); 
					for(Elem2 *p = list2->head; p != NULL; p = p->next)
					{
						char *cc = new char[120];
						strcpy(cc, p->key.FirstName);
						strcat(cc, " , ");
						strcat(cc, p->key.Name);						
						SendMessage(List2, LB_ADDSTRING, 0, (LPARAM)cc);
						delete cc;
					}
					break;
				}
			case IDC_PRINTNEXT:
				{
					SendMessage(List2, LB_RESETCONTENT, 0, 0); 
					for(Elem2 *p = list2->head; p != NULL; p = p->next)
					{
						char *cc = new char[120];
						strcpy(cc, p->key.FirstName);
						strcat(cc, " , ");
						strcat(cc, p->key.Name);						
						SendMessage(List2, LB_ADDSTRING, 0, (LPARAM)cc);
						delete cc;
					}
					break;
				}
			case IDC_CLEAR2:
				{
					list2->clear();
					break;
				}
			case IDC_SEARCH:
				{
					char *name = new char[100];
					char *fname = new char[100];
					bool flag = false;
					SendMessage(edFName, EM_GETLINE, 0, (LPARAM)fname);
					SendMessage(edName, EM_GETLINE, 0, (LPARAM)name);
					if (str(fname))
					{			
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;
					}
					if(str(name))
					{		
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;		
					}		
					if ((strlen(fname) != 0) && (strlen(name) != 0))
						for (Elem2 *p = list2->head; p != NULL; p = p->next)
						{
							if((strcmp(p->key.Name, name) == 0) && (strcmp(p->key.FirstName, fname) == 0))
								flag = true;
						}
					else
					{
						MessageBox(hDlg, "Элемент не введен","Поиск элемента в списке", MB_OK);
						delete name;
						delete fname;	
						break;
					}
					if (flag)
						MessageBox(hDlg, "Элемент найден","Поиск элемента в списке", MB_OK);
					else
						MessageBox(hDlg, "Элемент не найден","Поиск элемента в списке", MB_OK); 
					SetWindowText(edName, "\0");
					SetWindowText(edFName, "\0");
					delete name;
					delete fname;
					break;
				}
			case IDC_PRINTBACK:
				{
					SendMessage(List2, LB_RESETCONTENT, 0, 0); 
					for(Elem2 *p = list2->tail; p != NULL; p = p->prev)
					{
						char *ccc = new char[120];
						strcpy(ccc, p->key.FirstName);
						strcat(ccc, " , ");
						strcat(ccc, p->key.Name);						
						SendMessage(List2, LB_ADDSTRING, 0, (LPARAM)ccc);
						delete ccc;
					}
					break;
				}
			case IDC_DEL:
				{
					char *name = new char[100];
					char *fname = new char[100];
					SendMessage(edFName, EM_GETLINE, 0, (LPARAM)fname);
					SendMessage(edName, EM_GETLINE, 0, (LPARAM)name);
					if (str(fname))
					{			
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;
					}
					if(str(name))
					{		
						delete name;
						delete fname;
						SetWindowText(edName, "\0");
						SetWindowText(edFName, "\0");
						break;		
					}
					if ((strlen(fname) != 0) && (strlen(name) != 0))
						if (list2->del(fname, name))
							MessageBox(hDlg, "Элемент удален", "Удаление элемента списка", MB_OK); 
						else 
							MessageBox(hDlg, "Элемент не найден", "Удаление элемента списка", MB_OK);
					else
						MessageBox(hDlg, "Элемент не введен", "Удаление элемента списка", MB_OK);
					SetWindowText(edName, "\0");
					SetWindowText(edFName, "\0");
					delete name;
					delete fname;

					SendMessage(List2, LB_RESETCONTENT, 0, 0); 
					for(Elem2 *p = list2->head; p != NULL; p = p->next)
					{
						char *cc = new char[120];
						strcpy(cc, p->key.FirstName);
						strcat(cc, " , ");
						strcat(cc, p->key.Name);						
						SendMessage(List2, LB_ADDSTRING, 0, (LPARAM)cc);
						delete cc;
					}
					break;
				}

			}
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				list2->clear();
				delete list2;
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}
