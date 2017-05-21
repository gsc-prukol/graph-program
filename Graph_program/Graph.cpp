#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#define PI 3.14159256
#define COORDS(b) 247+220*sin((22.5*b/180)*PI) , 247-220*cos((22.5*b/180)*PI), 253+220*sin((22.5*b/180)*PI) ,253- 220*cos((22.5*b/180)*PI) 
#define COORDS1(b) 245+240*sin(((22.5*b)/180)*PI) , 244-240*cos(((22.5*b)/180)*PI)
#define COORDX(b) ( 250+220*sin((22.5*b/180)*PI) )
#define COORDY(b) ( 250-220*cos((22.5*b/180)*PI) )
#define MS 0.1
#define MF 0.9
#define BLACK 0
#define M matrix
#define MAX 4294967295

void clear_windows(HWND hwnd, int Left, int Top, int Right, int Bottom);


class graph
{
protected:
	unsigned distances[16];
	int matrix[16][16];
	virtual void paint_edge(HWND hwnd, int s, int f) {};
	void paint_point(HWND hwnd, bool active, int number);
	bool paint_euler(HWND hwnd, int no_orientachion);
	int min_element(bool *);
	void paint_distances(HWND);
	virtual bool existence_euler() { return 0; };
public:
	graph();
	graph(graph &);
	void dijkstra(HWND, int);
	virtual int add_edge(int p1, int length, int p2) { return 1; };
	virtual int delete_edge(int p1, int p2) { return 1; };
	virtual bool euler(HWND) { return 0; };
	virtual void paint(HWND hwnd) {};
	int graph::lenght(int p1, int p2) { return M[p1][p2]; };
	virtual ~graph() {};
	bool actived_point(int);
	bool deactived_point(int);
};
class graph_simple : public graph
{
protected:
	void paint_edge(HWND hwnd, int s, int f);
	bool existence_euler();
public:
	int add_edge(int p1, int length, int p2);
	int	delete_edge(int p1, int p2);
	bool euler( HWND );
	void paint(HWND hwnd);
	};
class graph_oriented : public graph
{
protected:
	bool existence_euler();
	void paint_edge(HWND hwnd, int s, int f);
public:
	int add_edge(int point1, int length, int point2);
	int delete_edge(int point1, int point2);
	void paint(HWND);
	bool euler(HWND);
};


graph::graph()
{
	for (int i = 0; i < 16; i++)
	{
		distances[i] = 0;
		for (int j = 0; j < 16; j++)
			matrix[i][j] = 1;
	}
}
graph::graph(graph & origin)
{
	for (int i = 0; i < 16; i++)
	{
		distances[i] = origin.distances[i];
		for (int j = 0; j < 16; j++)
			matrix[i][j] = origin.matrix[i][j];
	}
}
bool graph::actived_point(int n)
{
	if (M[n][n])
		return 0;
	M[n][n] = 1;
	return 1;
}
bool graph::deactived_point(int n)
{
	if (!M[n][n])
		return 0;
	for (int i = 0; i < 16; i++)
	{
		M[i][n] = 0;
		M[n][i] = 0;
	}
	return 1;

}
void graph::dijkstra(HWND hwnd,int n)
{
	bool marks[16];
	int k;
	for (int i = 0; i < 16; i++)
	{
		marks[i] = 1;
		distances[i] = MAX;
	}
	distances[n] = 0;
	do
	{
		k = min_element( marks);
		if (k == -1) break;
		marks[k] = 0;
		for (int i = 0; i < 16; i++)
		{
			if ( (distances[i] > (distances[k] + M[k][i]) ) && M[k][i])
				distances[i] = distances[k] + M[k][i];
		}
	} while (k != -1);
	paint_distances(hwnd);
	return;
}
int graph::min_element(bool * marks)
{
	int temp = -1;
	unsigned m = MAX;
	for ( int i = 0 ; i < 16; i++)
		if (distances[i] < m && marks[i])
		{
			temp = i;
			m = distances[i];
		}
	return temp;
}
void graph::paint_distances(HWND hwnd)
{
	paint(hwnd);
	HDC hdc = GetDC(hwnd);
	HPEN p1, p2 = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	char m[11];
	p1 = (HPEN)SelectObject(hdc, p2);// Заносим перо в контекст рисования
	SetBkColor(hdc, RGB(190, 190, 190));
	for (int i = 0; i < 16; i++)
	{
		if (distances[i] != MAX) 
		{
			sprintf_s(m, "%u", distances[i]);
			TextOutA(hdc, COORDS1(i), m, strnlen_s(m, 11)+1);
		}
		else
		{
			TextOutA(hdc, COORDS1(i), "    ", 4);
		}
	}
	SelectObject(hdc, p1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(p1);
	DeleteObject(p2);
	return;
}
void graph::paint_point(HWND hwnd, bool active, int number)
{
	HDC hdc = GetDC(hwnd);
	HPEN p1, p2;
	char m[3];
	sprintf_s(m, "%d", number);
	if (active)
	{
		p2 = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 0, 0));//так можешь сделать цвет текста
	}
	else
	{
		p2 = CreatePen(PS_SOLID, 4, RGB(100, 100, 100));
		SetTextColor(hdc, RGB(100, 100, 100));//так можешь сделать цвет текста
	}
	p1 = (HPEN)SelectObject(hdc, p2);// Заносим перо в контекст рисования
	SetBkColor(hdc, RGB(190, 190, 190));

	Ellipse(hdc, COORDS(number));
	TextOutA(hdc, COORDS1(number), m, 2);
	SelectObject(hdc, p1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(p1);
	DeleteObject(p2);
	return;
}
bool graph::paint_euler(HWND hwnd, int noor)
{
	bool notexit = 0;
	int point1 = -1, point2;
	if (!existence_euler()) return 0;
	clear_windows(hwnd, 0, 0, 500, 500);
	for (int i = 0; i < 16; i++)
		paint_point(hwnd, M[i][i], i);
	for (int i = 0; i < 16; i++)
		if (distances[i])
		{
			point1 = i;
			break;
		}
	if (point1 != -1)
		notexit = 1;
	point2 = point1;
	while (notexit)
	{
		notexit = 0;
		for (int i = 0; i < 16; i++)
			if ((point1 != i) && M[point1][i] && (distances[i] != noor))
			{
				Sleep(450);
				paint_edge(hwnd, point1, i);
				distances[i]-=noor;
				distances[point1]--;
				delete_edge(point1, i);
				point1 = i;
				notexit = 1;
				break;
			}
	}
	Sleep(450);
	paint_edge(hwnd, point1, point2);
	return 1;
}


int graph_simple::add_edge(int p1, int length, int p2)
{
	if (p1 == p2 || length <= 0 || !M[p1][p1] || !M[p2][p2]) return 0;
	if (M[p1][p2])
	{
		M[p1][p2] = M[p2][p1] = length;
		return -1;
	}
	M[p1][p2] = M[p2][p1] = length;
	return 1;
}
int graph_simple::delete_edge(int p1, int p2)
{
	if (p1 == p2)
		return 0;
	if (M[p1][p2])
	{
		M[p1][p2] = M[p2][p1] = 0;
		return 1;
	}
	M[p1][p2] = M[p2][p1] = 0;
	return 1;
}
void graph_simple::paint_edge(HWND hwnd, int s, int f)
{
	LPPOINT lpp = 0;
	HDC hdc = GetDC(hwnd);
	HPEN p1, p2 = CreatePen(4, 2, RGB(0, 0, 0));
	p1 = (HPEN)SelectObject(hdc, p2);
	MoveToEx(hdc, COORDX(s), COORDY(s), lpp);
	LineTo(hdc, COORDX(f), COORDY(f));
	SelectObject(hdc, p1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(p1);
	DeleteObject(p2);
}
bool graph_simple::euler(HWND hwnd)
{
	graph_simple temp(*this);
	return temp.paint_euler(hwnd, 1);
}
void graph_simple::paint(HWND hwnd)
{
	clear_windows(hwnd, 0, 0, 500, 500);
	for (int i = 0; i < 16; i++)
	{
		paint_point(hwnd, M[i][i], i);
	}
	for (int i = 0; i < 16; i++)
		for (int j = i + 1; j < 16; j++)
			if (M[i][j]) paint_edge(hwnd, i, j);
	return;
}
bool graph_simple::existence_euler()
{
	int step;
	for (int i = 0; i < 16; i++)
	{
		step = 0;
		for (int j = 0; j < 16; j++)
			if (M[i][j] && (i != j))
				step++;
		if (step % 2)
			return 0;
		else
			distances[i] = step;
	}
	return 1;
}

int graph_oriented::add_edge(int p1, int length, int p2)
{
	if (p1 == p2 || length <= 0 || !M[p1][p1] || !M[p2][p2]) return 0;
	if (M[p1][p2])
	{
		M[p1][p2] = length;
		return -1;
	}
	M[p1][p2] = length;
	return 1;
}
int graph_oriented::delete_edge(int p1, int p2)
{
	if (p1 == p2)
		return 0;
	if (M[p1][p2])
	{
		M[p1][p2] = 0;
		return 1;
	}
	M[p1][p2] = 0;
	return 1;
}
void graph_oriented::paint_edge(HWND hwnd, int s,  int f)
{
	LPPOINT lppt = 0;
	HDC hdc = GetDC(hwnd);
	HPEN p1, p2 = CreatePen(4, 2, BLACK);
	HBRUSH b1 , b2 = CreateSolidBrush(0);
	p1 = (HPEN)SelectObject(hdc, p2);
	b1 = (HBRUSH)SelectObject(hdc, b2);
	MoveToEx(hdc, COORDX(s), COORDY(s), lppt);
	LineTo(hdc, COORDX(f), COORDY(f));
	SelectObject(hdc, p2);
	Ellipse(hdc, COORDX(s) * MS + COORDX(f) * MF - 3, COORDY(s) * MS + COORDY(f) * MF - 3, COORDX(s) * MS + COORDX(f) * MF + 3, COORDY(s) * MS + COORDY(f) * MF + 3);
	SelectObject(hdc, p1);
	SelectObject(hdc, b1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(p1);
	DeleteObject(p2);
	DeleteObject(b1);
	DeleteObject(b2);
}
bool graph_oriented::euler(HWND hwnd)
{
	graph_oriented temp(*this);
	return temp.paint_euler(hwnd, 0);
}
void graph_oriented::paint(HWND hwnd)
{
	clear_windows(hwnd, 0, 0, 500, 500);
	for (int i = 0; i < 16; i++)
	{
		paint_point(hwnd, M[i][i], i);
	}
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			if (M[i][j]) paint_edge(hwnd, i, j);
	return;
}
bool graph_oriented::existence_euler()
{
	int step1, step2;
	for (int i = 0; i < 16; i++)
	{
		step1 = step2 = 0;
		for (int j = 0; j < 16; j++)
		{
			if (M[i][j] && (i != j))
				step1++;
			if (M[j][i] && (i != j))
				step2++;
		}
		if (step1 != step2)
			return 0;
		else
			distances[i] = step1;
	}
	return 1;
}

void clear_windows(HWND hwnd, int Left = 0 , int Top = 0 , int Right = 800, int Bottom = 600)
{
	HDC hdc = GetDC(hwnd);
	HBRUSH b1, b2 = CreateSolidBrush(RGB(190, 190, 190));
	HPEN p1, p2 = CreatePen(PS_SOLID, 3, RGB(190, 190, 190));
	b1 = (HBRUSH)SelectObject(hdc, b2);
	p1 = (HPEN)SelectObject(hdc, p2);
	Rectangle(hdc, Left, Top, Right, Bottom);
	SelectObject(hdc, b1);
	SelectObject(hdc, p1);
	ReleaseDC(hwnd, hdc);
	DeleteObject(b1);
	DeleteObject(b2);
	DeleteObject(p1);
	DeleteObject(p2);
}