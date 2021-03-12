#include "SkillManager.h"

SkillManager::SkillManager()
{
}


void SkillManager::SaveSkillData(string SaveFileName)
{
	ofstream save;

	char buf[30];
	char cstr[20];
	string Tail = ".txt";
	string FileName;
	FileName = SaveFileName + Tail;
	save.open(FileName);
	if (save.is_open())
	{
		for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
		{
			iter->SaveSkillData(save);
			if (iter == Skills.end()-1)
			{
				save << "END";
				break;
			}
			else
				save << "NEXT" << endl;
		}
		save.close();
	}
	//save.close();
}

void SkillManager::LoadSkillData(string LoadFileName)
{
	Skill skill;
	string SkillName;
	int SkillNumber, SkillLevel, SkillDammagePerCent, SkillCoolTime, SkillSpecialEffect, SkillMPCost;
	bool CanBeAcquired;
	string str2;
	ifstream load;
	string Tail = ".txt";
	string FileName;
	FileName = LoadFileName + Tail;
	load.open(FileName);
	while (!load.eof())
	{
		load >> SkillName >> SkillNumber >> SkillLevel >> SkillDammagePerCent >> SkillCoolTime >> SkillSpecialEffect >> SkillMPCost >> CanBeAcquired;
		load >> str2;
		if (str2 == "NEXT" || str2 == "END")
		{
			skill.InputSkillData(SkillName, SkillNumber, SkillLevel, SkillDammagePerCent, SkillCoolTime, SkillSpecialEffect, SkillMPCost, CanBeAcquired);
			Skills.push_back(skill);
			if (str2 == "END")
				break;
		}
	}
	//load.close();
}

//void SkillManager::SetSkillData(int SkillNumber)
//{
//	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
//	{
//		if (SkillNumber == iter->GetSkillNumber())
//		{
//			UseSkill.InputSkillData(iter->GetSkillName(), iter->GetSkillNumber(), iter->GetSkillLevel(), iter->GetSkillDammagePerCent(), iter->GetSkillCoolTime(),
//				iter->GetSkillSpecialEffect(), iter->GetSkillMPCost(), iter->GetCanBeAcquired());
//			return;
//		}
//	}
//}

void SkillManager::UseSkillInBattlePhase()
{
	Draw_Manager.DrawMidText("1.파워슬래쉬",Draw_Manager.GetWidth(), 17);
	ShowCanLearn(SKILLNAME_ePOWERSLASH, 18);
	Draw_Manager.DrawMidText("2.Active:콤보어썰트", Draw_Manager.GetWidth(), 20);
	ShowCanLearn(SKILLNAME_eCOMBOASSULT, 21);
	Draw_Manager.DrawMidText("3.Active:콤보익스팅션(사용시 한턴행동불가)", Draw_Manager.GetWidth(), 23);
	ShowCanLearn(SKILLNAME_eCOMBOEXTINGSION, 24);
	Draw_Manager.DrawMidText("4.돌아가기", Draw_Manager.GetWidth(), 26);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 27);
}

void SkillManager::SkillLevelUp(int SkillNumber)
{
	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
	{
		if (SkillNumber == iter->GetSkillNumber())
		{
			if (iter->GetCanBeAcquired() == false)
			{
				ShowCanNotLearnSkill();
				return;
			}
			else
			{
				iter->SkillLevelUp();
				switch (SkillNumber)
				{
				case SKILLNAME_ePOWERSLASH:
					iter->SkillDammageUp(1);
				case SKILLNAME_eCOMBOASSULT:
					iter->SkillDammageUp(3);
				case SKILLNAME_eCOMBOEXTINGSION:
					iter->SkillDammageUp(10);
				}
			}
		}
	}
}

void SkillManager::UpGradeSkill(int PlayerClassNumber, int* SkillPoint)
{
	int Select;
	while (1)
	{
		ShowAndUpgradeSkill(PlayerClassNumber, *SkillPoint);
		cin >> Select;
		switch (Select)
		{
		case SKILLNAME_ePOWERSLASH:
			if ((*SkillPoint) > 0)
			{
				SkillLevelUp(SKILLNAME_ePOWERSLASH);
				(*SkillPoint)--;
			}
			else
				SkillPointError();
			break;
		case SKILLNAME_eCOMBOASSULT:
			if ((*SkillPoint) > 0)
			{
				SkillLevelUp(SKILLNAME_eCOMBOASSULT);
				(*SkillPoint)--;
			}
			else
				SkillPointError();
			break;
		case SKILLNAME_eCOMBOEXTINGSION:
			if ((*SkillPoint) > 0)
			{
				SkillLevelUp(SKILLNAME_eCOMBOEXTINGSION);
				(*SkillPoint)--;
			}
			else
				SkillPointError();
			break;
		case SKILLNAME_eRETURN:
			return;
		default: break;
		}
	}
}

Skill SkillManager::GetSkillAllDataBySkillNumber(int SKillNumber)
{
	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
	{
		if (SKillNumber == iter->GetSkillNumber())
		{
			return *iter;
		}
	}
}

void SkillManager::SkillPointError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("스킬포인트가 부족해 스킬을 습득할수없습니다.", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawMidText("아직 습득할수없는 스킬입니다.", Draw_Manager.GetWidth(), 16);
	//Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawPauseByGameScreen(18);
	//system("pause");
}

void SkillManager::ChangeSkillCanBeAcquiredBySkillNumber(int SkillNumber)
{
	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
	{
		if (SkillNumber == iter->GetSkillNumber())
		{
			iter->AcquiredChange();
		}
	}
}

void SkillManager::ShowAndUpgradeSkill(int PlayerClass, int SkillPoint)
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText_PlusHeadInt(SkillPoint, "의 스킬포인트 보유중", Draw_Manager.GetWidth(), 4);

	Draw_Manager.DrawMidText("전사전직이후부터 습득가능", Draw_Manager.GetWidth(), 7);
	Draw_Manager.DrawMidText("1.Active:파워슬래쉬(한명의적에 강한 공격)", Draw_Manager.GetWidth(), 8);
	ShowCanLearn(SKILLNAME_ePOWERSLASH, 9);

	Draw_Manager.DrawMidText("히어로전직이후부터 습득가능", Draw_Manager.GetWidth(), 12);
	Draw_Manager.DrawMidText("2.Active:콤보어썰트(한명의적에 매우 강한 공격)", Draw_Manager.GetWidth(), 13);
	ShowCanLearn(SKILLNAME_eCOMBOASSULT, 14);
	Draw_Manager.DrawMidText("3.Active:콤보익스팅션(사용시 한턴행동불가)", Draw_Manager.GetWidth(), 16);
	ShowCanLearn(SKILLNAME_eCOMBOEXTINGSION, 17);
	Draw_Manager.DrawMidText("4.돌아가기", Draw_Manager.GetWidth(), 19);
	Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 21);
}

void SkillManager::ShowCanLearn(int SkillNumber, int Line)
{
	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
	{
		if (SkillNumber == iter->GetSkillNumber())
			if (iter->GetCanBeAcquired() == true)
			{
				Draw_Manager.DrawMidText_PlusTailInt(iter->GetSkillLevel(), "현재레밸 : ", Draw_Manager.GetWidth(), Line); 
					return;
			}
	}
	Draw_Manager.DrawMidText("현재 사용/습득불가능", Draw_Manager.GetWidth(), Line);
}

void SkillManager::SkillUseError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("아직습득하지않은 스킬이여서 사용할수 없습니다", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawPauseByGameScreen(18);
}

void SkillManager::ShowCanNotLearnSkill()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("아직 배울수없는 스킬입니다(전직필요)", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawPauseByGameScreen(18);
}

//int SkillManager::GetSkillDammageBySkillNumber(int SkillNumber)
//{
//	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
//	{
//		if (SkillNumber == iter->GetSkillNumber())
//			return iter->GetSkillDammagePerCent();
//	}
//}
//
//int SkillManager::GetSkillMpCostbySkillNumber(int SKillNumber)
//{
//	for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
//	{
//		if (SKillNumber == iter->GetSkillNumber())
//			return iter->GetSkillMPCost();
//	}
//}

void SkillManager::ClearSkillData()
{
	Skills.clear();
}

SkillManager::~SkillManager()
{
}
