#pragma once
#include"BaseHeader.h"

struct Point
{
	int m_iX_Location;
	int m_iY_Location;
};

class Character
{
protected:
	string m_strCharacterImage; //캐릭터의이미지
	int m_iClassNumber; //직업, 몬스터는 몬스터직업군
	string m_strName; //캐릭터이름 or 몬스터이름
	int m_iLevel; //현재레밸
	int m_iMaxHP; //최대체력
	int m_iHP; //현재체력
	int m_iAtk; //공격력
	int m_iShield; //물리방어
	int m_iAttackSpeed; //공격속도
	int m_iLifeStatus; //상태이상 이나 죽었거나 살았거나 여부
public:
	Character();
	void Get_Dammage(int TrueDammage);
	void InputCharacterImage(string str);
	void LifeStatusChange(int LifeStatus);
	void ChangeAttackSpeedByParalysys(int Speed);//마비상태로인한 속도변경

	inline string GetCharacterImage()
	{
		return m_strCharacterImage;
	}
	inline string GetName()
	{
		return m_strName;
	}
	inline int GetClassNumber()
	{
		return m_iClassNumber;
	}
	inline int GetLevel()
	{
		return m_iLevel;
	}
	inline int GetMaxHP()
	{
		return m_iMaxHP;
	}
	inline int GetHP()
	{
		return m_iHP;
	}
	inline int GetAtk()
	{
		return m_iAtk;
	}
	inline int GetShield()
	{
		return m_iShield;
	}
	inline int GetAttackSpeed()
	{
		return m_iAttackSpeed;
	}
	inline int GetLifeStatus()
	{
		return m_iLifeStatus;
	}
	~Character();
};

