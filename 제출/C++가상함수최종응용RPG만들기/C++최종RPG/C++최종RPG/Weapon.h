#pragma once
#include"BaseHeader.h"
#include "WeaponSkill.h"

enum WEAPONGRADE
{
	WEAPONGRADE_eCOMMON = 0,
	WEAPONGRADE_eUNCOMMON,
	WEAPONGRADE_eRARE,
	WEAPONGRADE_eUNIQUE,
	WEAPONGRADE_eEPIC,
	WEAPONGRADE_eETERNAL
};

class Weapon
{
private:
protected:
	string m_strWeaponType; //무기타입
	string m_strWeaponName; //아이템이름
	string m_strIntroduce; //아이템설명
	int m_iWeaponGrade; //장비등급에 따라 무기 이름의 색을 변경하려 했으나 미구현
	int m_iWeaponNumber; //무기번호
	int m_iEquipLevel; //착용제한래밸
	int m_iWeaponAtk; //무기공격력
	int m_iWeaponSheild; // 무기방어력
	//int m_iBonusEffect; //특수효과
	//int m_iReinForce; //강화수치
	int m_iWeaponPride; //구입할떄 필요한 골드량, 중복획득시 구입할떄금액의 50프로 획득
	bool m_bGotFlag; //보유 유무
	// int m_iOwndedNumber; //보유숫자 //이변수를 쓰게될경우 불로선언된 보유유무 를 없앨 예정
	WeaponSkill m_ClassUniqueSkill; //고유스킬
public:
	Weapon();
	void InputWeaponData(string WeaponType, string Name, string Introduce, int Grade, int WeaponNumber ,
		int EquipLevel,int Atk, int Sheild, int Gold, bool GetFlag, WeaponSkill UniqueSkill);
	//아이템정보넣기
	void SaveWeaponData(ofstream &save);
	void WeaponGet(); //아이템보유 유무 변경
	//void ReinForce(); //아이템강화
	//업캐스팅으로 관리하는것을 보여주기 위하여추가함
	virtual string WeaponNamePlusWeaponType() = 0; //무기이름앞에 무기타입 텍스트 추가되게끔(업캐스팅보여주기위한용도)
	//virtual void PrintWeaponType();
/*
	추상 클래스(abstract class)
		C++에서는 하나 이상의 순수 가상 함수를 포함하는 클래스를 추상 클래스(abstract class)라고 합니다.

		이러한 추상 클래스는 객체 지향 프로그래밍에서 중요한 특징인 다형성을 가진 함수의 집합을 정의할 수 있게 해줍니다.

		즉, 반드시 사용되어야 하는 멤버 함수를 추상 클래스에 순수 가상 함수로 선언해 놓으면, 이 클래스로부터 파생된 모든 클래스에서는 이 가상 함수를 반드시 재정의해야 합니다.



		추상 클래스는 동작이 정의되지 않은 순수 가상 함수를 포함하고 있으므로, 인스턴스를 생성할 수 없습니다.

		따라서 추상 클래스는 먼저 상속을 통해 파생 클래스를 만들고, 만든 파생 클래스에서 순수 가상 함수를 모두 오버라이딩하고 나서야 비로소 파생 클래스의 인스턴스를 생성할 수 있게 됩니다.

		하지만 추상 클래스 타입의 포인터와 참조는 바로 사용할 수 있습니다.
*/

	inline WeaponSkill GetWeaponSKillData() //무기고유스킬가져오기
	{
		return m_ClassUniqueSkill;
	}
	inline string GetWeaponName() //무기이름가져오기
	{
		return m_strWeaponName;
	}
	inline int GetWeaponPride() //무기가격 가져오기
	{
		return m_iWeaponPride;
	}
	inline int GetWeaponNumber() //무기번호 가져오기
	{
		return m_iWeaponNumber;
	}
	inline int GetWeaponatk() //무기공격력 가져오기
	{
		return m_iWeaponAtk;
	}
	inline int GetWeaponShield() //무기방어력 가져오기
	{
		return m_iWeaponSheild;
	}
	inline int GetEquipLimintLevel() //무기착용재한레밸 가져오기
	{
		return m_iEquipLevel;
	}
	inline bool GetGotFlag() //무기보유 유무 가져오기
	{
		return m_bGotFlag;
	}
	virtual ~Weapon();
};

