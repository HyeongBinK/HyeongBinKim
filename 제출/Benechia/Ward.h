#pragma once
#include "BaseHeader.h"

class Ward
{
private:
	int m_iLocationX; //X좌표
	int m_iLocationY; //Y좌표
	string m_strWard;
	int m_iTimer;
	int m_iFallenDelay;
	bool m_bDead;
	bool m_SuccessAttack;

protected:
public:
	void Warddraw(); //화면에 단어그리기
	void Warddrop(); //단어 떨어트리기(Y좌표값 증가)
	void Live(int NewTimer); //단어가 아직 떨어지는 상태 
	void Die(); //단어가 플레이어가 입력을하였거나 바닥에 닿아서 소멸
	void MakeNewWard(string NewWard, int XLocation, int NewFallenDelay); //외부에서 데이터값 몇가지만 입력받고 그외엔 디폴트값(지정한값)으로 
	void UserUseSpeedItem(int NewSpeed); //유저가 아이템을 사용하여 낙하속도 (m_iFallenDelay) 에 영향을 주어 낙하속도변경

	inline string GetWard() const
	{
		return m_strWard;
	}
	inline int GetXLocation() const
	{
		return m_iLocationX;
	}
	inline int GetYLocation() const
	{
		return m_iLocationY;
	}
	inline bool GetDie() const
	{
		return m_bDead;
	}
	inline bool GetAttackSuccees() const
	{
		return m_SuccessAttack;
	}
};

