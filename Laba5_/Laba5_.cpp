#include <windows.h>
#include "stdafx.h"
#include "All.h"

#define    ID_EDIT      1001
#define    ID_BUTTON    1002
#define    ID_BUTTON2   1004
#define    ID_LIST      1003
#define    ID_STATIC    1000

#pragma warning( disable : 4996 )

char   szClassName[ ] = "EditClass";
char   szTitle[ ] = "Laba5";


class value
{
public:
	int sizeStr;
	char sizeCh;
	int k;
	int i;
	char **b;
	char **arr;

public:
	value()
	{
		sizeStr = 0;
		sizeCh = 0;
		k = 0;
		i = 0;
		b = NULL;
		arr = NULL;
	}

};

value *vl;

BOOL RegClass(WNDPROC, LPCTSTR, UINT);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE  hInstance;

int WINAPI WinMain(HINSTANCE hlnst, HINSTANCE hPrevlnstance, LPSTR IpszCmdLine, int nCmdShow) 
{   
	MSG msg; 
	HWND hwnd; 
	hInstance = hlnst;
    vl = new value();
	if (!RegClass((WNDPROC)WndProc, szClassName, COLOR_WINDOW)) 
		return FALSE;
	if (!(hwnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		100, 50, 640, 480, 0, 0, hInstance, 
		NULL))) 
		return FALSE;
	while(GetMessage(&msg, 0, 0, 0))
	{  
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	delete vl;
	return msg.wParam;
}

BOOL RegClass(WNDPROC Proc, LPCTSTR szName, UINT brBackground) 
{   
	WNDCLASS wc; 
	wc.style = wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.lpfnWndProc = Proc;   
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(brBackground + 1);
	wc.lpszMenuName = (LPCTSTR)NULL;
	wc.lpszClassName = szName; 
	return (RegisterClass(&wc) != 0);
}

void pro(char **&a, const int size, int &sizeB, value &vl)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sizeB = getArrWords(a[0], false, vl.b);
	vl.b = new char *[sizeB];
	getArrWords(a[0], true, vl.b);
	process(a, vl.b, sizeB, size);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam) 
{   
	static HWND hEdit, hButton, Buttom, hStatic, hListBox;   
	char chBuff[80] = "0"; 
	bool flag = false;
	switch (msg) 
	{
	case WM_CREATE:
		{
			hButton = CreateWindow("button", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				350, 10, 100, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);
			hStatic = CreateWindow("static", "Please input count string: ", WS_CHILD | WS_VISIBLE | SS_CENTER, 
				30, 10, 300, 20, hwnd, (HMENU)ID_STATIC, hInstance,NULL); 
			hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 
				30, 40, 300, 30, hwnd, (HMENU)ID_EDIT, hInstance, NULL); 
			hListBox = CreateWindow("listbox",  NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT, 
				30, 80, 300, 150, hwnd, (HMENU)ID_LIST, hInstance, NULL);
			SetFocus(hEdit); 
			return 0;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) 
			{
			case ID_EDIT:
				{
					if ((HIWORD(wParam)) == EN_ERRSPACE)
						MessageBox(hwnd, "error", szTitle, MB_OK); 
					return 0;
				}
			case ID_LIST:
				{
					switch (HIWORD(wParam)) 
					{
					case LBN_DBLCLK:
						{
							return 0;
						}
					default: return 0;
					}
					return 0;
				}
			case ID_BUTTON:
				{  
					if (vl->sizeStr <= 0)
					{
						SendMessage(hEdit, EM_GETLINE, 0, (LPARAM)chBuff);
						vl->sizeStr = atoi(chBuff);
						SetWindowText(hEdit, "\0"); 
						if (vl->sizeStr > 0)
						{
							hStatic = CreateWindow("static", "Please input string:", WS_CHILD | WS_VISIBLE | SS_CENTER, 
								30, 10, 300, 20, hwnd, (HMENU)0, hInstance, NULL); 
							vl->arr = new char *[vl->sizeStr];
						} 
						else
							hStatic = CreateWindow("static", "Please correct input count srting: ", WS_CHILD | WS_VISIBLE | SS_CENTER, 
								30, 10, 300, 20, hwnd, (HMENU)0, hInstance, NULL); 
						break;
					} 
					else
					{
						SendMessage(hEdit, EM_GETLINE, 0, (LPARAM)chBuff);
						if (lenStr(chBuff) != 0)
						{
							SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)chBuff);
							vl->arr[vl->k] = new char [lenStr(chBuff) + 1];
							strcpy(vl->arr[vl->k], chBuff);
							vl->k++;

						}
						SetWindowText(hEdit, "\0"); 
						SetFocus(hEdit);
						if (vl->k < vl->sizeStr)
						{
							hStatic = CreateWindow("static", "Please input string:", WS_CHILD | WS_VISIBLE | SS_CENTER, 
								30, 10, 300, 20, hwnd, (HMENU)0, hInstance, NULL);
						}
						else
						{
							SendMessage(hEdit, EM_SETREADONLY, 1, 0);    
							SendMessage(hButton, BS_TEXT, (WPARAM)"dfgdg", 1);  
							hButton = CreateWindow("button", "Process", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								350, 10, 100, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);
							hStatic = CreateWindow("static", "Пожалуйста нажмите кнопку Process для начала обработки введенного массива:",
								WS_CHILD | WS_VISIBLE | WS_TILED  | SS_CENTER, 
								30, 10, 300, 30, hwnd, (HMENU)ID_STATIC, hInstance, NULL);
							vl->k++;
							flag = true;
						} 
						if ((flag == true) && (vl->k - 2 == vl->sizeStr))
						{
							int sizeB = 0;
							pro(vl->arr, vl->sizeStr, sizeB, *vl);
							SendMessage(hListBox, LB_RESETCONTENT, 0, 0L); 
							for (int i = 0; i <vl->sizeStr; i++)
								SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)vl->arr[i]);
							delArr(vl->b, sizeB);
							delArr(vl->arr, vl->sizeStr);
							vl->k++;
							break;

						}											
					}
					return 0;
				}				
			}
			return 0;
		}
	case WM_DESTROY: 
		{
			PostQuitMessage(0); 
			return 0;
		}
	}
	return DefWindowProc( hwnd, msg, wParam, IParam );
}
