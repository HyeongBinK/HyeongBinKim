#include "Weapon.h"

Weapon::Weapon()
{
}

void Weapon::InputWeaponData(string WeaponType, string Name, string Introduce, int Grade, int WeaponNumberint, int EquipLevel,
	int Atk, int Sheild, int Gold, bool GetFlag, WeaponSkill UniqueSkill)
{
	m_strWeaponType = WeaponType;
	m_strWeaponName = Name;
	m_strIntroduce = Introduce;
	m_iWeaponGrade = Grade;
	m_iWeaponNumber = WeaponNumberint;
	m_iEquipLevel = EquipLevel;
	m_iWeaponAtk = Atk;
	m_iWeaponSheild = Sheild;
//	m_iBonusEffect = BonusEffect; 
	//m_iReinForce = ReinForce;
	m_iWeaponPride = Gold;
	m_bGotFlag = GetFlag;
	m_ClassUniqueSkill = UniqueSkill;
}

void Weapon::SaveWeaponData(ofstream& save)
{
	string str;
	save << m_strWeaponType << " ";
	save << m_strWeaponName << " ";
	save << m_strIntroduce << " ";
	save << m_ClassUniqueSkill.GetWeaponSkillName() << " ";
	save << m_iWeaponGrade << " ";
	save << m_iWeaponNumber << " ";
	save << m_iEquipLevel << " ";
	save << m_iWeaponAtk << " ";
	save << m_iWeaponSheild << " ";
	//save << m_iBonusEffect << " ";
	//save << m_iReinForce << " ";
	save << m_iWeaponPride << " ";
	save << m_bGotFlag << " ";
	save << m_ClassUniqueSkill.GetIsWeaponSkill() << " ";
	save << m_ClassUniqueSkill.GetWeaponIntrinsicEffect() << " ";
}

//void Weapon::ReinForce()
//{
//	int RandomNum;
//
//	if (m_iReinForce < 5)
//		m_iReinForce++;
//	else if (m_iReinForce < 10)
//	{
//		RandomNum = (rand() % 2);
//		if (RandomNum == 1)
//			m_iReinForce++;
//	}
//	else if (m_iReinForce < 15)
//	{
//		RandomNum = (rand() % 3);
//		if (RandomNum == 1)
//			m_iReinForce++;
//		else
//			m_iReinForce--;
//
//	}
//	else
//	{
//		RandomNum = (rand() % 3);
//		if (RandomNum == 1)
//			m_iReinForce++;
//		else
//			m_iReinForce = 0;
//	}
//}

//void Weapon::PrintWeaponType()
//{
//	cout << "¹«±â ";
//}

void Weapon::WeaponGet()
{
	m_bGotFlag = true;

}


Weapon::~Weapon()
{

}