#pragma once
#include"BaseHeader.h"

class WeaponSkill 
{
private :
	bool m_iIsWeaponSkill; //무기의 스킬이있을시 트루 없으면 펄스
	string m_iWeapon_SkillName; //무기스킬이름(없으면 없음 이라 표시)
	int m_iWeapon_AbnormalStateSkill_IntrinsicEffect; //무기에 상태이상부여계열의 스킬이 있을시 해당숫자 없으면 0

protected :
public :
	WeaponSkill();
	void SetDataByOutSide(bool IsWeaponSkill, string SkillName, int IntrinsicEffect);

	inline bool GetIsWeaponSkill()
	{
		return m_iIsWeaponSkill;
	}
	inline string GetWeaponSkillName()
	{
		return m_iWeapon_SkillName;
	}
	inline int GetWeaponIntrinsicEffect()
	{
		return m_iWeapon_AbnormalStateSkill_IntrinsicEffect;
	}

   ~WeaponSkill();

};

