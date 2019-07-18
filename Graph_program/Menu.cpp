#include "stdafx.h"
#include "Graph.cpp"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#define RAD 20 
#define RED RGB(200, 0, 0)
#define LMM 240
#define RMM 560
#define SIRIY1 RGB(190,190,190)
#define SIRIY2 RGB(155,155,155)
#define SMSX 525
#define SMSY 25
using namespace std;
void message(HWND, int);
void graph_buttom_paint(HWND hwnd, int obrane, int m[]);
void support(HWND);
bool exit(HWND hwnd);
void graph_menu(HWND hwnd, bool oriented);
void buttom(HWND hwnd,int x1, int y1, int x2, int y2, char * text, bool o);
void main_buttom_paint(HWND ,int);
void buttom_yn(HWND, bool);
int input_box(HWND hwnd, int x1, int y1, int x2, int y2, int post, int limit);
int main_menu (HWND hwnd)
{
	int k = 0, fl1 = 1, fl2 = 0;
	char ch = 10;
	main_buttom_paint(hwnd, 0);
		while (fl1)
	{
		if (_kbhit())
		{
			Sleep(80);
			ch = _getch();
			switch (ch)
			{
			case 27: {
				fl1 = exit (hwnd);
				main_buttom_paint(hwnd, k);
				break;
			}
			case 13: {
				switch (k) {
				case 0: 
				{
					fl1 = 0;
					fl2 = 1; 
					break;
				}
				case 1: {
					fl1 = 0;
					fl2 = 2;
					break;
				}
				case 2: {
					fl1 = 0;
					fl2 = 3;
					break;
				}
				case 3: {
					fl1 = exit(hwnd);
					main_buttom_paint(hwnd, k);
					break;
				}
				};
				break;
			}
			case 80: {
				if (k == 3) k = 0;
				else k++;
				main_buttom_paint(hwnd, k);
				break;
			}
			case 72: {
				if (k == 0) k = 3;
				else k--;
				main_buttom_paint(hwnd, k);
				break;
			}
			}
		}
	}
		clear_windows(hwnd, 0, 0, 800, 600);
	return fl2;
}
void main_buttom_paint(HWND hwnd , int k)
{
	bool a[4];
	for (int i = 0; i < 4; i++)
		a[i] = 0;
	a[k] = 1;
	buttom(hwnd, LMM, 40, RMM, 140, "ORIENTED GRAPH", a[0]);
	buttom(hwnd, LMM, 180, RMM, 280, "SIMPLE GRAPH", a[1]);
	buttom(hwnd, LMM, 320, RMM, 420, "SUPPORT", a[2]);
	buttom(hwnd, LMM, 460, RMM, 560, "EXIT", a[3]);
}
void buttom(HWND hwnd, int Left, int Top, int Right, int Bottom, char * text, bool o)
{
	HDC hdc = GetDC(hwnd);
	HPEN p1, p2;
	HBRUSH b1, b2 = CreateSolidBrush(SIRIY2);
	int b = strlen(text);
	if (o)
	{
		p2 = CreatePen(PS_SOLID, 3, RGB(0, 0, 200));
		SetTextColor(hdc, RGB(0, 0, 200));//так можешь сделать цвет текста
	}
	else
	{
		p2 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 0, 0));//так можешь сделать цвет текста
	}
	p1 = (HPEN)SelectObject(hdc, p2);// Заносим перо в контекст рисования
	b1 = (HBRUSH)SelectObject(hdc, b2);// Заносим кисть в контекст рисования
	RoundRect(hdc, Left, Top, Right, Bottom, RAD, RAD);
	SelectObject(hdc, p1);   // Возвращаем старое перо
	SelectObject(hdc, b1);
	ReleaseDC(hwnd, hdc);
	hdc = GetDC(hwnd);
	//SetTextColor(hdc, RGB(0, 0, 0));//так можешь сделать цвет текста
	SetBkColor(hdc, SIRIY2);//так фон
	TextOutA(hdc, Left + (Right - Left)/2.0 - b*3.5 , Top + (Bottom - Top)/2 - 9 , text, b);
	DeleteObject(p1);
	DeleteObject(p2);// Удаляем созданное перо
	DeleteObject(b1);
	DeleteObject(b2);// Удаляем созданную кисть
	ReleaseDC(hwnd, hdc);
	return;
}
void support(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HPEN p1, p2 = CreatePen(4, 2, RGB(0, 0, 0));
	HBRUSH b1, b2 = CreateSolidBrush(0);
	p1 = (HPEN)SelectObject(hdc, p2);
	b1 = (HBRUSH)SelectObject(hdc, b2);
	SetTextColor(hdc, BLACK);//так можешь сделать цвет текста
	SetBkColor(hdc, SIRIY1);//так фон
	TextOutA(hdc, 105, 15, "Edge in menu", 13);
	buttom(hwnd, 25, 55, 80, 95, "Start", 0);
	buttom(hwnd, 105, 55, 195, 95, "Lenght", 0);
	buttom(hwnd, 220, 55, 275, 95, "Finish", 0);
	TextOutA(hdc, 105, 105, "Simple edge", 12);
	MoveToEx(hdc, 50, 140, 0);
	LineTo(hdc, 250, 140);
	TextOutA(hdc, 105, 155, "Orinted edge", 13);
	MoveToEx(hdc, 50, 190, 0);
	LineTo(hdc, 250, 190);
	Ellipse(hdc, 227, 187, 233, 193);
	TextOutA(hdc, 105, 200, "Active point", 13);
	Ellipse(hdc, 140, 229, 146, 235);
	TextOutA(hdc, 105, 220, "11", 2);
	TextOutA(hdc, 100, 245, "Deactive point", 15);
	SetTextColor(hdc, SIRIY2);
	DeleteObject(p2);
	p2 = CreatePen(0, 4, SIRIY2);
	SelectObject(hdc, p2);
	TextOutA(hdc, 105, 265, "11", 2);
	Ellipse(hdc, 140, 269, 146, 275);
	DeleteObject(p2);
	p2 = CreatePen(0, 4, 0);
	SelectObject(hdc, p2);
	MoveToEx(hdc, 325, 0, 0);
	LineTo(hdc, 325, 600);
	MoveToEx(hdc, 325, 300, 0);
	LineTo(hdc, 0, 300);
	SetTextColor(hdc, BLACK);
	TextOutA(hdc, 25, 325, "Institute for Applied Systems Analysis", 39);
	TextOutA(hdc, 10, 350, "Department of mathematical analysis methods", 44);
	TextOutA(hdc, 45, 375, "Coursework first year student", 30);
	TextOutA(hdc, 75, 400, "Volodimir Volodko", 18);
	TextOutA(hdc, 125, 525, "Kiev", 5);
	TextOutA(hdc, 125, 550, "2017", 5);
	buttom(hwnd, 375, 500, 750, 550, "EXIT", 1);
	TextOutA(hdc, 375, 25, "Graph is a structure amounting to a set of objects in which some", 65);
	TextOutA(hdc, 375, 50, "pairs of the objects are in some sense \"related\".", 50);
	TextOutA(hdc, 375, 100, "Euler cycle - a cycle that contains each edge once.", 52);//If the image on the screen disappears, then click the arrow.
	TextOutA(hdc, 375, 450, "If the image on the screen disappears, then click the arrow.", 61);
	SelectObject(hdc, p1);
	SelectObject(hdc, b1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(p1);
	DeleteObject(p2);
	DeleteObject(b1);
	DeleteObject(b2);
	_getch();
	clear_windows(hwnd);
}
bool exit(HWND hwnd) 
{
	bool a = 1 , b = 0;
	char ch;
	buttom(hwnd, 200, 200, 600, 400, "Realy need exit?", 0);
	buttom_yn(hwnd , b);
	while (a)
	{
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 27:
			{
				a = 0;
				b = 1;
				break;
			}
			case 13:
			{
				a = 0;
				break;
			}
			case 77:
			{
				b = 1;
				buttom_yn(hwnd, b);
				break;
			}
			case 75:
				b = 0;
				buttom_yn(hwnd, b);
				break;
			}
		}
	}
	clear_windows(hwnd, 200, 200, 600, 460);
	return b;
};
void buttom_yn(HWND hwnd, bool b)//b=0 yes - obrane
{
	buttom(hwnd, 200, 410, 395, 460, "Yes" , !b);
	buttom(hwnd, 405, 410, 600, 460, "No", b);
}
void graph_menu(HWND hwnd, bool oriented)
{
	bool fl1 = 1;
	int k = 0, mas[9], sms = -2 + oriented;
	char ch;
	graph * q;
	for (int i = 0; i < 9; i++)
		mas[i] = 0;
	if (oriented)
		q = new graph_oriented;
	else
		q = new graph_simple;
	q->paint(hwnd);
	graph_buttom_paint(hwnd, k, mas);
	message(hwnd, sms);
	while (fl1)
	{
		Sleep(100);
		if (_kbhit())
		{
			sms = 100;
			ch = _getch();
			switch (ch)
			{
			case 27: {
				fl1 = exit(hwnd);
				break;
			}
			case 80:
			{
				switch (k)
				{
				case 0:
				case 1:
				{
					k = 2;
					break;
				}
				case 2:
				{
					k++;
					break;
				}
				case 3:
				case 4:
				{
					k = 6;
					break;
				}
				case 5:
				{
					k = 7;
					break;
				}
				case 6 :
				case 7 :
				{
					k = 8;
					break;
				}
				case 8 :
				{
					k++;
					break;
				}
				case 9 :
				case 10 :
				{
					k = 11;
					break;
				}
			default :
			{
				break;
			}
				}
				break;
			}
			case 72 :
			{
				switch (k)
				{
				case 2:
				{
					k = 0;
					break;
				}
				case 3:
				case 4:
				case 5:
				{
					k = 2;
					break;
				}
				case 6:
				{
					k = 3;
					break;
				}
				case 7:
				{
					k = 5;
					break;
				}
				case 8:
				{
					k = 6;
					break;
				}
				case 9:
				case 10:
				{
					k = 8;
					break;
				}
				case 11:
				case 12:
				case 13:
				case 14:
				{
					k = 9;
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case 75 :
			{
				switch (k)
				{
				case 1 :
				case 4 :
				case 5 :
				case 7 :
				case 10 :
				{
					k--;
					break;
				}
				case 11 :
				case 12 :
				case 13 :
				{
					k++;
					break;
				}
				case 0 :
				case 2 :
				case 3 :
				case 6 :
				case 8 :
				case 9 :
				{
					k = 12;
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case 77 :
			{
				switch (k)
				{
				case 0 :
				case 3 :
				case 4 :
				case 6 :
				case 9 :
				{
					k++;
					break;
				}
				case 12 :
				case 13 :
				case 14 :
				{
					k--;
					break;
				}
				default :
				{
					break;
				}
				}
				break;
			}
			case 13 :
			{
				switch (k)
				{
				case 0:
				{
					sms = q->actived_point(mas[0]);
					break;
				}
				case 1:
				{
					mas[0] = input_box(hwnd, 730, 95, 775, 145, mas[0], 16 );
					break;
				}
				case 2:
				{
					sms = 3 + q->add_edge(mas[1], mas[2], mas[3]);
					mas[6] = q->lenght(mas[5], mas[7]);
					break;
				}
				case 3:
				{
					mas[1] = input_box(hwnd, 525, 245, 580, 285, mas[1], 16);
					break;
				}
				case 4:
				{
					mas[2] = input_box(hwnd, 605, 245, 695, 285 , mas[2], 9999);
					break;
				}
				case 5:
				{
					mas[3] = input_box(hwnd, 720, 245, 775, 285, mas[3], 16);
					break;
				}
				case 6:
				{
					sms = 5 + q->deactived_point(mas[4]);
					mas[6] = q->lenght(mas[5], mas[7]);
					break;
				}
				case 7:
				{
					mas[4] = input_box(hwnd, 730, 310, 775, 360, mas[4], 16);
					break;
				}
				case 8:
				{
					sms = 7 + q->delete_edge(mas[5], mas[7]);
					mas[6] = 0;
					break;
				}
				case 9:
				{
					mas[5] = input_box(hwnd, 525, 460, 580, 500, mas[5], 16);
					mas[6] = q->lenght(mas[5], mas[7]);
					break;
				}
				case 10:
				{
					mas[7] = input_box(hwnd, 720, 460, 775, 500, mas[7], 16);
					mas[6] = q->lenght(mas[5], mas[7]);
					break;
				}
				case 11:
				{
					fl1 = exit(hwnd);
					break;
				}
				case 12:
				{
					mas[8] = input_box(hwnd, 450, 525, 495, 575,mas[8], 16);
					break;
				}
				case 13:
				{
					q->dijkstra(hwnd, mas[8]);
					Sleep(3000);
					break;
				}
				case 14:
				{
					sms = 9 + q->euler(hwnd);
					break;
				}
				default :
				{
					break;
				}
				}
			}
			default:
			{
				break;
			}
			}
			q->paint(hwnd);
			graph_buttom_paint(hwnd, k, mas);
			message(hwnd, sms);
		}
	}
	clear_windows(hwnd, 0, 0, 800, 600);
	delete q;
	return;
}
void graph_buttom_paint (HWND hwnd, int obrane, int m[])
	{
	char ch[9];
	clear_windows(hwnd, 500, 0, 800, 600);
	bool a[15];
	for (int i = 0; i < 15; i++)
		a[i] = 0;
	a[obrane] = 1;
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[0]);
	buttom(hwnd, 525 ,  95 , 705 , 145 , "Add a point"            , a[ 0] );
	buttom(hwnd, 730 ,  95 , 775 , 145 , ch, a[ 1] );
	buttom(hwnd, 525 , 170 , 775 , 220 , "Add edge"               , a[ 2] ); 
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[1]);
	buttom(hwnd, 525 , 245 , 580 , 285 , ch, a[ 3] );
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[2]);
	buttom(hwnd, 605 , 245 , 695 , 285 , ch, a[ 4] );
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[3]);
	buttom(hwnd, 720 , 245 , 775 , 285 , ch, a[ 5] );
	buttom(hwnd, 525 , 310 , 705 , 360 , "Destroy point"          , a[ 6] );
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[4]);
	buttom(hwnd, 730 , 310 , 775 , 360 , ch, a[ 7] );
	buttom(hwnd, 525 , 385 , 775 , 435 , "Remove edge"            , a[ 8] );
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[5]);
	buttom(hwnd, 525 , 460 , 580 , 500 , ch, a[ 9] );
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[6]);
	buttom(hwnd, 605 , 460 , 695 , 500 , ch, 0     );
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[7]);
	buttom(hwnd, 720, 460, 775, 500, ch, a[10]);
	buttom(hwnd, 525, 525, 775, 575, "Exit", a[11]);
	ch[0] = '\n';
	sprintf_s(ch, "%d", m[8]);
	clear_windows(hwnd, 0, 500, 500, 600);
	buttom(hwnd, 450 , 525 , 495 , 575 , ch                       , a[12] );
	buttom(hwnd, 225 , 525 , 425 , 575 , "Distance from point"    , a[13] );
	buttom(hwnd,  25 , 525 , 200 , 575 , "Euler cycle"            , a[14] );
	return;
}
int input_box(HWND hwnd, int Left, int Top, int Right, int Bottom,int post, int limit) // limit > 9
{
	HDC hdc = GetDC(hwnd);
	char m[9], key ;
	SetTextColor(hdc, RED);//так можешь сделать цвет текста
	SetBkColor(hdc, SIRIY2);//так фон
	sprintf_s(m, "%d", post, 8);
	buttom(hwnd, Left, Top, Right, Bottom, "", 1);
	TextOutA(hdc, Left + (Right - Left) / 2.0 - strlen(m)*3.5, Top + (Bottom - Top) / 2 - 9, m, strlen(m)+1);
	while (1)
	{
		if (_kbhit())
		{
			Sleep(80);
			key = _getch();
			switch (key)
			{
			case 48:
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
			{
				post = (post * 10 + (int) key - 48 );
				if (post >= limit) post = (int)key - 48;
				m[0] = '\n';
				sprintf_s(m, "%d", post);
				buttom(hwnd, Left, Top, Right, Bottom,"", 1 );
				TextOutA(hdc, Left + (Right - Left) / 2.0 - strlen(m)*3.5, Top + (Bottom - Top) / 2 - 9, m, strlen(m)+1);
				break;
			}
			case 27:
			case 13:
			{
				return post;
				break;
			}
			case 8:
			{
				post = post/10;
				m[0] = '\n';
				sprintf_s(m, "%d", post);
				buttom(hwnd, Left, Top, Right, Bottom, "", 1);
				TextOutA(hdc, Left + (Right - Left) / 2.0 - strlen(m)*3.5, Top + (Bottom - Top) / 2 - 9, m, strlen(m)+1);
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
	ReleaseDC(hwnd, hdc);
	return post;
}
void message(HWND hwnd, int g)
{
	HDC hdc = GetDC(hwnd);
	SetTextColor(hdc, RED);//так можешь сделать цвет текста
	SetBkColor(hdc, SIRIY1);//так фон
	switch (g)
	{
	case 0:
	{
		TextOutA(hdc, SMSX, SMSY, "The point was activated before", 31);
		break;
	}
	case 1:
	{
		TextOutA(hdc, SMSX, SMSY, "Point activated", 16);
		break;
	}
	case 2:
	{
		TextOutA(hdc, SMSX, SMSY, "Edge length changed", 20);
		break;
	}
	case 3:
	{
		TextOutA(hdc, SMSX, SMSY, "Unable to add an edge", 22);
		break;
	}
	case 4 :
	{
		TextOutA(hdc, SMSX, SMSY, "Edge added", 11);
		break;
	}
	case 5:
	{
		TextOutA(hdc, SMSX, SMSY, "The point is not active", 24);
		break;
	}
	case 6:
	{
		TextOutA(hdc, SMSX, SMSY, "Point deactivated", 18);
		break;
	}
	case 7:
	{
		TextOutA(hdc, SMSX, SMSY, "Edge found", 18);
		break;
	}
	case 8:
	{
		TextOutA(hdc, SMSX, SMSY, "Edge removed", 13);
		break;
	}
	case 9:
	{
		TextOutA(hdc, SMSX, SMSY, "Euler cycle does not exist", 27);
		break;
	}
	case 10:
	{
		TextOutA(hdc, SMSX, SMSY, "Euler cycle demonstrated", 25);
		break;
	}
	case -2:
	{
		TextOutA(hdc, SMSX, SMSY, "Simple graph", 13);
		break;
	}
	case -1:
	{
		TextOutA(hdc, SMSX, SMSY, "Oriented graph", 13);
		break;
	}
	default :
	{
		break;
	}
	}
	ReleaseDC(hwnd, hdc);
}