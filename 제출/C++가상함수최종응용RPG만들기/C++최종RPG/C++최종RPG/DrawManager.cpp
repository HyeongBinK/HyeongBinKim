#include "DrawManager.h"
DrawManager::DrawManager()
{
	m_iWidth = BASEWIDTH;
	m_iHeight = BASEHEIGHT;
}

void DrawManager::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << " ";
	return;
}

void DrawManager::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	return;
}

void DrawManager::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}

void DrawManager::DrawPauseByGameScreen(int y)
{
	gotoxy(m_iWidth/2, y);
	system("pause");
	return;
}

void DrawManager::DrawMidText_TwoString(string str1, string str2, int x, int y)
{
	string str = str1 + str2;
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}

void DrawManager::DrawMidText_PlusHeadInt(int i, string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << i << str;
	return;
}

void DrawManager::DrawMidText_PlusTailInt(int i, string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str << i;
	return;
}

void DrawManager::DrawBattleDammage(string str1, int Dammage, string str2, int x, int y)
{
	string str = str1 + to_string(Dammage) + str2;
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}

void DrawManager::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void DrawManager::DrawBorders(int Width, int Height, string WallShape)
{
	for (int i = 0; i < Height; i++)
	{
		cout << WallShape;
		for (int j = 0; j < Width - 2; j++)
		{
			if (i == 0 || i == Height - 1)
				cout << WallShape;
			else
				cout << "  ";

		}
		cout << WallShape << endl;
	}
}

void DrawManager::DrawBorder()
{
	DrawBorders(m_iWidth, m_iHeight, "бс");
}

void DrawManager::ChangeScreenSize(int NewWidth, int NewHeight)
{
	m_iWidth = NewWidth;
	m_iHeight = NewHeight;
}

DrawManager::~DrawManager()
{
}
