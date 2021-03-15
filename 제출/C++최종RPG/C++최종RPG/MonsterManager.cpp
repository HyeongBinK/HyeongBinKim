#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	m_iMonsterMakeClock = clock();
	m_iMonsterMakeCoolTime = NORMAL_MONSTER_MAKE_COOLTIME;
	m_iFieldMonsterNum = 0;
	m_iBossSummonCount = 0;
}

int MonsterManager::MonsterSpecialItemDrop(int MonsterNumber)
{
	int num = (rand() % 10) + 1;
	if (num == 1)
	{
		switch (MonsterNumber)
		{
		case MOBNAME_eKINGGOB:
			return WEAPONNAME_eGOBKINGSWORD;
		case MOBNAME_eMINOTARUSKING:
			return WEAPONNAME_eMISRILLSWORD;
		case MOBNAME_eDEMONKING:
			return WEAPONNAME_eDEMONKINGSWORD;
		case MOBNAME_eHORNTAIL:
			return WEAPONNAME_eDRAGONSWORD;
		default :
			return NULL;
		}
	}
	else 
		return NULL;
}

void MonsterManager::LoadMonsterData(string LoadFileName)
{
	string CharacterImage, Name;
	int ClassNumber, MonsterNumber, Level, MaxHP, Atk, Shield, MagicShield, AttackSpeed, LifeStatus, GiveExp, GiveMaxMoney;
	Monster mob;
	string str2;
	ifstream load;
	char buf[30];
	char str[20] = ".txt";
	char cstr[20];
	strcpy(cstr, LoadFileName.c_str());
	sprintf(buf, "%s%s", cstr, str);
	load.open(buf);
	while (!load.eof())
	{
		load >> CharacterImage >> ClassNumber >> MonsterNumber >> Name >> Level >> MaxHP >> Atk
			>> Shield >> AttackSpeed >> LifeStatus >> GiveExp >> GiveMaxMoney;

		mob.InputMonsterData(CharacterImage, ClassNumber, MonsterNumber, Name, Level, MaxHP
			, Atk, Shield, AttackSpeed, LifeStatus, GiveExp, GiveMaxMoney);

		load >> str2;
		if (str2 == "NEXT" || str2 == "END")
		{
			MonstersData.push_back(mob);
			if (str2 == "END")
				break;
		}
	}
}

void MonsterManager::BossSummonCountUp()
{
	m_iBossSummonCount++;
}

void MonsterManager::MakeMonsterInDungeon(int MonsterNumber, Point PlayerLocation)
{
	bool MakeFlag;
	Point MonsterLoaction;
	Monster Mob;
	if (m_iFieldMonsterNum < FIELDMAXMONSTER)
	{
		if (clock() - m_iMonsterMakeClock >= m_iMonsterMakeCoolTime)
		{
			for (auto iter = MonstersData.begin(); iter != MonstersData.end(); iter++)
			{
				if (m_iBossSummonCount >= MAXBOSSGAGE)
				{
					MonsterNumber += 1;
					ResetBossSummonCount();
				}
				if (MonsterNumber == iter->GetMonsterNumber())
				{
					MakeFlag = true;
					MonsterLoaction.m_iX_Location = (rand() % BASEWIDTH - 5) + 3;
					MonsterLoaction.m_iY_Location = (rand() % BASEHEIGHT - 5) + 3;

					if (MonsterLoaction.m_iX_Location == PlayerLocation.m_iX_Location && MonsterLoaction.m_iY_Location == PlayerLocation.m_iY_Location)
						MakeFlag = false;

					if (MonsterLoaction.m_iX_Location == 0 || MonsterLoaction.m_iX_Location == BASEWIDTH)
						MakeFlag = false;

					if (MonsterLoaction.m_iY_Location == 0 || MonsterLoaction.m_iY_Location == BASEHEIGHT)
						MakeFlag = false;

					for (auto iter2 = InDungeonMonster.begin(); iter2 != InDungeonMonster.end(); iter2++)
					{
						if (MonsterLoaction.m_iX_Location == iter2->GetMonsterLocation().m_iX_Location && MonsterLoaction.m_iY_Location == iter2->GetMonsterLocation().m_iY_Location)
							MakeFlag = false;
					}

					if (MakeFlag == true)
					{
						Mob.InputMonsterData(iter->GetCharacterImage(), iter->GetClassNumber(), iter->GetMonsterNumber(), iter->GetName(), iter->GetLevel(), iter->GetMaxHP(),
					    iter->GetAtk(), iter->GetShield(), iter->GetAttackSpeed(), iter->GetLifeStatus(), iter->GetMonsterGiveExp(), iter->GetMonsterGiveMoney());
						Mob.ChangeMonsterLocation(MonsterLoaction.m_iX_Location, MonsterLoaction.m_iY_Location);
						InDungeonMonster.push_back(Mob);
						Draw_Manager.DrawPoint(Mob.GetCharacterImage(), Mob.GetMonsterLocation().m_iX_Location, Mob.GetMonsterLocation().m_iY_Location);
						m_iFieldMonsterNum++;
						m_iMonsterMakeClock = clock();
						return;
					}
					else
					MakeMonsterInDungeon(MonsterNumber, PlayerLocation);
				
				}
			}
		}
	}
}

void MonsterManager::DrawMonster()
{
	for (auto iter = InDungeonMonster.begin(); iter != InDungeonMonster.end(); iter++)
	{
		Draw_Manager.DrawPoint(iter->GetCharacterImage(), iter->GetMonsterLocation().m_iX_Location, iter->GetMonsterLocation().m_iY_Location);
	}
	
}

void MonsterManager::FieldMonsterDie(Point PlayerLocation)
{
	for (auto iter = InDungeonMonster.begin(); iter != InDungeonMonster.end(); iter++)
		{
			if (PlayerLocation.m_iX_Location == iter->GetMonsterLocation().m_iX_Location && PlayerLocation.m_iY_Location == iter->GetMonsterLocation().m_iY_Location)
			{
				iter = InDungeonMonster.erase(iter);
				m_iFieldMonsterNum--;
				break;
			}
		}
}

int MonsterManager::MonsterJowCheck(Point PlayerLocation)
{
	for (auto iter = InDungeonMonster.begin(); iter != InDungeonMonster.end(); iter++)
	{
		if (PlayerLocation.m_iX_Location == iter->GetMonsterLocation().m_iX_Location && PlayerLocation.m_iY_Location == iter->GetMonsterLocation().m_iY_Location)
			return iter->GetMonsterNumber();
	}
	return false;
}

void MonsterManager::SetJowMobData(int MonsterNumber)
{
	for (auto iter = MonstersData.begin(); iter != MonstersData.end(); iter++)
	{
		if(MonsterNumber == iter->GetMonsterNumber())
		JowMobData.InputMonsterData(iter->GetCharacterImage(), iter->GetClassNumber(), iter->GetMonsterNumber(), iter->GetName(), iter->GetLevel(), iter->GetMaxHP(),
			iter->GetAtk(), iter->GetShield(), iter->GetAttackSpeed(), iter->GetLifeStatus(), iter->GetMonsterGiveExp(), iter->GetMonsterGiveMoney());
	}
}

void MonsterManager::ResetBossSummonCount()
{
	m_iBossSummonCount = 0;
}

void MonsterManager::ChangeMonsterMakeClock(int NewClock)
{
	m_iMonsterMakeClock = NewClock;
}

void MonsterManager::EraseMonsterData()
{
	MonstersData.clear();
}

void MonsterManager::ResetMonsterInDungeon()
{
	for (auto iter = InDungeonMonster.begin(); iter != InDungeonMonster.end(); iter++)
	{
		Draw_Manager.ErasePoint(iter->GetMonsterLocation().m_iX_Location, iter->GetMonsterLocation().m_iY_Location);
	}
	InDungeonMonster.clear();

	m_iMonsterMakeClock = clock();
	m_iFieldMonsterNum = 0;
	m_iBossSummonCount = 0;
}

MonsterManager::~MonsterManager()
{
}
