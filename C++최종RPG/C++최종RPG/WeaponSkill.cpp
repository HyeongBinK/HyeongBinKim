#include "WeaponSkill.h"
WeaponSkill::WeaponSkill()
{

}

void WeaponSkill::SetDataByOutSide(bool IsWeaponSkill, string SkillName, int IntrinsicEffect)
{
	m_iIsWeaponSkill = IsWeaponSkill;
	m_iWeapon_SkillName = SkillName;
	m_iWeapon_AbnormalStateSkill_IntrinsicEffect = IntrinsicEffect;
}

WeaponSkill::~WeaponSkill()
{

}