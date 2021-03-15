#include "GameManager.h"

GameManager::GameManager()
{
	ScreenSizeSetting();
	m_bGameEndFlag = false;
	m_bExitDungeonFlag = false;
	m_bPlayerDeadFlag = false;
}

void GameManager::PlayGame()
{
	int Select;
	while (1)
	{
		m_bGameEndFlag = false;

		ShowStartMenu();
		cin >> Select;
		switch (Select)
		{
		case 1:
			NewGame();
			GameManipulation();
			break;
		case 2:
			if (LoadSlot() == true)
				GameManipulation();
			else 
				break;
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void GameManager::NewGame()
{
	string Name;
	Player_Manager.LoadPlayerCharacter("BasePlayerCharacter", 0);
	Weapon_Manager.LoadWeaponsData("BaseWeaponData");
	Monster_Manager.LoadMonsterData("BaseMonsterData");
	Player_Manager.ShowMakeNameMenu();
	cin >> Name;
	Player_Manager.MakePlayerName(Name);
}

void GameManager::SaveGame(int i)
{
	Player_Manager.SavePlayerCharacter("PlayerCharacterData" , i);
	Weapon_Manager.SaveWeaponsData("WeaponData"+ to_string(i));
	//Player_Manager.SavePlayerCharacter("PlayerCharacterData");
	//Weapon_Manager.SaveWeaponsData("WeaponData");
	ShowSaveAndLoadComplete();
}

void GameManager::LoadGame(int i)
{
	DataClear();
	Player_Manager.LoadPlayerCharacter("PlayerCharacterData" , i);
	Weapon_Manager.LoadWeaponsData("WeaponData" + to_string(i));
	/*Player_Manager.LoadPlayerCharacter("PlayerCharacterData");
	Weapon_Manager.LoadWeaponsData("WeaponData");*/
	Monster_Manager.LoadMonsterData("BaseMonsterData");
	ShowSaveAndLoadComplete();
}

void GameManager::DataClear()
{
	Monster_Manager.ResetMonsterInDungeon();
	Monster_Manager.EraseMonsterData();
	Weapon_Manager.ClearWeaponData();
	Player_Manager.ClearSkillData();
}

void GameManager::SaveSlot()
{
	string PlayerDataName = "PlayerCharacterData";
	string WeaponDataName = "WeaponData";
	string FileName;
	string Tail = ".txt";
	char FileNametoChar[30];
	int FileSlotNumber;
	int Select;
	FILE* f;

	//ifstream load;
	while (1)
	{
		system("cls");
		Draw_Manager.DrawBorder();
		Draw_Manager.DrawMidText("=====Save=====", Draw_Manager.GetWidth(), 10);
		//printf("=====Save=====\n");
		for (FileSlotNumber = 1; FileSlotNumber <= SAVELOADSLOTMAX; FileSlotNumber++)
		{
			char ch;
			FileName = PlayerDataName + to_string(FileSlotNumber)+ Tail;
			strcpy(FileNametoChar, FileName.c_str());
			f = fopen(FileNametoChar, "r");
			if (f == NULL)
				ch = 'x';
			else
				ch = 'o';
			//printf("%d번슬롯 : <파일여부 : %c>\n", i, ch);
			//cout << i << "번슬롯 : <파일여부 :" + ch + '>' << endl;
			Draw_Manager.DrawMidText(to_string(FileSlotNumber) + "번슬롯 : <파일여부 :" + ch + '>', Draw_Manager.GetWidth(), 10 + FileSlotNumber);
		}
		Draw_Manager.DrawMidText(to_string(FileSlotNumber) + "되돌아가기", Draw_Manager.GetWidth(), 10 + FileSlotNumber);
		Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 10 + FileSlotNumber + 2);
		cin >> Select;
		if (Select == FileSlotNumber)
			return;
		else if (Select > FileSlotNumber || Select < 1)
		{
			system("cls");
			Draw_Manager.DrawBorder();
			Draw_Manager.DrawMidText("1~10사이의 슬롯에만 저장로드하세요!", Draw_Manager.GetWidth(), 15);
		}
		else if (Select >= 1 && Select <= SAVELOADSLOTMAX)
		{
			SaveGame(Select);
			return;
		}
	}
}

bool GameManager::LoadSlot()
{
	string PlayerDataName = "PlayerCharacterData";
	//string WeaponDataName = "WeaponData";
	string FileName;
	string Tail = ".txt";
	char FileNametoChar[30];
	int FileSlotNumber;
	int Select;
	bool LoadStateFlag = false;
	FILE* f;

	//ifstream load;
	while (1)
	{
		system("cls");
		Draw_Manager.DrawBorder();

		Draw_Manager.DrawMidText("=====Load=====", Draw_Manager.GetWidth(), 10);
		for (FileSlotNumber = 1; FileSlotNumber <= SAVELOADSLOTMAX; FileSlotNumber++)
		{
			char ch;
			FileName = PlayerDataName + to_string(FileSlotNumber)+ Tail;
			strcpy(FileNametoChar, FileName.c_str());
			f = fopen(FileNametoChar, "r");
			if (f == NULL)
				ch = 'x';
			else
				ch = 'o';
			Draw_Manager.DrawMidText(to_string(FileSlotNumber) + "번슬롯 : <파일여부 :" + ch + '>', Draw_Manager.GetWidth(), 10 + FileSlotNumber);
		}
		Draw_Manager.DrawMidText(to_string(FileSlotNumber) + "되돌아가기", Draw_Manager.GetWidth(), 10 + FileSlotNumber);
		Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 10 + FileSlotNumber + 2);
		cin >> Select;
		if (Select == FileSlotNumber)
			break;
		else if (Select > FileSlotNumber || Select < 1)
		{
			system("cls");
			Draw_Manager.DrawBorder();
			Draw_Manager.DrawMidText("1~10사이의 슬롯에만 저장로드하세요!", Draw_Manager.GetWidth(), 15);
		}
		else if (Select >= 1 && Select <= SAVELOADSLOTMAX)
		{
			FileName = PlayerDataName + to_string(Select) + Tail;
			strcpy(FileNametoChar, FileName.c_str());
			f = fopen(FileNametoChar, "r");
			if (f == NULL)
			{
				system("cls");
				Draw_Manager.DrawBorder();
				Draw_Manager.DrawMidText("해당슬롯엔 세이브파일이없습니다", Draw_Manager.GetWidth(), 15);
				Draw_Manager.DrawPauseByGameScreen(16);
			}
			else
			{
				DataClear();
				LoadGame(Select);
				LoadStateFlag = true;
				break;
			}
		}
	}
	return LoadStateFlag;
}

void GameManager::ScreenSizeSetting()
{
	int Width = (Draw_Manager.GetWidth() * 2) + 1;
	int Height = Draw_Manager.GetHeight() + 5;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);
}

void GameManager::GameManipulation() 
{
	while (m_bGameEndFlag == false)
	{
		OutDungeonManipulation();
	}
	DataClear();
}

void GameManager::OutDungeonManipulation()
{
	if (m_bGameEndFlag == true)
		return;
	
	int Select;
	Draw_Manager.DrawBorder();
	ShowOutDungeonMenu();
	
	cin >> Select;
	switch (Select)
	{
		case OUTDUNGEON_eGOBSHOME : 
			InDungeonManipulation(MOBNAME_eGOB);
			break;
		case OUTDUNGEON_eMINOTASHOME :
			InDungeonManipulation(MOBNAME_eMINOTAURS);
			break;
		case OUTDUNGEON_eCULSEDTEMPLE :
			InDungeonManipulation(MOBNAME_eDEVIL);
			break;
		case OUTDUNGEON_eDRAGONNEST :
			InDungeonManipulation(MOBNAME_eWYVERN);
			break;
		case OUTDUNGEON_eWEAPONTRADER :
			Player_Manager.Use_Gold(Weapon_Manager.WeaponTrader(Player_Manager.GetOwnedGold()));
			break;
		case OUTDUNGEON_eCHARACTERINFORMATION :
			CharacterMenuManipulation();
			break;
		case OUTDUNGEON_eGAMESAVE :
			SaveSlot();
			break;
		case OUTDUNGEON_eGAMELOAD :
			LoadSlot();
			return;
		case OUTDUNGEON_eENDGAME :
			m_bGameEndFlag = true;
			return;
		default :
			break;
	}
}

void GameManager::InDungeonManipulation(int MonsterNumber)
{
	m_bExitDungeonFlag = false;
	//bool HitMonsterFlag = false;
	char ch = NULL;
	system("cls");
	Draw_Manager.DrawBorder();
	ShowInDungeonKeyRule();
	Monster_Manager.ChangeMonsterMakeClock(clock());
	Player_Manager.LocationChange(Draw_Manager.GetWidth() * 0.5f, Draw_Manager.GetHeight() * 0.5f);
	Player_Manager.DrawCharacter();
	while (m_bExitDungeonFlag == false)
	{
		Monster_Manager.MakeMonsterInDungeon(MonsterNumber, Player_Manager.GetPlayerLocation());
		if (kbhit())
		{
			ch = getch();
			Draw_Manager.ErasePoint(Player_Manager.GetPlayerLocation().m_iX_Location, Player_Manager.GetPlayerLocation().m_iY_Location);
			switch (ch)
			{
			case KEY_LEFT: //왼쪽
				if (Player_Manager.GetPlayerLocation().m_iX_Location - 2 >= 0)
					Player_Manager.LocationChange(Player_Manager.GetPlayerLocation().m_iX_Location - 1, Player_Manager.GetPlayerLocation().m_iY_Location);
				break;
			case KEY_RIGHT: //오른쪽
				if (Player_Manager.GetPlayerLocation().m_iX_Location + 2 < Draw_Manager.GetWidth())
					Player_Manager.LocationChange(Player_Manager.GetPlayerLocation().m_iX_Location + 1, Player_Manager.GetPlayerLocation().m_iY_Location);
				break;
			case KEY_UP: //위쪽
				if (Player_Manager.GetPlayerLocation().m_iY_Location - 2 >= 0)
					Player_Manager.LocationChange(Player_Manager.GetPlayerLocation().m_iX_Location, Player_Manager.GetPlayerLocation().m_iY_Location - 1);
				break;
			case KEY_DOWN: //아래쪽
				if (Player_Manager.GetPlayerLocation().m_iY_Location + 2 < Draw_Manager.GetHeight())
					Player_Manager.LocationChange(Player_Manager.GetPlayerLocation().m_iX_Location, Player_Manager.GetPlayerLocation().m_iY_Location + 1);
				break;
			case KEY_ENTER: //인던전중 메뉴창불러오기
				InDungeonSelectManipulation();
				ReDrawMap();
				Monster_Manager.ChangeMonsterMakeClock(clock());
				break;
			case KEY_ESC: //게임도중 강재종료
				m_bGameEndFlag = true;
				return;
			default:
				break;
			}
			Player_Manager.DrawCharacter();
		}
		if (Monster_Manager.GetInDungeonMonsterVectorFileSize() != NULL)
		{
			if (Monster_Manager.MonsterJowCheck(Player_Manager.GetPlayerLocation()) != false)
			{
				BattlePhase(Monster_Manager.MonsterJowCheck(Player_Manager.GetPlayerLocation()));
				if (m_bPlayerDeadFlag == true)
				{
					Monster_Manager.ResetMonsterInDungeon();
					m_bPlayerDeadFlag = false;
					return;
				}
				Monster_Manager.FieldMonsterDie(Player_Manager.GetPlayerLocation());
				ReDrawMap();
				Monster_Manager.ChangeMonsterMakeClock(clock());
			}
		}
	}
}

void GameManager::InDungeonSelectManipulation()
{
	system("cls");
	int Select;
	Draw_Manager.DrawBorder();
	ShowInDungeonMenu();

	cin >> Select;
	switch (Select)
	{
	case INDUNGEON_eCHARACTERINFORMATION :
		CharacterMenuManipulation();
		break;
	case INDUNGEON_eDUNGEONEXIT :
		Monster_Manager.ResetMonsterInDungeon();
		m_bExitDungeonFlag = true;
		return;
	case INDUNGEON_eRETURNTODUNGEON :
		return;
	default :
		break;
	}
}

void GameManager::ReDrawMap()
{
	system("cls");
	Draw_Manager.DrawBorder();
	ShowInDungeonKeyRule();
	Player_Manager.DrawCharacter();
	Monster_Manager.DrawMonster();
}

void GameManager::BattlePhase(int MonsterNumber)
{
	//int BattleTurn = 1;
	int Select;
	int MemoPlayerOriginalSpeed = Player_Manager.GetAttackSpeed(); //마비상태일때 스피드값이 바뀌기에 원래스피드값 기억
	int SpecialDropItemNumber = 0; //스페셜아이템드롭시 그아이템의 번호 0일시에는 드랍안된거입니다
	bool PhaseSkipFlag = false; //반동기 사용여부
	bool BattleResult = false;
	Monster_Manager.SetJowMobData(MonsterNumber);
	Weapon_Manager.SetWeaponAtkShieldSkillByNumber(Player_Manager.GetEquipWeaponNumber());
	//Weapon EquipWeaponData;
	//Weapon_Manager.SetEquipWeaponData(Player_Manager.GetEquipWeaponNumber());
	Monster Mob = Monster_Manager.GetJowMobData();
	system("cls");
	Draw_Manager.DrawBorder();
	while (1)
	{
		system("cls");
		//Draw_Manager.DrawMidText_PlusTailInt(BattleTurn, "경과턴 : ", Draw_Manager.GetWidth(), 2);
		//Draw_Manager.DrawMidText(Monster_Manager.GetJowMobData().GetCharacterImage(), Draw_Manager.GetWidth(), 2);
		Draw_Manager.DrawMidText_PlusTailInt(Mob.GetLevel(), Monster_Manager.GetJowMobData().GetName() + " LV : ", Draw_Manager.GetWidth(), 2);
		Draw_Manager.DrawMidText_PlusTailInt(Mob.GetHP(), "남은체력 : ", Draw_Manager.GetWidth(), 3);

		Draw_Manager.DrawMidText("VS", Draw_Manager.GetWidth(), 5);

		//Draw_Manager.DrawMidText(Player_Manager.GetCharacterImage(), Draw_Manager.GetWidth(), 6);
		Draw_Manager.DrawMidText_PlusTailInt(Player_Manager.GetLevel(), Player_Manager.GetName() + " LV : ", Draw_Manager.GetWidth(), 7);
		Draw_Manager.DrawMidText_PlusTailInt(Player_Manager.GetHP(), "남은체력 : ", Draw_Manager.GetWidth(), 8);
		Draw_Manager.DrawMidText_PlusTailInt(Player_Manager.GetCharacterMP(), "남은마력 : ", Draw_Manager.GetWidth(), 9);
		//반동으로 인해 플레이어만 데미지를입음 
		if (PhaseSkipFlag == true)
		{
			PhaseSkipFlag = false;
			DontMoveByCoolTime();
			BattlePhase_MonsterDammage(&Mob, Weapon_Manager.GetEquipWeaponShield());
			if (Player_Manager.GetHP() <= 0)
			{
				if (PlayerDeadByMonster(MemoPlayerOriginalSpeed) == true)
					return;
			}
		}


		Draw_Manager.DrawMidText("===============================================", Draw_Manager.GetWidth(), 12);
		Draw_Manager.DrawMidText("1.기본공격 2.스킬공격 3.도망가기", Draw_Manager.GetWidth(), 13);
		Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 14);
		cin >> Select;

		Draw_Manager.DrawMidText("===============================================", Draw_Manager.GetWidth(), 15);
		switch (Select)
		{
		case BATTLEPHASESELECT_eNORMALATTACK:
			//Player_Manager.GetSkillData().SetSkillData(SKILLNAME_eNORMALATTACK);
			BattleDammageCalculate(&Mob, Weapon_Manager.GetEquipWeaponAtk(), Weapon_Manager.GetEquipWeaponShield(), Weapon_Manager.GetEquipWeaponSKillData(), Player_Manager.GetSkillData().GetSkillAllDataBySkillNumber(SKILLNAME_eNORMALATTACK));
			break;
		case BATTLEPHASESELECT_eSKILLATTACK:
			int SkillSelect;
			Player_Manager.GetSkillData().UseSkillInBattlePhase();
			cin >> SkillSelect;
			if (SkillSelect == SKILLNAME_eRETURN)
				break;
			//Player_Manager.GetSkillData().SetSkillData(SkillSelect);
			if (Player_Manager.GetSkillData().GetSkillAllDataBySkillNumber(SkillSelect).GetSkillLevel() > 0)
			{
				if (Player_Manager.Use_Mp(Player_Manager.GetSkillData().GetSkillAllDataBySkillNumber(SkillSelect).GetSkillMPCost()) == true)
				{
					BattleDammageCalculate(&Mob, Weapon_Manager.GetEquipWeaponAtk(), Weapon_Manager.GetEquipWeaponShield(), Weapon_Manager.GetEquipWeaponSKillData(), Player_Manager.GetSkillData().GetSkillAllDataBySkillNumber(SkillSelect));
					if (Player_Manager.GetSkillData().GetSkillAllDataBySkillNumber(SkillSelect).GetSkillCoolTime() != 0)
						PhaseSkipFlag = true;
				}
				else
				{
					Player_Manager.MPError();
					break;
				}
			}
			else
				Player_Manager.GetSkillData().SkillUseError();
			break;
		case BATTLEPHASESELECT_eRUNFROMBATTLE:
			return;
		}

		//마비상태가될시 스피드값하락
		if (Mob.GetLifeStatus() == LIFESTATUS_eON_PARALYSIS)
			Mob.ChangeAttackSpeedByParalysys(9999);
		if (Player_Manager.GetLifeStatus() == LIFESTATUS_eON_PARALYSIS)
			Player_Manager.ChangeAttackSpeedByParalysys(9999);
		
		
		//둘다 독이나 기타등의 이유로 피가 0이되었을시엔 플레이어가 판정승함
		if (Mob.GetHP() <= 0)
		{
			Mob.LifeStatusChange(LIFESTATUS_eDEAD);
		}
		else if (Player_Manager.GetHP() <= 0)
		{
			Player_Manager.LifeStatusChange(LIFESTATUS_eDEAD);
		}

		//죽은쪽을 기준으로 결과(보상)창출력
		if (PlayerDeadByMonster(MemoPlayerOriginalSpeed) == true)
			return;
		if (Mob.GetLifeStatus() == LIFESTATUS_eDEAD)
		{
			//몬스터 드랍골드
			int RandomMoney = 0;
			while (1)
			{
				RandomMoney = (rand() % Monster_Manager.GetJowMobData().GetMonsterGiveMoney());
				if (RandomMoney >= Monster_Manager.GetJowMobData().GetMonsterGiveMoney() / 2)
					break;
			}
			Player_Manager.GetGold(RandomMoney);
			//보스몹특별아이템 드랍관련부분 중복획득시 상품가격의 절반획득
			SpecialDropItemNumber = Monster_Manager.MonsterSpecialItemDrop(Monster_Manager.GetJowMobData().GetMonsterNumber());
			if (Weapon_Manager.FindWeaponGotFlag(SpecialDropItemNumber) == true)
			{
				Player_Manager.GetGold(Weapon_Manager.WeaponNumberToWeaponPride(SpecialDropItemNumber));
			}
			else 
				Weapon_Manager.WeaponGet(SpecialDropItemNumber);
			//보스몬스터소환게이지관련부분
			Monster_Manager.BossSummonCountUp();
			if (Monster_Manager.GetJowMobData().GetClassNumber() == CLASS_eBOSSMONSTER)
				Monster_Manager.ResetBossSummonCount();
			//승리인터페이스 
			ShowVictory(Monster_Manager.GetJowMobData().GetMonsterGiveExp(), RandomMoney, SpecialDropItemNumber);
			//경험치획득
			Player_Manager.Get_EXP(Monster_Manager.GetJowMobData().GetMonsterGiveExp());
			Player_Manager.ChangeAttackSpeedByParalysys(MemoPlayerOriginalSpeed);
			return;
		}
	}
}

bool GameManager::PlayerDeadByMonster(int MemoPlayerOriginalSpeed)
{
	if (Player_Manager.GetLifeStatus() == LIFESTATUS_eDEAD)
	{
		Player_Manager.GetDeadPenalty();
		YouDied();
		Player_Manager.LifeStatusChange(LIFESTATUS_eNORMAL);
		Player_Manager.ChangeAttackSpeedByParalysys(MemoPlayerOriginalSpeed);
		m_bPlayerDeadFlag = true;
		return true;
	}
	return false;
}

void GameManager::BattleDammageCalculate(Monster* JowMob, int WeaponAtk, int WeaponShield, WeaponSkill WeaponSkillData, Skill UseSKill)
{
	int TrueDammage;
	//마비독상태체크(마비상태일시 스피드값이 2배가되어 느려짐(수치가낮을수록선공))(독은 최대체력의 5프로지속데미지)
	//스피드수치가 적은쪽이 선공
	//스피드가 같을시 플레이어쪽이 선공
	
	//플레이어선공
	if (Player_Manager.GetAttackSpeed() <= Monster_Manager.GetJowMobData().GetAttackSpeed())
	{
		BattlePhase_PlayerDammage(JowMob, WeaponAtk, WeaponSkillData, UseSKill);
		if (JowMob->GetLifeStatus() == LIFESTATUS_eDEAD)
		{
			cout << endl;
			Draw_Manager.DrawPauseByGameScreen(12);
			return;
		}
		else
			Draw_Manager.DrawPauseByGameScreen(12);
		BattlePhase_MonsterDammage(JowMob, WeaponShield);
		Draw_Manager.DrawPauseByGameScreen(12);
	}
	//몬스터선공
	else if (Player_Manager.GetAttackSpeed() > Monster_Manager.GetJowMobData().GetAttackSpeed())
	{
		BattlePhase_MonsterDammage(JowMob, WeaponShield);
		if (Player_Manager.GetLifeStatus() == LIFESTATUS_eDEAD)
		{
			cout << endl;
			Draw_Manager.DrawPauseByGameScreen(12);
			return;
		}
		else
			Draw_Manager.DrawPauseByGameScreen(12);
		BattlePhase_PlayerDammage(JowMob, WeaponAtk, WeaponSkillData, UseSKill);
		Draw_Manager.DrawPauseByGameScreen(12);

	}

	return;
}

void GameManager::BattlePhase_MonsterDammage(Monster* JowMob, int WeaponShield)
{
	int TrueDammage = 0;
	//플레이어쪽 데미지입는방식
	if (JowMob->GetAtk() - Player_Manager.GetShield() - WeaponShield <= 0)
		TrueDammage = 0;
	else
		TrueDammage = JowMob->GetAtk() - Player_Manager.GetShield() - WeaponShield;

	Player_Manager.Get_Dammage(TrueDammage);
	Draw_Manager.DrawBattleDammage(Player_Manager.GetName() + "이(가) ", TrueDammage, "의 데미지를 " + Monster_Manager.GetJowMobData().GetName() + "에 의해 입었다", Draw_Manager.GetWidth(), 10);

	//독상태일시 독에의해 입은 데미지출력
	if (JowMob->GetLifeStatus() == LIFESTATUS_eON_POISON)
	{
		JowMob->Get_Dammage(JowMob->GetMaxHP() /20 );
		Draw_Manager.DrawBattleDammage(JowMob->GetName() + "가 독에의해", JowMob->GetMaxHP() / 20, "의 데미지를입었다", Draw_Manager.GetWidth(), 11);
	}
}

void GameManager::BattlePhase_PlayerDammage(Monster* JowMob, int WeaponAtk, WeaponSkill WeaponSkillData, Skill UseSKill)
{
	int TrueDammage = 0;
	if ((Player_Manager.GetAtk() + WeaponAtk) * UseSKill.GetSkillDammagePerCent() / 100 - JowMob->GetShield() <= 0)
		TrueDammage = 0;
	else
		TrueDammage = (Player_Manager.GetAtk() + WeaponAtk) * UseSKill.GetSkillDammagePerCent() / 100;

	JowMob->Get_Dammage(TrueDammage);
	if (WeaponSkillData.GetWeaponIntrinsicEffect() == SPECIALEFFECT_ePOISON_EFFECT)
		JowMob->LifeStatusChange(LIFESTATUS_eON_POISON);
	if (WeaponSkillData.GetWeaponIntrinsicEffect() == SPECIALEFFECT_ePARAIYSIS_EFFECT)
		JowMob->LifeStatusChange(LIFESTATUS_eON_PARALYSIS);

	Draw_Manager.DrawBattleDammage(JowMob->GetName() + "이(가) ", TrueDammage, "의 데미지를 " + Player_Manager.GetName() + "에 의해 입었다", Draw_Manager.GetWidth(), 10);
	//독상태일시 독에의해 입은 데미지출력
	if (Player_Manager.GetLifeStatus() == LIFESTATUS_eON_POISON)
	{
		Player_Manager.Get_Dammage(Player_Manager.GetMaxHP() / 20);
		Draw_Manager.DrawBattleDammage("독상태에의해", Player_Manager.GetMaxHP() / 20, "의 데미지를입었다", Draw_Manager.GetWidth(), 11);
	}
}

//void GameManager::WeaponTraderManipulation()
//{
//	
//	int Select;
//	Draw_Manager.DrawBorder();
//	ShowWeaponTraderMenu();
//	cin >> Select;
//	switch (Select)
//	{
//	case WEAPONNAME_eSHORTSWORD :
//		if (Player_Manager.Use_Gold(WEAPONPRIDE_eSHORTSWORD) == true)
//		{
//			Weapon_Manager.WeaponGet(WEAPONNAME_eSHORTSWORD);
//		}
//		else
//			Player_Manager.GoldError();
//		break;
//	case WEAPONNAME_eLONGSWORD :
//		if (Player_Manager.Use_Gold(WEAPONPRIDE_eLONGSWORD) == true)
//		{
//			Weapon_Manager.WeaponGet(WEAPONNAME_eLONGSWORD);
//		}
//		else
//			Player_Manager.GoldError();
//		break;
//	case WEAPONNAME_eBUSTERSWORD :
//		if (Player_Manager.Use_Gold(WEAPONPRIDE_eBUSTERSWORD) == true)
//		{
//			Weapon_Manager.WeaponGet(WEAPONNAME_eBUSTERSWORD);
//		}
//		else
//			Player_Manager.GoldError();
//		break;
//	default :
//		break;
//	}
//}


void GameManager::CharacterMenuManipulation()
{
	int MemoWeaponNumber = 0;
	int Select;
	while (1)
	{
		Draw_Manager.DrawBorder();
		ShowCharacterMenu();
		cin >> Select;
		switch (Select)
		{
		case CHARACTERINFORMATION_eSTATUS:
			Player_Manager.ShowTotalStatus();
			break;
		case CHARACTERINFORMATION_eUPGRADESTATUS:
			Player_Manager.UpGradeStatusPoint();
			break;
		case CHARACTERINFORMATION_eSKILL:
			Player_Manager.UpgradeSkill_PlusPlayerData();
			break;
		case CHARACTERINFORMATION_eCLASSCHANGE :
			Player_Manager.ShowClassChange();
			break;
		case CHARACTERINFORMATION_eWEAPON :
			MemoWeaponNumber = Weapon_Manager.WeaponChange(Player_Manager.GetEquipWeaponNumber(), Player_Manager.GetLevel());
			if (MemoWeaponNumber != 0)
				Player_Manager.ItemEquip(MemoWeaponNumber);
			break;
		case CHARACTERINFORMATION_eRETURN :
			return;
		default :
			break;
		}
	}
}

//void GameManager::ChangeWeaponMenu()
//{
//	int Select;
//	while (1)
//	{
//		Weapon_Manager.ShowWeaponMenu(Player_Manager.GetEquipWeaponNumber());
//		cin >> Select;
//		switch (Select)
//		{
//		case WEAPONNAME_eSHORTSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eSHORTSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eSHORTSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eLONGSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eLONGSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eLONGSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eBUSTERSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eBUSTERSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eBUSTERSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eGOBKINGSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eGOBKINGSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eGOBKINGSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eMISRILLSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eMISRILLSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eMISRILLSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eDEMONKINGSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eDEMONKINGSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eDEMONKINGSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eDRAGONSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eDRAGONSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eDRAGONSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eETERNALSWORD :
//			if (Weapon_Manager.FindWeaponEquipLimitLevel(WEAPONNAME_eETERNALSWORD) <= Player_Manager.GetLevel())
//				ChangeWeapon(WEAPONNAME_eETERNALSWORD);
//			else
//				Weapon_Manager.ShowWeaponEquipError();
//			break;
//		case WEAPONNAME_eRETURN :
//			return; 
//		default :
//			break;
//		}
//	}
//}

void GameManager::ChangeWeapon(int WeaponNumber)
{

	if (Weapon_Manager.FindWeaponGotFlag(WeaponNumber) == true)
		Player_Manager.ItemEquip(WeaponNumber);
	else
		Weapon_Manager.ShowWeaponEquipError();
}

//void GameManager::UpgradeSkill()
//{
//	int Select;
//	while (1)
//	{
//		Skill_Manager.ShowAndUpgradeSkill(Player_Manager.GetClassNumber(), Player_Manager.GetSkillPoint());
//		cin >> Select;
//		switch (Select)
//		{
//		case SKILLNAME_ePOWERSLASH:
//			if (Player_Manager.Use_SkillPoint() == true)
//				Skill_Manager.SkillLevelUp(SKILLNAME_ePOWERSLASH);
//			break;
//		case SKILLNAME_eCOMBOASSULT:
//			if (Player_Manager.Use_SkillPoint() == true)
//				Skill_Manager.SkillLevelUp(SKILLNAME_eCOMBOASSULT);
//			break;
//		case SKILLNAME_eCOMBOEXTINGSION:
//			if (Player_Manager.Use_SkillPoint() == true)
//				Skill_Manager.SkillLevelUp(SKILLNAME_eCOMBOEXTINGSION);
//			break;
//		case SKILLNAME_eRETURN:
//			return;
//		default: break;
//		}
//	}
//}


void GameManager::ShowStartMenu()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("RPG Game", Draw_Manager.GetWidth(), 7);
	Draw_Manager.DrawMidText("1. NewGame", Draw_Manager.GetWidth(), 10);
	Draw_Manager.DrawMidText("2. LoadGame", Draw_Manager.GetWidth(), 13);
	Draw_Manager.DrawMidText("3. EndGame", Draw_Manager.GetWidth(), 16);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 19);
}

void GameManager::ShowVictory(int GiveExp, int Gold, int SpecialItem)
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("몬스터에게서 승리하였습니다.", Draw_Manager.GetWidth(), 12);
	Draw_Manager.DrawMidText_PlusHeadInt(GiveExp, "의 경험치를 획득하였습니다.", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawMidText_PlusHeadInt(Gold, "의 골드를 획득하였습니다.", Draw_Manager.GetWidth(), 17);
	if(SpecialItem != 0)
	Draw_Manager.DrawMidText_TwoString(Weapon_Manager.WeaponNumberToWeaponName(SpecialItem), "을 특별보상으로 획득하였습니다.", Draw_Manager.GetWidth(), 19);
	//Draw_Manager.DrawMidText("아무키나누르면 다음창으로 이동", Draw_Manager.GetWidth(), 21);
	cout << endl;
	Draw_Manager.DrawPauseByGameScreen(22);
	//DrawMidText_PlusInt(KillNum, "번 해당몬스터를 사냥하였습니다.", m_iWidth, 18);
}

void GameManager::YouDied()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("YOU DIED", Draw_Manager.GetWidth(), 13);
	Draw_Manager.DrawMidText("Continue?(press AnyKey)", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawMidText("컨티뉴시 패널티로", Draw_Manager.GetWidth(), 17);
	Draw_Manager.DrawMidText("경험치획득량 하락 & 체력마나치절반으로 부활", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawPauseByGameScreen(20);
}

void GameManager::ShowInDungeonMenu()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("1.캐릭터정보", Draw_Manager.GetWidth(), 12);
	Draw_Manager.DrawMidText("2.던전나가기", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawMidText("3.던전으로되돌아가기", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 20);
}

void GameManager::ShowCharacterMenu()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("1.스테이터스", Draw_Manager.GetWidth(), 8);
	Draw_Manager.DrawMidText("2.스테이터스투자", Draw_Manager.GetWidth(), 10);
	Draw_Manager.DrawMidText("3.스킬습득현황및 투자", Draw_Manager.GetWidth(), 12);
	Draw_Manager.DrawMidText("4.전직하기", Draw_Manager.GetWidth(), 14);
	Draw_Manager.DrawMidText("5.아이템정보", Draw_Manager.GetWidth(), 16);
	Draw_Manager.DrawMidText("6.되돌아가기", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 20);
}

void GameManager::ShowOutDungeonMenu()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("1.고블린집락으로 향한다", Draw_Manager.GetWidth(), 4);
	Draw_Manager.DrawMidText("2.미노타우루스의 둥지로 향한다", Draw_Manager.GetWidth(), 6);
	Draw_Manager.DrawMidText("3.저주받은신전으로 향한다", Draw_Manager.GetWidth(), 8);
	Draw_Manager.DrawMidText("4.용의둥지로 향한다", Draw_Manager.GetWidth(), 10);
	Draw_Manager.DrawMidText("5.무기상점", Draw_Manager.GetWidth(), 12);
	Draw_Manager.DrawMidText("6.캐릭터정보", Draw_Manager.GetWidth(), 14);
	Draw_Manager.DrawMidText("7.게임저장", Draw_Manager.GetWidth(), 16);
	Draw_Manager.DrawMidText("8.게임불러오기", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawMidText("9.게임종료", Draw_Manager.GetWidth(), 20);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 22);
}

void GameManager::ShowSaveAndLoadComplete()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("게임 저장/로드 완료", Draw_Manager.GetWidth(), 15);
	//Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
	cout << endl;
	Draw_Manager.DrawPauseByGameScreen(18);
}

void GameManager::ShowInDungeonKeyRule()
{
	Draw_Manager.DrawMidText("Enter Key를 눌러 메뉴창으로이동", Draw_Manager.GetWidth(), Draw_Manager.GetHeight()+1);
	Draw_Manager.DrawMidText("키보드방향키 : 캐릭터이동", Draw_Manager.GetWidth(), Draw_Manager.GetHeight() + 2);
	Draw_Manager.DrawMidText("ESC : 게임종료(맨처음창으로)", Draw_Manager.GetWidth(), Draw_Manager.GetHeight() + 3);
}

void GameManager::DontMoveByCoolTime()
{
	Draw_Manager.DrawMidText("반동으로 인해 움직일수 없다", Draw_Manager.GetWidth(), 11);
	cout << endl;
	Draw_Manager.DrawPauseByGameScreen(12);
	return;
}

GameManager::~GameManager()
{

}