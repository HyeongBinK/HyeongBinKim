#include "Character.h"

Character :: Character()
{
	
}

void Character::Get_Dammage(int TrueDammage)
{
	m_iHP -= TrueDammage;
	if (m_iHP <= 0)
	m_iLifeStatus = LIFESTATUS_eDEAD;
}

void Character::LifeStatusChange(int LifeStatus)
{
	m_iLifeStatus = LifeStatus;
}

void Character::InputCharacterImage(string str)
{
	m_strCharacterImage = str;
}

void Character::ChangeAttackSpeedByParalysys(int Speed)
{
	m_iAttackSpeed = Speed;
}

Character :: ~Character()
{

}