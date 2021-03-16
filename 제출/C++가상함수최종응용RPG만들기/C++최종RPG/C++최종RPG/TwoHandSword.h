#pragma once
#include "BaseHeader.h"
#include "Weapon.h"

class TwoHandSword : public Weapon
{
private:
protected:
public:
	string WeaponNamePlusWeaponType();
	//void PrintWeaponType();
 	TwoHandSword();
	~TwoHandSword();
};

