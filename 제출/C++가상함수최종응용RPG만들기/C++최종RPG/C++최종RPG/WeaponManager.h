#pragma once
#include "BaseHeader.h"
#include "DrawManager.h"
#include "Weapon.h"
#include "Sword.h"
#include "TwoHandSword.h"

enum WEAPONTRADER_KEY
{
	WEAPONTRADER_KEY_eBEFOREPAGE =7,
	WEAPONTRADER_KEY_eNEXTPAGE,
	WEAPONTRADER_KEY_eRETURN
};

class WeaponManager 
{
private:
	int m_iMemoWeaponAtk;
	int m_iMemoWeaponShield;
	WeaponSkill MemoWeaponSkill;

	DrawManager Draw_Manager;
	//Weapon *tmp;
	//vector<tmp> WeaPons;
	//vector<Weapon> *WeaPons;
	vector<Weapon*> WeaPons;
	//Weapon EquipWeaponData;
protected:

public:
	WeaponManager();
	//데이터관리
	void LoadWeaponsData(string LoadFileName); //아이템상태불러오기
	void SaveWeaponsData(string SaveFileName); //아이템상태저장
	void ClearWeaponData(); //게임종료시나 로드시 데이터삭제

	void WeaponGet(int WeaponNumber); //무기획득시 무기획득관련불변수 true로 변환하며 장착가능하게끔
	void ShowGetorNot(int WeaponNumber); //무기보유여부 알수있게끔표시 하기위한변수
	//void SetEquipWeaponData(int WeaponNumber); //장착한 무기의 모든정보를 가져옴
	void SetWeaponAtkShieldSkillByNumber(int WeaponNumber); //장착한무기의 정보를 무기번호로 조회하여 공격력 방어력 수치값을 기억시킴 
	bool FindWeaponGotFlag(int WeaponNumber); //무기보유여부를 무기번호로 확인하여 있으면 트루 없으면 false 반환
	int FindWeaponEquipLimitLevel(int WeaponNumber); //무기의 레밸재한을 무기번호로 가져와서 무기레밸재한값을 반환
	
	int WeaponTrader(int PlayerGold); //무기상점시스템
	bool BuyWeapon(int PlayerGold, int WeaponPride); //무기계산할때 골드가충분하면 무기를 획득하고 골드가 부족하면 골드부족창 표시하게끔
	//void ShowWeaponNameAndPride(Weapon WeaponData, int Line); //무기상점내 무기가격과 무기이름 줄
	void GoldError(); //골드부족할시 표시되는 에러창
	int WeaponChange(int EquipWeaponNumber, int PlayerLevel); //무기변경창

	void ShowWeaponEquipError(); //없는무기를 장착하려했을시 표시되는 창
	
	string WeaponNumberToWeaponName(int WeaponNumber); //무기번호를 무기이름으로 변환
	int WeaponNumberToWeaponPride(int WeaponNumber); //무기번호를 무기가격으로 변환

	/*inline Weapon GetEquipWeaponData()
	{
		return EquipWeaponData;
	}*/
	inline int GetEquipWeaponAtk()
	{
		return m_iMemoWeaponAtk;
	}
	inline int GetEquipWeaponShield()
	{
		return m_iMemoWeaponShield;
	}
	inline WeaponSkill GetEquipWeaponSKillData()
	{
		return MemoWeaponSkill;
	}
	~WeaponManager();
	
};

