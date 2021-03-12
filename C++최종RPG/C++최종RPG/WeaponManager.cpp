#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
}

void WeaponManager::SaveWeaponsData(string SaveFileName)
{
	ofstream save;
	string FileName = SaveFileName+".txt";

	save.open(FileName);
	if (save.is_open())
	{
		for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
		{
			(*iter)->SaveWeaponData(save);
			if (iter == WeaPons.end()-1)
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

void WeaponManager::LoadWeaponsData(string LoadFileName)
{
	Weapon* tmp;
	WeaponSkill UniqueSkill;
	string Name, Introduce, SkillName, WeaponType;
	int Grade, WeaponNumberint, EquipLevel, Atk, Sheild, Gold, IntrinsicEffect;
	bool GetFlag, IsWeaponSkillFlag;
	string str2;
	string FileName;
	ifstream load;
	
	FileName = LoadFileName + ".txt";
	load.open(FileName);
	while (!load.eof())
	{
		

		load >> WeaponType >> Name >> Introduce >> SkillName >> Grade >> WeaponNumberint >> EquipLevel >> Atk >> Sheild >> Gold >> GetFlag >> IsWeaponSkillFlag >> IntrinsicEffect;
		load >> str2;
		if (str2 == "NEXT" || str2 == "END")
		{
			UniqueSkill.SetDataByOutSide(IsWeaponSkillFlag, SkillName, IntrinsicEffect);
			if (WeaponType == "SWORD")
				tmp = new Sword;
			else if (WeaponType == "TWOHANDSWORD")
				tmp = new TwoHandSword;

			tmp->InputWeaponData(WeaponType, Name, Introduce, Grade, WeaponNumberint, EquipLevel, Atk, Sheild, Gold, GetFlag, UniqueSkill);
			WeaPons.push_back(tmp);
			if (str2 == "END")
				break;
		}
	}
	//load.close();
}

void WeaponManager::WeaponGet(int WeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (WeaponNumber == (*iter)->GetWeaponNumber())
		{
			(*iter)->WeaponGet();
		}
	}
}

bool WeaponManager::FindWeaponGotFlag(int WeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (WeaponNumber == (*iter)->GetWeaponNumber())
		{
			if ((*iter)->GetGotFlag() == true)
				return true;
			else
				return false;
		}
	}
	return false;
}

int WeaponManager::FindWeaponEquipLimitLevel(int WeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (WeaponNumber == (*iter)->GetWeaponNumber())
		{
			return (*iter)->GetEquipLimintLevel();
		}
	}
}

void WeaponManager::ClearWeaponData()
{
	WeaPons.clear();
}

void WeaponManager::ShowGetorNot(int WeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (WeaponNumber == (*iter)->GetWeaponNumber())
			if ((*iter)->GetGotFlag() == true)
			{
				cout << " ㅇ";
				return;
			}
	}
	cout << " x";
}

string WeaponManager::WeaponNumberToWeaponName(int EquipWeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (EquipWeaponNumber == (*iter)->GetWeaponNumber())
			return (*iter)->GetWeaponName();
	}
}

int WeaponManager::WeaponNumberToWeaponPride(int EquipWeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (EquipWeaponNumber == (*iter)->GetWeaponNumber())
			return (*iter)->GetWeaponPride();
	}
}

//void WeaponManager::SetEquipWeaponData(int EquipWeaponNumber)
//{
//	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
//	{
//		if (EquipWeaponNumber == iter->GetWeaponNumber())
//			EquipWeaponData = *iter;
//	}
//}

void WeaponManager::SetWeaponAtkShieldSkillByNumber(int WeaponNumber)
{
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
	{
		if (WeaponNumber == (*iter)->GetWeaponNumber())
		{
			m_iMemoWeaponAtk = (*iter)->GetWeaponatk();
			m_iMemoWeaponShield = (*iter)->GetWeaponShield();
			MemoWeaponSkill = (*iter)->GetWeaponSKillData();
			return;
		}
	}
}

int WeaponManager::WeaponTrader(int PlayerGold)
{
	int Select;
	int line = 6;
	int IterCount = 0;
	int iterPlusCount = 1;
	//int WeaponNumberCount; //페이지관리를위해준비
	
	system("cls");
	Draw_Manager.DrawBorder();
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter+= iterPlusCount)
	{
		if ((*iter)->GetWeaponNumber() != 999)
		{
			iterPlusCount =1;
			string str = to_string((*iter)->GetWeaponNumber()) + "." + (*iter)->WeaponNamePlusWeaponType() + WeaponNumberToWeaponName((*iter)->GetWeaponNumber());
			str += " : ";
			Draw_Manager.DrawMidText_PlusTailInt(WeaponNumberToWeaponPride((*iter)->GetWeaponNumber()), str, Draw_Manager.GetWidth(), line);
			
			/*string str = to_string(iter->GetWeaponNumber()) + "." + WeaponNumberToWeaponName(iter->GetWeaponNumber());
			str += " : ";
			Draw_Manager.DrawMidText_PlusTailInt(WeaponNumberToWeaponPride(iter->GetWeaponNumber()), str, Draw_Manager.GetWidth(), line);
			iter->PrintWeaponType();*/

			line += 2;
			IterCount++;

			if (iter== WeaPons.end()-2 || line == 18)
			{
				Draw_Manager.DrawMidText("7.이전페이지", Draw_Manager.GetWidth(), 18);
				Draw_Manager.DrawMidText("8.다음페이지", Draw_Manager.GetWidth(), 20);
				Draw_Manager.DrawMidText("9.되돌아가기", Draw_Manager.GetWidth(), 22);
				Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 24);
				cin >> Select;
				if (Select < 7 || Select > 9)
				{
					for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
					{
						if (Select == (*iter)->GetWeaponNumber())
						{
							if (BuyWeapon(PlayerGold, (*iter)->GetWeaponPride()) == true)
							{
								(*iter)->WeaponGet();
								return (*iter)->GetWeaponPride();
							}
							else
							return 0;
							
						}
					}
				}
				else if (Select == WEAPONTRADER_KEY_eBEFOREPAGE)
				{
					line = 6;
					if (IterCount >= 7)
					{
						IterCount -= 7;
						iter = WeaPons.begin() + IterCount;
						iterPlusCount = 0;
					}
					else
					{
						IterCount = 0;
						iter = WeaPons.begin();
						iterPlusCount = 0;
					}
					system("cls");
					Draw_Manager.DrawBorder();
				}
				else if (Select == WEAPONTRADER_KEY_eNEXTPAGE)
				{
					if (iter == WeaPons.end() - 2)
					{
						iter = WeaPons.begin();
						iterPlusCount = 0;
						IterCount = 0;
						line = 6;
						system("cls");
						Draw_Manager.DrawBorder();
					}
					else
					{
						line = 6;
						system("cls");
						Draw_Manager.DrawBorder();
					}
				}
				else if (Select == WEAPONTRADER_KEY_eRETURN)
					return 0;
			}
		}
	}
	return 0;
}

bool WeaponManager::BuyWeapon(int PlayerGold, int WeaponPride)
{
	if (PlayerGold >= WeaponPride)
		return true;
	else
	{
		GoldError();
		return false;
	}
}

//void WeaponManager::ShowWeaponNameAndPride(Weapon WeaponData, int Line)
//{
//	string str = to_string(WeaponData.GetWeaponNumber()) + "." + WeaponData.WeaponNamePlusWeaponType() +WeaponNumberToWeaponName(WeaponData.GetWeaponNumber());
//	str += " : ";
//	Draw_Manager.DrawMidText_PlusTailInt(WeaponNumberToWeaponPride(WeaponData.GetWeaponNumber()), str, Draw_Manager.GetWidth(), Line);
//}

void WeaponManager::GoldError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("골드가부족해 아이템을 구입할수없습니다.", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
	Draw_Manager.DrawPauseByGameScreen(18);
}

int WeaponManager::WeaponChange(int EquipWeaponNumber, int PlayerLevel)
{
	int Select;
	int line = 6;
	int IterCount = 0;
	int iterPlusCount = 1;
	//int WeaponNumberCount; //페이지관리를위해준비

	system("cls");
	Draw_Manager.DrawBorder();
	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter += iterPlusCount)
	{
		if ((*iter)->GetWeaponNumber() != WEAPONNAME_eETERNALSWORD)
		{
			iterPlusCount = 1;
			Draw_Manager.DrawMidText_PlusHeadInt((*iter)->GetWeaponNumber(), " : "+ (*iter)->WeaponNamePlusWeaponType() + WeaponNumberToWeaponName((*iter)->GetWeaponNumber()), Draw_Manager.GetWidth(), line);
			//Draw_Manager.DrawMidText_PlusHeadInt(iter->GetWeaponNumber(), " : " +  WeaponNumberToWeaponName(iter->GetWeaponNumber()), Draw_Manager.GetWidth(), line);
			ShowGetorNot((*iter)->GetWeaponNumber());
			//iter->PrintWeaponType();

			line += 2;
			IterCount++;

			if (iter == WeaPons.end() - 2 || line == 18)
			{
				Draw_Manager.DrawMidText_TwoString("장착중인 무기 : ", WeaponNumberToWeaponName(EquipWeaponNumber), Draw_Manager.GetWidth(), 4);
				Draw_Manager.DrawMidText("7.이전페이지", Draw_Manager.GetWidth(), 18);
				Draw_Manager.DrawMidText("8.다음페이지", Draw_Manager.GetWidth(), 20);
				Draw_Manager.DrawMidText("9.되돌아가기", Draw_Manager.GetWidth(), 22);
				Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 24);
				cin >> Select;
				if (Select < 7 || Select > 9)
				{
					for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
					{
						if (Select == (*iter)->GetWeaponNumber())
							if ((*iter)->GetGotFlag() == true)
							{
								if (PlayerLevel >= (*iter)->GetEquipLimintLevel())
									return (*iter)->GetWeaponNumber();
								else
								{
									ShowWeaponEquipError();
									return 0;
								}
							}
							else
							{
								ShowWeaponEquipError();
								return 0;
							}
					}
				}
				else if (Select == WEAPONTRADER_KEY_eBEFOREPAGE)
				{
					line = 6;
					if (IterCount >= 7)
					{
						IterCount -= 7;
						iter = WeaPons.begin() + IterCount;
						iterPlusCount = 0;
					}
					else
					{
						IterCount = 0;
						iter = WeaPons.begin();
						iterPlusCount = 0;
					}
					system("cls");
					Draw_Manager.DrawBorder();
				}
				else if (Select == WEAPONTRADER_KEY_eNEXTPAGE)
				{
					if (iter == WeaPons.end() - 2)
					{
						iter = WeaPons.begin();
						iterPlusCount = 0;
						IterCount = 0;
						line = 6;
						system("cls");
						Draw_Manager.DrawBorder();
					}
					else
					{
						line = 6;
						system("cls");
						Draw_Manager.DrawBorder();
					}
				}
				else if (Select == WEAPONTRADER_KEY_eRETURN)
					return 0;
			}
		}
	}
	return 0;
}

void WeaponManager::ShowWeaponEquipError()
{
	system("cls");
	Draw_Manager.DrawBorder();
	Draw_Manager.DrawMidText("아직 습득하지못한 무기이거나 착용제한래밸이 부족합니다.", Draw_Manager.GetWidth(), 15);
	Draw_Manager.DrawPauseByGameScreen(18);
}



WeaponManager::~WeaponManager()
{
}


//void WeaponManager::SaveWeaponsData(string SaveFileName)
//{
//	ofstream save;
//
//	char buf[30];
//	char cstr[20];
//	char str[20] = ".txt";
//
//	strcpy(cstr, SaveFileName.c_str());
//	sprintf(buf, "%s%s", cstr, str);
//	save.open(buf);
//	if (save.is_open())
//	{
//		for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//		{
//			iter->SaveWeaponData(save);
//			if (iter == WeaPons->end())
//				save << "END";
//			else
//				save << "NEXT" << endl;
//		}
//
//		save.close();
//	}
//
//}
//
//void WeaponManager::LoadWeaponsData(string LoadFileName)
//{
//	Weapon* tmp;
//	WeaponSkill UniqueSkill;
//	string Name, Introduce, SkillName, WeaponType;
//	int Grade, WeaponNumberint, EquipLevel, Atk, Sheild, Gold, IntrinsicEffect;
//	bool GetFlag, IsWeaponSkillFlag;
//	string str2;
//	ifstream load;
//	char buf[30];
//	char str[20] = ".txt";
//	char cstr[20];
//	strcpy(cstr, LoadFileName.c_str());
//	sprintf(buf, "%s%s", cstr, str);
//
//	load.open(buf);
//	while (!load.eof())
//	{
//
//
//		load >> WeaponType >> Name >> Introduce >> SkillName >> Grade >> WeaponNumberint >> EquipLevel >> Atk >> Sheild >> Gold >> GetFlag >> IsWeaponSkillFlag >> IntrinsicEffect;
//		load >> str2;
//		if (str2 == "NEXT" || str2 == "END")
//		{
//			UniqueSkill.SetDataByOutSide(IsWeaponSkillFlag, SkillName, IntrinsicEffect);
//			if (WeaponType == "SWORD")
//				tmp = new Sword;
//			else if (WeaponType == "TWOHANDSWORD")
//				tmp = new TwoHandSword;
//
//			tmp->InputWeaponData(WeaponType, Name, Introduce, Grade, WeaponNumberint, EquipLevel, Atk, Sheild, Gold, GetFlag, UniqueSkill);
//			WeaPons->push_back(*tmp);
//			if (str2 == "END")
//				break;
//		}
//	}
//}
//
//void WeaponManager::WeaponGet(int WeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (WeaponNumber == iter->GetWeaponNumber())
//		{
//			iter->WeaponGet();
//		}
//	}
//}
//
//bool WeaponManager::FindWeaponGotFlag(int WeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (WeaponNumber == iter->GetWeaponNumber())
//		{
//			if (iter->GetGotFlag() == true)
//				return true;
//			else
//				return false;
//		}
//	}
//	return false;
//}
//
//int WeaponManager::FindWeaponEquipLimitLevel(int WeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (WeaponNumber == iter->GetWeaponNumber())
//		{
//			return iter->GetEquipLimintLevel();
//		}
//	}
//}
//
//void WeaponManager::ClearWeaponData()
//{
//	WeaPons->clear();
//}
//
//void WeaponManager::ShowGetorNot(int WeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (WeaponNumber == iter->GetWeaponNumber())
//			if (iter->GetGotFlag() == true)
//			{
//				cout << " ㅇ";
//				return;
//			}
//	}
//	cout << " x";
//}
//
//string WeaponManager::WeaponNumberToWeaponName(int EquipWeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (EquipWeaponNumber == iter->GetWeaponNumber())
//			return iter->GetWeaponName();
//	}
//}
//
//int WeaponManager::WeaponNumberToWeaponPride(int EquipWeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (EquipWeaponNumber == iter->GetWeaponNumber())
//			return iter->GetWeaponPride();
//	}
//}
//
////void WeaponManager::SetEquipWeaponData(int EquipWeaponNumber)
////{
////	for (auto iter = WeaPons.begin(); iter != WeaPons.end(); iter++)
////	{
////		if (EquipWeaponNumber == iter->GetWeaponNumber())
////			EquipWeaponData = *iter;
////	}
////}
//
//void WeaponManager::SetWeaponAtkShieldSkillByNumber(int WeaponNumber)
//{
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//	{
//		if (WeaponNumber == iter->GetWeaponNumber())
//		{
//			m_iMemoWeaponAtk = iter->GetWeaponatk();
//			m_iMemoWeaponShield = iter->GetWeaponShield();
//			MemoWeaponSkill = iter->GetWeaponSKillData();
//		}
//	}
//}
//
//int WeaponManager::WeaponTrader(int PlayerGold)
//{
//	int Select;
//	int line = 6;
//	int IterCount = 0;
//	int iterPlusCount = 1;
//	//int WeaponNumberCount; //페이지관리를위해준비
//
//	system("cls");
//	Draw_Manager.DrawBorder();
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter += iterPlusCount)
//	{
//		if (iter->GetWeaponNumber() != 999)
//		{
//			iterPlusCount = 1;
//			string str = to_string(iter->GetWeaponNumber()) + "." + iter->WeaponNamePlusWeaponType() + WeaponNumberToWeaponName(iter->GetWeaponNumber());
//			str += " : ";
//			Draw_Manager.DrawMidText_PlusTailInt(WeaponNumberToWeaponPride(iter->GetWeaponNumber()), str, Draw_Manager.GetWidth(), line);
//
//			/*string str = to_string(iter->GetWeaponNumber()) + "." +  WeaponNumberToWeaponName(iter->GetWeaponNumber());
//			str += " : ";
//			Draw_Manager.DrawMidText_PlusTailInt(WeaponNumberToWeaponPride(iter->GetWeaponNumber()), str, Draw_Manager.GetWidth(), line);
//			iter->PrintWeaponType();*/
//
//			line += 2;
//			IterCount++;
//
//			if (iter == WeaPons->end() - 2 || line == 18)
//			{
//				Draw_Manager.DrawMidText("7.이전페이지", Draw_Manager.GetWidth(), 18);
//				Draw_Manager.DrawMidText("8.다음페이지", Draw_Manager.GetWidth(), 20);
//				Draw_Manager.DrawMidText("9.되돌아가기", Draw_Manager.GetWidth(), 22);
//				Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 24);
//				cin >> Select;
//				if (Select < 7 || Select > 9)
//				{
//					for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//					{
//						if (Select == iter->GetWeaponNumber())
//						{
//							if (BuyWeapon(PlayerGold, iter->GetWeaponPride()) == true)
//							{
//								iter->WeaponGet();
//								return iter->GetWeaponPride();
//							}
//							else
//								return 0;
//
//						}
//					}
//				}
//				else if (Select == WEAPONTRADER_KEY_eBEFOREPAGE)
//				{
//					line = 6;
//					if (IterCount >= 7)
//					{
//						IterCount -= 7;
//						iter = WeaPons->begin() + IterCount;
//						iterPlusCount = 0;
//					}
//					else
//					{
//						IterCount = 0;
//						iter = WeaPons->begin();
//						iterPlusCount = 0;
//					}
//					system("cls");
//					Draw_Manager.DrawBorder();
//				}
//				else if (Select == WEAPONTRADER_KEY_eNEXTPAGE)
//				{
//					if (iter == WeaPons->end() - 2)
//					{
//						iter = WeaPons->begin();
//						iterPlusCount = 0;
//						IterCount = 0;
//						line = 6;
//						system("cls");
//						Draw_Manager.DrawBorder();
//					}
//					else
//					{
//						line = 6;
//						system("cls");
//						Draw_Manager.DrawBorder();
//					}
//				}
//				else if (Select == WEAPONTRADER_KEY_eRETURN)
//					return 0;
//			}
//		}
//	}
//	return 0;
//}
//
//bool WeaponManager::BuyWeapon(int PlayerGold, int WeaponPride)
//{
//	if (PlayerGold >= WeaponPride)
//		return true;
//	else
//	{
//		GoldError();
//		return false;
//	}
//}
//
////void WeaponManager::ShowWeaponNameAndPride(Weapon WeaponData, int Line)
////{
////	string str = to_string(WeaponData.GetWeaponNumber()) + "." + WeaponData.WeaponNamePlusWeaponType() +WeaponNumberToWeaponName(WeaponData.GetWeaponNumber());
////	str += " : ";
////	Draw_Manager.DrawMidText_PlusTailInt(WeaponNumberToWeaponPride(WeaponData.GetWeaponNumber()), str, Draw_Manager.GetWidth(), Line);
////}
//
//void WeaponManager::GoldError()
//{
//	system("cls");
//	Draw_Manager.DrawBorder();
//	Draw_Manager.DrawMidText("골드가부족해 아이템을 구입할수없습니다.", Draw_Manager.GetWidth(), 15);
//	//Draw_Manager.DrawMidText("아무키나누르면 원래창으로 이동", Draw_Manager.GetWidth(), 18);
//	Draw_Manager.DrawPauseByGameScreen(18);
//}
//
//int WeaponManager::WeaponChange(int EquipWeaponNumber, int PlayerLevel)
//{
//	int Select;
//	int line = 6;
//	int IterCount = 0;
//	int iterPlusCount = 1;
//	//int WeaponNumberCount; //페이지관리를위해준비
//
//	system("cls");
//	Draw_Manager.DrawBorder();
//	for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter += iterPlusCount)
//	{
//		if (iter->GetWeaponNumber() != WEAPONNAME_eETERNALSWORD)
//		{
//			iterPlusCount = 1;
//			Draw_Manager.DrawMidText_PlusHeadInt(iter->GetWeaponNumber(), " : " + iter->WeaponNamePlusWeaponType() + WeaponNumberToWeaponName(iter->GetWeaponNumber()), Draw_Manager.GetWidth(), line);
//			ShowGetorNot(iter->GetWeaponNumber());
//
//		/*	Draw_Manager.DrawMidText_PlusHeadInt(iter->GetWeaponNumber(), " : " + WeaponNumberToWeaponName(iter->GetWeaponNumber()), Draw_Manager.GetWidth(), line);
//			ShowGetorNot(iter->GetWeaponNumber());
//			iter->PrintWeaponType();*/
//
//			line += 2;
//			IterCount++;
//
//			if (iter == WeaPons->end() - 2 || line == 18)
//			{
//				Draw_Manager.DrawMidText_TwoString("장착중인 무기 : ", WeaponNumberToWeaponName(EquipWeaponNumber), Draw_Manager.GetWidth(), 4);
//				Draw_Manager.DrawMidText("7.이전페이지", Draw_Manager.GetWidth(), 18);
//				Draw_Manager.DrawMidText("8.다음페이지", Draw_Manager.GetWidth(), 20);
//				Draw_Manager.DrawMidText("9.되돌아가기", Draw_Manager.GetWidth(), 22);
//				Draw_Manager.DrawMidText("선택 : ", Draw_Manager.GetWidth(), 24);
//				cin >> Select;
//				if (Select < 7 || Select > 9)
//				{
//					for (auto iter = WeaPons->begin(); iter != WeaPons->end(); iter++)
//					{
//						if (Select == iter->GetWeaponNumber())
//							if (iter->GetGotFlag() == true)
//							{
//								if (PlayerLevel >= iter->GetEquipLimintLevel())
//									return iter->GetWeaponNumber();
//								else
//								{
//									ShowWeaponEquipError();
//									return 0;
//								}
//							}
//							else
//							{
//								ShowWeaponEquipError();
//								return 0;
//							}
//					}
//				}
//				else if (Select == WEAPONTRADER_KEY_eBEFOREPAGE)
//				{
//					line = 6;
//					if (IterCount >= 7)
//					{
//						IterCount -= 7;
//						iter = WeaPons->begin() + IterCount;
//						iterPlusCount = 0;
//					}
//					else
//					{
//						IterCount = 0;
//						iter = WeaPons->begin();
//						iterPlusCount = 0;
//					}
//					system("cls");
//					Draw_Manager.DrawBorder();
//				}
//				else if (Select == WEAPONTRADER_KEY_eNEXTPAGE)
//				{
//					if (iter == WeaPons->end() - 2)
//					{
//						iter = WeaPons->begin();
//						iterPlusCount = 0;
//						IterCount = 0;
//						line = 6;
//						system("cls");
//						Draw_Manager.DrawBorder();
//					}
//					else
//					{
//						line = 6;
//						system("cls");
//						Draw_Manager.DrawBorder();
//					}
//				}
//				else if (Select == WEAPONTRADER_KEY_eRETURN)
//					return 0;
//			}
//		}
//	}
//	return 0;
//}
//
//void WeaponManager::ShowWeaponEquipError()
//{
//	system("cls");
//	Draw_Manager.DrawBorder();
//	Draw_Manager.DrawMidText("아직 습득하지못한 무기이거나 착용제한래밸이 부족합니다.", Draw_Manager.GetWidth(), 15);
//	Draw_Manager.DrawPauseByGameScreen(18);
//}
//
//WeaponManager::~WeaponManager()
//{
//}
