#pragma once
#include"BaseHeader.h"
#include"Character.h"

class Monster: public virtual Character
{

protected:
	int m_iMonsterNumber; //몬스터번호
	int m_iGiveExp; //잡았을떄주는 경험치	
	int m_iGiveMaxMoney; //잡았을떄주는 최대 골드
	Point Location; //몬스터좌표 메모장에서 안불러오고 몬스터매니저에서 몬스터생성시 입력
public:
	Monster();
	void InputMonsterData(string CharacterImage, int ClassNumber, int MonsterNumber, string Name, int Level, int MaxHP
		, int Atk, int Shield, int AttackSpeed, int LifeStatus, int GiveExp, int GiveMaxMoney);
	void ChangeMonsterLocation(int NewX, int NewY)
	{
		Location.m_iX_Location = NewX;
		Location.m_iY_Location = NewY;
	}
	inline Point GetMonsterLocation()
	{
		return Location;
	}
	inline int GetMonsterNumber()
	{
		return m_iMonsterNumber;
	}
	inline int GetMonsterGiveMoney()
	{
		return m_iGiveMaxMoney;
	}
	inline int GetMonsterGiveExp()
	{
		return m_iGiveExp;
	}
	~Monster();
};

