// Головне.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Menu.cpp"
#include <Windows.h>

int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	int g = 1;
	//HDC hdc = GetDC(hwnd);
	system("mode con lines=50 cols=100");
	SetConsoleTextAttribute(handle, 112);
	MoveWindow(hwnd, 0, 0, 820, 640, FALSE);
	system("cls");
	while (g)
	{
		g = main_menu(hwnd);
		switch (g)
		{
		case 1:
		{
			graph_menu(hwnd, 1);
			break;
		}
		case 2:
			graph_menu(hwnd, 0);
			break;
		case 3:
		{
			support(hwnd);
			break;
		}
		default:
		{
			break;
		}
		}
	}
    return 0;
}

