#include "Skill.h"

Skill::Skill()
{
}

void Skill::AcquiredChange()
{
	m_bCanBeAcquired = true;
}

void Skill::SkillLevelUp()
{
	m_iSkillLevel++;
}

void Skill::SkillDammageUp(int DammagePerCent)
{
	m_iSkillDammagePerCent += DammagePerCent;
}

void Skill::InputSkillData(string Name, int SkillNumber, int SkillLevel, int SkillDammagePerCent, int SkillCoolTime,
	int SkillSpecialEffect, int SkillMPCost, bool CanBeAcquired)
{
	 m_strSkillName = Name;
	 m_iSkillNumber = SkillNumber;
	 m_iSkillLevel = SkillLevel;
	 m_iSkillDammagePerCent = SkillDammagePerCent;
	 m_iSkillCoolTime = SkillCoolTime;
     m_iSkillSpecialEffect = SkillSpecialEffect;
     m_iSkillMPCost = SkillMPCost;
     m_bCanBeAcquired = CanBeAcquired;
}

void Skill::SaveSkillData(ofstream& save)
{
	string str;
	save << m_strSkillName << " ";
	save << m_iSkillNumber << " ";
	save << m_iSkillLevel << " ";
	save << m_iSkillDammagePerCent << " ";
	save << m_iSkillCoolTime << " ";
	save << m_iSkillSpecialEffect << " ";
	save << m_iSkillMPCost << " ";
	save << m_bCanBeAcquired << " ";
}

Skill::~Skill()
{
}
