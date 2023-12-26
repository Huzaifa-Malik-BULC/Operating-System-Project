#include "ConsoleControl.h"
#include<iostream>
#include<Windows.h>
using namespace std;
ConsoleControl::ConsoleControl()
{
}

void ConsoleControl::setColor(char* s)
{
	system(s);
}

void ConsoleControl::setCursorPosition(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(console, position);
}

COORD ConsoleControl::GetConsoleCursorPosition(HANDLE &hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}


void ConsoleControl::makeBorder(int row, int col)
{
	++col;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int lastPoint;;
	pos = GetConsoleCursorPosition(console);
	for (int i = 1; i <= row; i++)
	{
		std::cout << "-";
	}
	setCursorPosition(pos.X-1, pos.Y + 1);
	for (int i = 1; i <= col; i++) 
	{
		std::cout << "|";
		for (int i = 1; i <= row ; i++) { std::cout << " "; }
		std::cout << "|";
		setCursorPosition(pos.X-1, pos.Y + i);
		if (i == col)
			setCursorPosition(pos.X, pos.Y + i);
		lastPoint = i;
	}
	for (int i = 1; i <= row; i++)
	{
		std::cout << "-";
	}
	setCursorPosition(pos.X, pos.Y + 1);
}

void ConsoleControl::makeBorder(int row)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos = GetConsoleCursorPosition(console);
	for (int i = 1; i <= row; i++)
	{
		std::cout << "-";
	}
	setCursorPosition(pos.X - 1, pos.Y + 1);
	std::cout << "|";
	for (int i = 1; i <= row; i++) { std::cout << " "; }
	std::cout << "|";
	setCursorPosition(pos.X, pos.Y + 2);
	for (int i = 1; i <= row; i++)
	{
		std::cout << "-";
	}
	setCursorPosition(pos.X, pos.Y + 1);
}

void ConsoleControl::singleBorder(int x, int y, int z, int g)
{
	int a, b, c, d;
	a = x; b = y; c = z, d = g;
	//We draw FRAME for the bar
	for (int i = x; i < y; i++)
	{
		setCursorPosition(i, z);
		cout << char(196);     // 2 horizontal lines
		setCursorPosition(i, g);
		cout << char(196);
	}
	for (int i = z + 1; i < g; i++)   //2 vertical lines
	{
		setCursorPosition(a, i);
		cout << char(179);
		setCursorPosition(b, i);
		cout << char(179);
	}
	setCursorPosition(a, z);   //top left
	cout << char(218);
	setCursorPosition(b, z);   //top right
	cout << char(191);
	setCursorPosition(a, g);  // bottom left
	cout << char(192);
	setCursorPosition(b, g);    //bottom right
	cout << char(217);
}

ConsoleControl::~ConsoleControl()
{
}
