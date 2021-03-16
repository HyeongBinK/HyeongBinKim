#pragma once
#include"BaseHeader.h"

class DrawManager
{
public:
	DrawManager();
private :
	int m_iWidth;
	int m_iHeight;
public:
	//void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void DrawMidText_TwoString(string str1, string str2, int x, int y);
	void DrawMidText_PlusHeadInt(int i, string str, int x, int y);
	void DrawMidText_PlusTailInt(int i, string str, int x, int y);
	void DrawBattleDammage(string str1, int Dammage, string str2, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	void DrawBorder();
	void DrawBorders(int Width, int Height, string WallShape); //게임모서리그리기
	void ChangeScreenSize(int NewWidth, int NewHeight); //화면크기변경
	void DrawPauseByGameScreen(int y);

	//void Preferences(); //환경설정(화면크기와 같은 항목)
	inline int GetWidth()
	{
		return m_iWidth;
	}

	inline int GetHeight()
	{
		return m_iHeight;
	}

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	~DrawManager();
};



