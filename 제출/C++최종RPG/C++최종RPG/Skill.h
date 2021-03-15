#pragma once
#include"BaseHeader.h"

class Skill
{
private:
protected:
	string m_strSkillName; //스킬이름
	int m_iSkillNumber; //스킬고유식별번호
	int m_iSkillLevel; //스킬레밸
	int m_iSkillDammagePerCent; //액티브스킬의 데미지 증가비율
	int m_iSkillCoolTime; //스킬패널티턴
	int m_iSkillSpecialEffect; //마비, 화상등 상태이상을 거는 스킬일경우
	int m_iSkillMPCost; //소모 MP양
	bool m_bCanBeAcquired; //습득가능여부
public:
	Skill();
	void AcquiredChange(); //전직시 습득가능여부변경
	void SkillLevelUp(); //스킬레밸업
	void SkillDammageUp(int DammagePerCent); //스킬데미지위력증가
	void InputSkillData(string Name, int SkillNumber, int SkillLevel, int SkillDammagePerCent, int SkillCoolTime,
		int SkillSpecialEffect, int SkillMPCost, bool CanBeAcquired); //스킬정보넣기
	void SaveSkillData(ofstream& save); //스킬정보저장

	inline bool GetCanBeAcquired()
	{
		return m_bCanBeAcquired;
	}
	inline int GetSkillLevel()
	{
		return m_iSkillLevel;
	}
	inline string GetSkillName()
	{
		return m_strSkillName;
	}
	inline int GetSkillMPCost()
	{
		return m_iSkillMPCost;
	}
	inline int GetSkillCoolTime()
	{
		return m_iSkillCoolTime;
	}
	inline int GetSkillNumber()
	{
		return m_iSkillNumber;
	}
	inline int GetSkillSpecialEffect()
	{
		return m_iSkillSpecialEffect;
	}
	inline int GetSkillDammagePerCent()
	{
		return m_iSkillDammagePerCent;
	}
	~Skill();
};

