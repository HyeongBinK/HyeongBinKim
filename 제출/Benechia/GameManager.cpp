#include "GameManager.h"

GameManager::GameManager()
{
	SetToDefault();
	Draw::SetScreenSize();
}

void GameManager::GameSelect()
{
	while (1)
	{
		system("cls");

		int iSelect;
		Draw::BoxDraw(0, 0, m_iScreenWidth, m_iScreenHeight);

		Draw::DrawMidText("☆★베네치아★☆", m_iScreenWidth, m_iScreenHeight * 0.2);
		Draw::DrawMidText("1. Game Start", m_iScreenWidth, m_iScreenHeight * 0.4);
		Draw::DrawMidText("2. Ranking", m_iScreenWidth, m_iScreenHeight * 0.5);
		Draw::DrawMidText("3. Exit", m_iScreenWidth, m_iScreenHeight * 0.6);
		
		iSelect = Draw::MenuSelectCursor(3, 3, 24, m_iScreenHeight*0.4);
		switch (iSelect)
		{
		case 1:
			ShowStory();
			GameStart();
			break;
		case 2:
			ShowRank();
			break;
		case 3:
			return;
		}
	}
}

void GameManager::GameStart()
{
	int i = 0;
	while (1)
	{
		if ((m_iScreenHeight * 0.3) + i != m_iScreenHeight * 0.7 + 1)
		{
			Draw::EraseLine(m_iScreenWidth, (m_iScreenHeight * 0.3) + i);
			i++;
		}
		else
			break;
	}

	SetToDefault();
	MakeName();
	Ward_Manager.SetDefaultState();

	int MemoScore = m_iScore; //기존의 스코어를 기억시켜두고 값이 바뀌면 스테이터스창 갱신시키기위해 만듬
	int MemoLife = m_iPlayerLife; //기존의 목숨을 기억시켜두고 값이 바뀌면 스테이터스창 갱신시키기위해 만듬
	
	char ch = NULL;
	string AttackWard;
	bool ItemUseFlag = false;
	ShowStatus();
	ShowStage();
	
	while (1)
	{
		if (m_bGameClearFlag == true)
		{
			Draw::BoxErase(0, 0, m_iScreenWidth, m_iScreenHeight);
			Draw::DrawMidText("★ Game Clear ★", m_iScreenWidth, m_iScreenHeight*0.5);
			Rank_Manager.SaveRank(m_strPlayerName, m_iScore, m_iStage);
			return;
		}

		if (kbhit())
		{
			Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
			ch = getch();
			if (ch != NULL)
			{
				if (ch == BACKSPACE)
				{
					if (AttackWard.length() > 0)
					{
						Draw::EraseWard((m_iScreenWidth), (m_iScreenHeight*0.8), AttackWard.length());
						AttackWard.pop_back();
						Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
						cout << AttackWard;
					}
				}
				else if (ch == '1')
				{
					if (m_iEnemySpeedUpItem > 0)
					{
						Ward_Manager.Item_SpeedUP();
						ItemUseFlag = true;
						m_iEnemySpeedUpItem--;
					}
				}
				else if (ch == '2')
				{
					if (m_iEnemySpeedDownItem > 0)
					{
						Ward_Manager.Item_SpeedDown();
						ItemUseFlag = true;
						m_iEnemySpeedDownItem--;
					}
				}
				else if (ch == '3')
				{
					if (m_iEnemyStopItem > 0)
					{
						Ward_Manager.Item_StopEnemy();
						ItemUseFlag = true;
						m_iEnemyStopItem--;
					}
				}
				else if (ch == '4')
				{
					if (m_iEnemyClearItem > 0)
					{
						Ward_Manager.Item_ClearEnemy();
						ItemUseFlag = true;
						m_iEnemyClearItem--;
					}
				}
				else if (ch == ENTER)
				{
					if (AttackWard != "")
					{
						if (AttackWard.length() <= 20)
						{
							Ward_Manager.PlayerAttackEnenmy(AttackWard);
							Draw::EraseWard((m_iScreenWidth), (m_iScreenHeight*0.8), AttackWard.length());
							AttackWard = "";
							Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
						}
					}
				}
				else if (AttackWard.length() < ATTACKWARDLENGTHLIMIT)
				{
					AttackWard += ch;
					Draw::EraseWard((m_iScreenWidth - 10), (m_iScreenHeight*0.8), AttackWard.length() - 1);
					Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
					cout << AttackWard;
				}

				if (AttackWard.length() >= ATTACKWARDLENGTHLIMIT)
				{
					Draw::DrawMidText("20글자초과!!!", m_iScreenWidth, m_iScreenHeight*0.8 - 3);
					//Sleep(300);
					//Draw::EraseLine(m_iScreenWidth, m_iScreenHeight*0.8 - 3);
					//Draw::BoxErase((m_iScreenWidth*0.5) - 10, (m_iScreenHeight*0.8) - 2, (m_iScreenWidth * 0.5) + 10, (m_iScreenHeight*0.8) + 2);
				}
				else
				{
					Draw::EraseLine(m_iScreenWidth, m_iScreenHeight*0.8 - 3);
				}
			}
			
		}
		Ward_Manager.MakeRandomEnemy();
		Ward_Manager.FallEnemy(&m_iScore, &m_iPlayerLife);
		//Draw::BoxDraw((m_iScreenWidth*0.5) - 10, (m_iScreenHeight*0.8) - 2, (m_iScreenWidth * 0.5) + 10, (m_iScreenHeight*0.8) + 2);
		if (MemoScore != m_iScore || MemoLife != m_iPlayerLife)
		{
			if (MemoLife != m_iPlayerLife)
			{
				for (int i = 0; i < m_iPlayerLife; i++)
				{
					Draw::DrawPoint("  ", 7 + i, m_iScreenHeight + 2);
				}
				MemoLife = m_iPlayerLife;
			}
			else
				MemoScore = m_iScore;
			ShowStatus();
		}
		StageChange();
		if (ItemUseFlag == true)
		{
			ItemUseFlag = false;
			ShowStatus();
		}
		if (GameOverCheck() == true)
		{
			Draw::BoxErase(0, 0, m_iScreenWidth, m_iScreenHeight);
			Draw::DrawMidText("★ Game Over ★", m_iScreenWidth, m_iScreenHeight*0.5);
			Rank_Manager.SaveRank(m_strPlayerName, m_iScore, m_iStage);
			Sleep(300);
			return;
		}
	}
}

void GameManager::MakeName()
{
	char ch = NULL;
	string Dummyname;

	Draw::DrawMidText("이름입력", m_iScreenWidth, (m_iScreenHeight*0.8) - 5);
	Draw::BoxDraw((m_iScreenWidth*0.5) - 10, (m_iScreenHeight*0.8) - 2, (m_iScreenWidth * 0.5) + 10, (m_iScreenHeight*0.8) + 2);
	Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
	while (1)
	{
		
		ch = getch();
		if (ch != NULL)
		{
			if (ch == BACKSPACE)
			{
				if (Dummyname.length() > 0)
				{
					Draw::EraseWard((m_iScreenWidth), (m_iScreenHeight*0.8), Dummyname.length());
					Dummyname.pop_back();
					Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
					cout << Dummyname;
				}
			}
			else if (ch == SPACE)
			{

			}
			else if (ch == ENTER)
			{
				if (Dummyname != "")
				{
					if (Dummyname.length() <= 10)
					{
						m_strPlayerName = Dummyname;
						break;
					}
				}
			}
			else if (Dummyname.length() < NAMELENGTHLIMIT)
			{
				Dummyname += ch;
				Draw::EraseWard((m_iScreenWidth - 10), (m_iScreenHeight*0.8), Dummyname.length()-1);
				Draw::gotoxy((m_iScreenWidth), (m_iScreenHeight*0.8));
				cout << Dummyname;
			}
		
		}

		if (Dummyname.length() >= NAMELENGTHLIMIT)
		{
			Draw::DrawMidText("10글자초과!!!", m_iScreenWidth, m_iScreenHeight*0.8 - 3);
			//Sleep(300);
			//Draw::EraseLine(m_iScreenWidth, m_iScreenHeight*0.8 - 3);
			//Draw::BoxErase((m_iScreenWidth*0.5) - 10, (m_iScreenHeight*0.8) - 2, (m_iScreenWidth * 0.5) + 10, (m_iScreenHeight*0.8) + 2);
		}
		else
		{
			Draw::EraseLine(m_iScreenWidth, m_iScreenHeight*0.8 - 3);
		}
	}
	Draw::BoxErase((m_iScreenWidth*0.5) - 10, (m_iScreenHeight*0.8) - 2, (m_iScreenWidth * 0.5) + 10, (m_iScreenHeight*0.8) + 2);

}

void GameManager::StageChange()
{
	if (m_iScore >= 1000)
	{
		if (m_iStage >= 10)
		{
			m_bGameClearFlag = true;
			return;
		}

		m_iScore = 0;
		m_iStage++;
		Ward_Manager.StageUp();
		ShowStage();
		m_iPlayerLife = 10;
	}
}

void GameManager::ShowRank()
{
	Rank_Manager.ShowRank();
}

void GameManager::ShowStory()
{
	Draw::BoxErase(0, 0, m_iScreenWidth, m_iScreenHeight);
	int SkipKey;
	vector<string> BenechiaStory;
	string OneLine;
	string FileName = "베네치아_스토리.txt";
	float Line;

	ifstream load;

	load.open(FileName);

	load >> SkipKey;
	while (!load.eof())
	{
		getline(load, OneLine);
		BenechiaStory.push_back(OneLine);
	}
	
	Draw::BoxDraw((m_iScreenWidth*0.5)-10, (m_iScreenHeight*0.8) -2, (m_iScreenWidth * 0.5)+10, (m_iScreenHeight*0.8) +2);

	Draw::DrawMidText("Skip : s", m_iScreenWidth, m_iScreenHeight*0.8);
	char ch = NULL;
	Line = m_iScreenHeight * 0.3;

		int i = 1;
		int TotalCount = 0;
		int HeadLineCount = 0;
		for (auto iter = BenechiaStory.begin(); iter != BenechiaStory.end(); iter++)
		{
			if (kbhit())
			{
				ch = getch();
				if (ch == 's' || ch == 'S')
					return;
			}

			if (Line == m_iScreenHeight * 0.7)
			{
				HeadLineCount++;
				int Line2 = m_iScreenHeight * 0.3 + 1;
				for (auto iter = BenechiaStory.begin() + HeadLineCount; iter != BenechiaStory.begin() + TotalCount; iter++)
				{
					Draw::EraseLine(m_iScreenWidth, Line2);
					Draw::DrawMidText(*iter, m_iScreenWidth, Line2);
					Line2++;	
				}
			}
			else
			Line++;

			TotalCount++;
			if (Line == m_iScreenHeight * 0.7)
				Draw::EraseLine(m_iScreenWidth, Line);
			Draw::DrawMidText(*iter, m_iScreenWidth, Line);
			Sleep(300);
		}
		BenechiaStory.clear();

		for (int i = 1; i <= m_iScreenHeight * 0.4; i++)
		{
			Draw::EraseLine(m_iScreenWidth, i);
		}
		return;
	
}

void GameManager::ShowStatus()
{
	Draw::BoxDraw(2, m_iScreenHeight + 1, 20, m_iScreenHeight + 4); // Life
	Draw::BoxDraw((m_iScreenWidth*0.5) - 10, m_iScreenHeight + 1, (m_iScreenWidth * 0.5) + 10, m_iScreenHeight + 4); // Score
	Draw::BoxDraw(m_iScreenWidth - 13, m_iScreenHeight + 1, m_iScreenWidth - 1, m_iScreenHeight + 4); // Name
	Draw::DrawPoint("Life : ", 3, m_iScreenHeight + 2);
	Draw::DrawPoint("Score : ", m_iScreenWidth*0.5 - 9, m_iScreenHeight + 2);
	Draw::DrawPoint("Name : ", m_iScreenWidth- 12, m_iScreenHeight + 2);
	
	Draw::DrawPoint("SpeedUP : ", 3, m_iScreenHeight + 5);
	cout << m_iEnemySpeedUpItem;
	Draw::DrawPoint("SpeedDown : ", 15, m_iScreenHeight + 5);
	cout << m_iEnemySpeedDownItem;
	Draw::DrawPoint("StopEnemy : ", 30, m_iScreenHeight + 5);
	cout << m_iEnemyStopItem;
	Draw::DrawPoint("ClearEnemy : ", 45, m_iScreenHeight + 5);
	cout << m_iEnemyClearItem;
	
	for (int i = 0; i < m_iPlayerLife; i++)
	{
		Draw::DrawPoint("♥", 7 + i, m_iScreenHeight + 2);
	}
	Draw::DrawPoint(m_strPlayerName, m_iScreenWidth - 7, m_iScreenHeight + 2);
	Draw::DrawPoint(to_string(m_iScore),m_iScreenWidth*0.5, m_iScreenHeight + 2);
}

void GameManager::SetToDefault()
{
	m_iScreenWidth = WIDTH;
	m_iScreenHeight = HEIGHT;
	m_iPlayerLife = 10;
	m_iScore = 0;
	m_bGameClearFlag = false;
	m_strPlayerName = "???";
	m_iStage = 1;
	m_iEnemySpeedUpItem = 1; 
	m_iEnemySpeedDownItem = 1; 
	m_iEnemyStopItem = 1; 
	m_iEnemyClearItem = 1; 

}

void GameManager::ShowStage()
{
	for(int i =1; i < m_iScreenHeight - 1; i++)
	Draw::EraseLine(m_iScreenWidth, i);

	string ScreenText = "★ " + to_string(m_iStage) + "STAGE ★";
	Draw::DrawMidText(ScreenText, m_iScreenWidth, (m_iScreenHeight*0.5));
		
	Sleep(300);
	Draw::EraseLine(m_iScreenWidth, (m_iScreenHeight*0.5));
	Draw::BoxDraw((m_iScreenWidth*0.5) - 10, (m_iScreenHeight*0.8) - 2, (m_iScreenWidth * 0.5) + 10, (m_iScreenHeight*0.8) + 2);

}

bool GameManager::GameOverCheck()
{
	if (m_iPlayerLife <= 0)
		return true;
	else
		return false;
}

GameManager::~GameManager()
{
	Ward_Manager.ClearData();
	Rank_Manager.ClearRankData();
}
