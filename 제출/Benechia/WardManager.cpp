#include "WardManager.h"

WardManager::WardManager()
{
	LoadWards();
	SetDefaultState();
}

void WardManager::LoadWards()
{
	ifstream load;
	load.open("Word.txt");
	if (!load.is_open())
	{
		return;
	}
	string Ward;
	while (!load.eof())
	{
		getline(load, Ward);
		Wards.push_back(Ward);
	}
	load.close();
}

int WardManager::MakeRandomXLocation()
{
	int Random_XLocation;

	Random_XLocation = rand() % (WIDTH*2 - 15) + 3;

	return Random_XLocation;
}

void WardManager::MakeRandomEnemy()
{
	if (clock() - m_iCurClock >= m_iEnemyMakeTerm)
	{
		int Count = 0;
		int RandomWardNumber;
		string RandomEnemyWard;
		Ward DummyWard;
		bool FindWard = false;
		bool OverLapWard = false;
		RandomWardNumber = (rand() % Wards.size());

		for (auto iter = Wards.begin(); iter != Wards.end(); iter++)
		{
			if (Count == RandomWardNumber)
			{
				RandomEnemyWard = *iter;
				FindWard = true;
				break;
			}
			Count++;
		}

		if (FindWard == true)
		{
			if (Enemy.size() == NULL)
			{
				DummyWard.MakeNewWard(RandomEnemyWard, MakeRandomXLocation(), m_iEnemyFallenSpeed);
				Enemy.push_back(DummyWard);
				DummyWard.Warddraw();
				m_iCurClock = clock();
			}
			else
			{
				for (auto iter = Enemy.begin(); iter != Enemy.end(); iter++)
				{
					if (iter->GetWard() == RandomEnemyWard)
					{
						OverLapWard = true;
						break;
					}
				}

				if (OverLapWard == true)
					MakeRandomEnemy();
				else
				{
					DummyWard.MakeNewWard(RandomEnemyWard, MakeRandomXLocation(), m_iEnemyFallenSpeed);
					Enemy.push_back(DummyWard);
					DummyWard.Warddraw();
					m_iCurClock = clock();
				}
			}

		}
	}
}

void WardManager::FallEnemy(int* PlayerScroe, int* PlayerLife)
{
	if (Enemy.size() != NULL)
	{
		if (m_iStopEnemyFallFlag == false)
		{
			for (auto iter = Enemy.begin(); iter != Enemy.end(); iter++)
			{
				iter->Live(clock());
				if (iter->GetDie() == true)
				{
					if (HEIGHT >= (HEIGHT*0.8) - 3 && HEIGHT <= (HEIGHT*0.8) + 1)
					{
						if (WIDTH < ((WIDTH * 0.5) + 10) * 2 && (WIDTH + iter->GetWard().length()) >((WIDTH * 0.5) - 10) * 2)
						{
							iter = Enemy.erase(iter);
							*(PlayerScroe) += m_iEnemyKillScore;
							return;
						}
					}

					Draw::EraseWard(iter->GetXLocation(), iter->GetYLocation(), iter->GetWard().length());

					if (iter == Enemy.end() - 1)
					{
						iter = Enemy.erase(iter);
						*(PlayerScroe) += m_iEnemyKillScore;
						return;
					}
					iter = Enemy.erase(iter);
					*(PlayerScroe) += m_iEnemyKillScore;
				}
				if (iter->GetAttackSuccees() == true)
				{
					iter = Enemy.erase(iter);
					*(PlayerLife) -= 1;
				}
			}
		}
	}
}

void WardManager::PlayerAttackEnenmy(string AttackWard)
{
	for (auto iter = Enemy.begin(); iter != Enemy.end(); iter++)
	{
		if (iter->GetWard() == AttackWard)
		{
			iter->Die();
			return;
		}
	}

	Draw::DrawMidText("해당적없음", WIDTH, HEIGHT*0.8 - 3);
}

void WardManager::StageUp()
{
	m_iEnemyKillScore -= 10;
	m_iEnemyMakeTerm -= 100;
	m_iEnemyFallenSpeed -= 20;
	if (Enemy.size() != NULL)
	{
		Enemy.clear();
	}
}

void WardManager::SetDefaultState()
{
	m_iCurClock = clock();
	m_iEnemyMakeTerm = FIRSTSTAGEENEMYMAKETERM;
	m_iEnemyFallenSpeed = FIRSTSTAGEENEMYSPEED;
	m_iEnemyKillScore = FIRSTSTAGEENEMYSCORE;
	m_iStopEnemyFallFlag = false;
	if (Enemy.size() != NULL)
	{
		Enemy.clear();
	}
}

void WardManager::ClearData()
{
	if (Wards.size() != 0)
		Wards.clear();
	if (Enemy.size() != 0)
		Enemy.clear();
}

void WardManager::Item_SpeedUP()
{
	for (auto iter = Enemy.begin(); iter != Enemy.end(); iter++)
	{
		iter->UserUseSpeedItem(m_iEnemyFallenSpeed - 100);
	}
}

void WardManager::Item_SpeedDown()
{
	for (auto iter = Enemy.begin(); iter != Enemy.end(); iter++)
	{
		iter->UserUseSpeedItem(m_iEnemyFallenSpeed + 100);
	}
}

void WardManager::Item_StopEnemy()
{
	m_iStopEnemyFallFlag = true;
	Sleep(2000);
	m_iStopEnemyFallFlag = false;
}

void WardManager::Item_ClearEnemy()
{
	if (Enemy.size() != NULL)
	{
		for (auto iter = Enemy.begin(); iter != Enemy.end(); iter++)
		{
			Draw::EraseWard(iter->GetXLocation(), iter->GetYLocation(), iter->GetWard().length());
		}
		Enemy.clear();
	}
}

WardManager::~WardManager()
{
	if (Enemy.size() != NULL)
		Enemy.clear();
	if (Wards.size() != NULL)
		Wards.clear();
}
