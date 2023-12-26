#pragma once
#include<iostream>
#include<Windows.h>
class ConsoleControl
{
	COORD GetConsoleCursorPosition(HANDLE& hConsoleOutput);
public:
	ConsoleControl();
	void setColor(char*);
	void singleBorder(int x, int y, int z, int g);
	void setCursorPosition(int x, int y);
	void makeBorder(int row, int col);
	void makeBorder(int row);
	~ConsoleControl();
};

