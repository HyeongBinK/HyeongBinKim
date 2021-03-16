#include "Monster.h"

Monster::Monster()
{
	Location.m_iX_Location = 0;
	Location.m_iY_Location = 0;
}

void Monster::InputMonsterData(string CharacterImage, int ClassNumber, int MonsterNumber , string Name, int Level, int MaxHP
	, int Atk, int Shield, int AttackSpeed, int LifeStatus, int GiveExp, int GiveMaxMoney)
{
	m_strCharacterImage = CharacterImage;
	m_iClassNumber = ClassNumber;
	m_iMonsterNumber = MonsterNumber;
	m_strName = Name;
	m_iLevel = Level;
	m_iMaxHP = MaxHP;
	m_iAtk = Atk;
	m_iShield = Shield;
	m_iAttackSpeed = AttackSpeed;
	m_iLifeStatus = LifeStatus; 
	m_iGiveExp = GiveExp;
	m_iGiveMaxMoney = GiveMaxMoney;
	m_iHP = m_iMaxHP;
}

Monster::~Monster()
{

}