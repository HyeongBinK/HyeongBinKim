#pragma once
#include<iostream> //전체적인 기본코딩기능
#include<Windows.h> //시스템(퍼즈),(클스)
#include<fstream> //파일저장로딩
#include<string>  //string 사용하기위해
#include<conio.h> //getch()
#include<math.h> //랜덤함수
#include<vector> //단어들모음 , 데이터로드시
#include<time.h> //단어낙하속도 타이머
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////

#define UP 'w'
#define DOWN 's'
#define ENTER 13
#define SPACE 32
#define BACKSPACE 8
#define ESC 27
#define WIDTH 60
#define HEIGHT 30

namespace Draw
{
	static inline void gotoxy(const int& x, const int& y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	static void ErasePoint(const int& x, const int& y)
	{
		gotoxy(x * 2, y);
		cout << "  ";
		gotoxy(-1, -1);
		return;
	}

	static void EraseWard(const int& x, const int& y, const int& WardLength)
	{
		gotoxy(x, y);
		for (int i = 0; i < WardLength; i++)
		{
			cout << " ";
		}
		gotoxy(-1, -1);
		return;
	}

	static void EraseLine(const int& Width, const int& Height)
	{
		gotoxy(2, Height);
		for (int i = 2; i < Width * 2 - 2; i++)
		{
			cout << " ";
		}
		gotoxy(-1, -1);
		return;
	}

	static void DrawPoint(const string& str, const int& x, const int& y)
	{
		gotoxy(x * 2, y);
		cout << str;
		gotoxy(-1, -1);
		return;
	}

	static void DrawMidText(const string& str, int x, const int& y)
	{
		if (x > str.size() / 2)
			x -= str.size() / 2;
		gotoxy(x, y);
		cout << str;
		return;
	}

	static void TextDraw(const string& str, const int& x, const int& y)
	{
		gotoxy(x, y);
		cout << str;
	}



	static void BoxErase(int Start_x, const int& Start_y, const int& Width, const int& Height)
	{
		int i = 0;

		if (Start_x > Width)
			Start_x -= Width;
		for (int y = 1 + Start_y; y < Height - 1; y++)
		{
			gotoxy(2 + Start_x * 2, 1 + Start_y + i);
			for (int x = 0; x < Width - Start_x - 2; x++)
				cout << "  ";
			i++;
		}
		return;
	}

	static void SetScreenSize()
	{
		char buf[256];
		sprintf(buf, "mode con: cols=%d lines=%d ", WIDTH * 2, HEIGHT + 6);
		system(buf);
	}

	static void BoxDraw(int Start_x, const int& Start_y, const int& Width, const int& Height)
	{
		int i = 0;
		if (Start_x > Width)
			Start_x -= Width;

		for (int y = Start_y; y < Height; y++)
		{
			gotoxy(Start_x * 2, Start_y + i);
			if (y == Start_y)
			{
				cout << "┌";
				for (int x = 1; x < Width - Start_x - 1; x++)
					cout << "─";
				cout << "┐";
			}
			else if (y == Height - 1)
			{
				cout << "└";
				for (int x = 1; x < Width - Start_x - 1; x++)
					cout << "─";
				cout << "┘";
			}
			else
			{
				cout << "│";
				for (int x = 1; x < Width - Start_x - 1; x++)
					cout << "  ";
				cout << "│";
			}
			i++;
		}
		return;
	}

	static int MenuSelectCursor(const int& MenuLen, const int& AddCol, const int& x, int y)
	{
		int Select = 1;
		RED
			DrawPoint("▶", x, y);
		ORIGINAL
			while (1)
			{
				switch (getch())
				{
				case UP:
					if (Select - 1 >= 1)
					{
						ErasePoint(x, y);
						y -= AddCol;
						Select--;
					}
					break;
				case DOWN:
					if (Select + 1 <= MenuLen)
					{
						ErasePoint(x, y);
						y += AddCol;
						Select++;
					}
					break;
				case ENTER:
					return Select;
				}
				RED
					DrawPoint("▶", x, y);
				ORIGINAL
			}
	}
}
