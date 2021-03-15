#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
	
}

void PlayerManager::LevelUp()
{
	while (1)
	{
		if (m_iGetExp >= m_iNeedExp)
		{
			int Memo;
			Memo = m_iGetExp - m_iNeedExp;
			m_iLevel++;
			NeedExp_Change();
		
			m_iGetExp = Memo;
			m_iSkillPoint += 3;
			m_iStatPoint += 5;
			StatStatusChange();
			m_iHP = m_iMaxHP;
			m_iMP = m_iMaxMP;
		}
		else
			return;
	}
}

void PlayerManager::Use_Gold(int Gold)
{
	if (m_iOwnedGold >= Gold)
	m_iOwnedGold -= Gold;
}

void PlayerManager::MakePlayerName(string Name)
{
	m_strName = Name;
}

void PlayerManager::StatStatusChange()
{
	 m_iMaxHP = 50 + 10*m_iStr + 10*m_iLevel; 
	 m_iMaxMP = 20 + 5 * m_iLevel; 
	 m_iAtk = 10 + 5 * m_iStr + 2 * m_iDex;
	 m_iShield = 5 + 3 * m_iStr + m_iDex;
	 m_iAttackSpeed = 500 - 2* m_iDex; 
}

void PlayerManager::NeedExp_Change()
{
	m_iNeedExp = 10 + m_iLevel ^ 2;
}

void PlayerManager::Get_EXP(int GiveExp)
{
	m_iGetExp += GiveExp;
	LevelUp();
}

void PlayerManager::GetDeadPenalty()
{
	m_iGetExp *= 0.9;
	m_iHP = m_iMaxHP / 2;
	m_iMP = m_iMaxMP / 2;

}

bool PlayerManager::Use_Mp(int SkillMP)
{
	if (m_iMP - SkillMP >= 0)
	{
		m_iMP -= SkillMP;
		return true;
	}
	else
	{
		cout << "스킬마나부족" << endl;
		return false;
	}
}

void PlayerManager::ClassChange(int Num)
{
	m_iClassNumber = Num;
}

void PlayerManager::LocationChange(int LocationX, int LocationY)
{
	Location.m_iX_Location = LocationX;
	Location.m_iY_Location = LocationY;
}

//void PlayerManager::ChangeMapSize(int Width, int Height)
//{
//	m_iWidth = Width;
//	m_iHeight = Height;
//
//	PlayerLocationXY.m_iX_Location = Width * 0.5f;
//	PlayerLocationXY.m_iY_Location = Height * 0.5f;
//}

//void PlayerManager::PlayerMoveinDunGeon(char* ch)
//{
//	while (1)
//	{
//			DrawCharacter();
//
//			*ch = getch();
//
//			Draw_Manager.ErasePoint(PlayerLocationXY.m_iX_Location, PlayerLocationXY.m_iY_Location);
//
//		
//
//			switch (*ch)
//			{
//			case KEY_LEFT: //왼쪽
//				if (PlayerLocationXY.m_iX_Location - 2 >= 0)
//					PlayerLocationXY.m_iX_Location--;
//				break;
//			case KEY_RIGHT: //오른쪽
//				if (PlayerLocationXY.m_iX_Location + 2 < Draw_Manager.GetWidth())
//					PlayerLocationXY.m_iX_Location++;
//				break;
//			case KEY_UP: //위쪽
//				if (PlayerLocationXY.m_iY_Location - 2 >= 0)
//					PlayerLocationXY.m_iY_Location--;
//				break;
//			case KEY_DOWN: //아래쪽
//				if (PlayerLocationXY.m_iY_Location + 2 < Draw_Manager.GetHeight())
//					PlayerLocationXY.m_iY_Location++;
//				break;
//			case KEY_ENTER: //인던전중 메뉴창불러오기
//				return;
//			case KEY_ESC: //게임도중 강재종료
//				return;
//			default:
//				break;
//			/*default:
//				break;*/
//			}
//		}
//	
//}

void PlayerManager::DrawCharacter()
{
	Draw_Manager.DrawPoint(m_strCharacterImage, Location.m_iX_Location, Location.m_iY_Location);
}

void PlayerManager::SavePlayerCharacter(string SaveFileName, int i)
{
	ofstream save;
	string FileName;
	char cstr[50];
	string Tail = ".txt";

	FileName = SaveFileName + to_string(i) + Tail;

	strcpy(cstr, FileName.c_str());
	save.open(cstr);
	if (save.is_open())
	{
		save << m_strCharacterImage << endl;
		save << m_iClassNumber << endl;
		save << m_strName << endl;
		save << m_iLevel << endl;
		save << m_iMaxHP << endl;
		save << m_iMaxMP << endl;
		save << m_iHP << endl;
		save << m_iMP << endl;
		save << m_iAtk << endl;
		save << m_iShield << endl;
		save << m_iAttackSpeed << endl;
		save << m_iGetExp << endl;
		save << m_iNeedExp << endl;
		save << m_iLifeStatus << endl;
		
		save << m_iStatPoint << endl;
		save << m_iSkillPoint << endl;
		save << m_iStr << endl;
		save << m_iDex << endl;
		save << m_iOwnedGold << endl;

		//save << m_iWidth << endl;
		//save << m_iHeight << endl;
		save << m_iEquipWeaponNumber << endl;
		save << "END" << endl;
		save.close();
	}
	FileName = "SkillData" + to_string(i);
	Skill_Manager.SaveSkillData(FileName);
	return;
}

void PlayerManager::LoadPlayerCharacter(string LoadFileName, int i)
{
	ifstream load;
	char buf[30];
	string Tail = ".txt";
	char cstr[20];
	string str2;
	string FileName;
	
	if (i != 0)
		FileName = LoadFileName + to_string(i) + Tail;
	else
		FileName = LoadFileName + Tail;

	load.open(FileName);
	while (!load.eof())
	{
		load >> m_strCharacterImage;
		load >> m_iClassNumber;
		load >> m_strName;
		load >> m_iLevel;
		load >> m_iMaxHP;
		load >> m_iMaxMP;
		load >> m_iHP;
		load >> m_iMP;
		load >> m_iAtk;
		load >> m_iShield;
		load >> m_iAttackSpeed;
		load >> m_iGetExp;
		load >> m_iNeedExp;
		load >> m_iLifeStatus;
	
		load >> m_iStatPoint;
		load >> m_iSkillPoint;
		load >> m_iStr;
		load >> m_iDex;
		load >> m_iOwnedGold;

		//load >> m_iWidth;
		//load >> m_iHeight;
		load >> m_iEquipWeaponNumber;
		load >> str2;
		if (str2 == "END")
			break;
	}
	load.close();
	if(LoadFileName == "BasePlayerCharacter")
	Skill_Manager.LoadSkillData("BaseSkillData");
	else if (LoadFileName == "PlayerCharacterData")
	{
		FileName = "SkillData" + to_string(i);
		Skill_Manager.LoadSkillData(FileName);
	}
}

void PlayerManager::ItemEquip(int WeaponNumber)
{
	m_iEquipWeaponNumber = WeaponNumber;
}

void PlayerManager::ShowTotalStatus()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText_TwoString("캐릭터이미지 : ", m_strCharacterImage, Draw_Manager.GetWidth(), 3);
	Draw_Manager.DrawMidText_TwoString("캐릭터직업 : ", ClassNumbertoClassName(m_iClassNumber), Draw_Manager.GetWidth(), 4);
	Draw_Manager.DrawMidText_TwoString("캐릭터이름 : ", m_strName, Draw_Manager.GetWidth(), 5);
	Draw_Manager.DrawMidText_PlusTailInt(m_iLevel, "현재레밸 :", Draw_Manager.GetWidth(), 6);
	Draw_Manager.DrawMidText_PlusTailInt(m_iMaxHP, "최대체력 :", Draw_Manager.GetWidth(), 7);
	Draw_Manager.DrawMidText_PlusTailInt(m_iHP, "현재체력 :", Draw_Manager.GetWidth(), 8);
	Draw_Manager.DrawMidText_PlusTailInt(m_iMaxMP, "최대마나량 :", Draw_Manager.GetWidth(), 9);
	Draw_Manager.DrawMidText_PlusTailInt(m_iMP, "현재 마나량 :", Draw_Manager.GetWidth(), 10);
	Draw_Manager.DrawMidText_PlusTailInt(m_iStr, "현재투자된 STR :", Draw_Manager.GetWidth(), 11);
	Draw_Manager.DrawMidText_PlusTailInt(m_iDex, "현재투자된 DEX :", Draw_Manager.GetWidth(), 12);
	Draw_Manager.DrawMidText_PlusTailInt(m_iAtk, "공격력 :", Draw_Manager.GetWidth(), 13);
	Draw_Manager.DrawMidText_PlusTailInt(m_iShield, "방어력 :", Draw_Manager.GetWidth(), 14);
	Draw_Manager.DrawMidText_PlusTailInt(m_iAttackSpeed, "선공치 :", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawMidText_PlusTailInt(m_iGetExp, "현재까지습득한경험치 :", Draw_Manager.GetWidth(), 16);
	Draw_Manager.DrawMidText_PlusTailInt(m_iNeedExp, "래밸업에필요한경험치 :", Draw_Manager.GetWidth(), 17);
	Draw_Manager.DrawMidText_PlusTailInt(m_iStatPoint, "보유중인 스탯포인트 :", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawMidText_PlusTailInt(m_iSkillPoint, "보유중인 스킬포인트 :", Draw_Manager.GetWidth(), 19);
	Draw_Manager.DrawMidText_PlusTailInt(m_iOwnedGold, "보유중인 골드 :", Draw_Manager.GetWidth(), 20);
	Draw_Manager.DrawMidText_PlusTailInt(m_iEquipWeaponNumber, "장착중인무기번호 :", Draw_Manager.GetWidth(), 21);
	Draw_Manager.DrawPauseByGameScreen(22);

}

void PlayerManager::ClearSkillData()
{
	Skill_Manager.ClearSkillData();
}

string PlayerManager::ClassNumbertoClassName(int ClassNumber)
{
	switch (ClassNumber)
	{
	case CLASS_eCIVILIAN : 
		return "시민";
	case CLASS_eWARRIOR :
		return "전사";
	case CLASS_eHERO :
		return "히어로";
	default:
		return "클래스번호로드중오류발생";
	}
}

void PlayerManager::UpGradeStatusPoint()
{
	int Select;
	while (1)
	{
		system("cls");
		Draw_Manager.DrawBorder();
		Draw_Manager.DrawMidText_PlusHeadInt(m_iStatPoint, "의 스탯포인트 보유중", Draw_Manager.GetWidth(), 5);

		Draw_Manager.DrawMidText_PlusTailInt(m_iStr, "현재까지투자된 STR :", Draw_Manager.GetWidth(), 7);
		Draw_Manager.DrawMidText_PlusTailInt(m_iDex, "현재까지투자된 DEX :", Draw_Manager.GetWidth(), 9);
		Draw_Manager.DrawMidText("1.STR(공격력에 영향)", Draw_Manager.GetWidth(), 11);
		Draw_Manager.DrawMidText("2.DEX(공격속도에 영향)", Draw_Manager.GetWidth(), 13);
		/*
		DrawMidText("2.INT(마법사계열마력및 최대마나량에 영향)", BASEWIDTH, 9);
		DrawMidText("3.DEX(궁수계열공격력및 공격속도에 영향)", BASEWIDTH, 11);
		*/
		Draw_Manager.DrawMidText("3.돌아가기", Draw_Manager.GetWidth(), 15);
		Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 17);
		cin >> Select;
		switch (Select)
		{
		case STATUS_eSTR:
			if (m_iStatPoint > 0)
			{
				m_iStatPoint--;
				m_iStr++;
				StatStatusChange();
			}
			else 
				StatPointError();
			break;;
		case STATUS_eDEX:
			if (m_iStatPoint > 0)
			{
				m_iStatPoint--;
				m_iDex++;
				StatStatusChange();

			}
			else 
				StatPointError();
			break;
		case STATUS_eRETURN :
			return;
		default:
			break;
		}

	}
}

void PlayerManager::GetGold(int Gold)
{
	m_iOwnedGold += Gold;
}

void PlayerManager::ShowClassChange()
{
	system("cls");
	Draw_Manager.DrawBorder();
	int Select;

	switch (m_iClassNumber)
	{
	case CLASS_eCIVILIAN:
		Draw_Manager.DrawMidText("LV10이상일시 전직가능", Draw_Manager.GetWidth(), 9);
		Draw_Manager.DrawMidText("1.전사", Draw_Manager.GetWidth(), 11);

		/*	DrawMidText("2.궁수(Str베이스 2차로 패스파인더,레인저 있음)", BASEWIDTH,14);
			DrawMidText("3.마법사(Int베이스 2차로 불,얼음아크메이지 있음)", BASEWIDTH, 17);*/
		break;
	case CLASS_eWARRIOR:
		Draw_Manager.DrawMidText("LV50이상일시 전직가능", Draw_Manager.GetWidth(), 9);
		Draw_Manager.DrawMidText("1.히어로", Draw_Manager.GetWidth(), 11);
		/*
		DrawMidText("2.드래곤워리어(주무기: 창))", BASEWIDTH, 14);
			break;
		case m_eARCHER:
			DrawMidText("1.패스파인더(주무기: 에이션트보우)", BASEWIDTH, 11);
			DrawMidText("2.레인저(주무기: 활)", BASEWIDTH, 14);
			break;
		case m_eMAGICIAN:
			DrawMidText("1.불아크메이지)", BASEWIDTH, 11);
			DrawMidText("2.얼음아크메이지)", BASEWIDTH, 14);
			break;
		*/
		break;
	default:
		return;
	}
	Draw_Manager.DrawMidText("2.돌아가기", Draw_Manager.GetWidth(), 13);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 15);
	cin >> Select;

	switch (Select)
	{
	case 1:
		if (m_iClassNumber == CLASS_eCIVILIAN)
		{
			if (m_iLevel >= 10)
			{
				ClassChange(CLASS_eWARRIOR);
				Draw_Manager.DrawMidText("모험가에서 전사로 성공적으로 전직에 성공하였습니다", Draw_Manager.GetWidth(), 12);
			}
			else
				Draw_Manager.DrawMidText("레밸이부족합니다", Draw_Manager.GetWidth(), 12);
			cout << endl;
		}
		else if (m_iClassNumber == CLASS_eWARRIOR)
		{
			if (m_iLevel >= 50)
			{
				ClassChange(CLASS_eHERO);
				Draw_Manager.DrawMidText("전사에서 히어로로 성공적으로 전직에 성공하였습니다", Draw_Manager.GetWidth(), 12);
			}

			else
				Draw_Manager.DrawMidText("레밸이부족합니다", Draw_Manager.GetWidth(), 12);
			cout << endl;
		}

		Draw_Manager.DrawPauseByGameScreen(15);
		break;
	case 2:
		return;
	}
	if (m_iClassNumber == CLASS_eWARRIOR)
	{
		Skill_Manager.ChangeSkillCanBeAcquiredBySkillNumber(SKILLNAME_ePOWERSLASH);
	}
	else if (m_iClassNumber == CLASS_eHERO)
	{
		Skill_Manager.ChangeSkillCanBeAcquiredBySkillNumber(SKILLNAME_eCOMBOASSULT);
		Skill_Manager.ChangeSkillCanBeAcquiredBySkillNumber(SKILLNAME_eCOMBOEXTINGSION);
	}

}

void PlayerManager::UpgradeSkill_PlusPlayerData()
{
	Skill_Manager.UpGradeSkill(m_iClassNumber ,&m_iSkillPoint);
}

void PlayerManager::ShowMakeNameMenu()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("캐릭터이름입력 : ", Draw_Manager.GetWidth(), 15);
}

void PlayerManager::ShowSkillLearnError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("아직습득할수없는 스킬입니다.", Draw_Manager.GetWidth(), 15);
	//Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawPauseByGameScreen(18);
}

void PlayerManager::GoldError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("골드가부족해 아이템을 구입할수없습니다.", Draw_Manager.GetWidth(), 15);
	//Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawPauseByGameScreen(18);
}

void PlayerManager::StatPointError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("스탯포인트가부족하여 스탯을찍을수없습니다", Draw_Manager.GetWidth(), 15);
	//Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawPauseByGameScreen(18);
	
}

void PlayerManager::MPError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("MP가 부족해 스킬을 사용할수없습니다", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawPauseByGameScreen(18);
}

PlayerManager::~PlayerManager()
{

}