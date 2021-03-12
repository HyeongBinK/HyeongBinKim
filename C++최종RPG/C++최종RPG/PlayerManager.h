#pragma once
#include"BaseHeader.h"
#include"Character.h"
#include"DrawManager.h"
#include"SkillManager.h"

enum STATUS
{
	STATUS_eSTR = 1,
	STATUS_eDEX,
	STATUS_eRETURN
};

class PlayerManager :virtual public Character
{
private:
	//int m_iWidth; //개인이 설정한 화면 가로크기
	//int m_iHeight; //개인이 설정한 화면 세로크기
	int m_iMaxMP; //최대마나
	int m_iMP; //현재마나
	int m_iNeedExp; //래밸업하는데 필요한 경험치량
	int m_iGetExp; //현재경험치량
	int m_iStatPoint; //스탯포인트
	int m_iSkillPoint; //스킬포인트
	int m_iStr; //물리공격력 상승
	int m_iDex; //물리공격력소량 상승, 공속상승
	int m_iOwnedGold; //캐릭터가 가지고있는 골드량 아이템강화 구입등에 소모
	int m_iEquipWeaponNumber; //착용하고있는아이템
	Point Location;
	DrawManager Draw_Manager;
	SkillManager Skill_Manager;
protected:
public:
	PlayerManager();
	void MakePlayerName(string Name); //새로운모험시작시 캐릭터 이름입력

	void LevelUp(); // 레밸업
	void Use_Gold(int Gold); //골드소모
	bool Use_Mp(int SkillMP); //스킬사용시 마나소모
	void NeedExp_Change(); //레밸업에따른 경험치요구량변경
	void Get_EXP(int GiveExp); // 경험치 획득
	void StatStatusChange(); //힘 덱스 스탯추가를 통한 기본능력치 변경
	void GetDeadPenalty(); //캐릭터사망후 부활시 받는 패널티
	void ClassChange(int Num); //전직
	void ItemEquip(int WeaponNumber); //아이템 장착
	void GetGold(int Gold); //골드획득
	void UpgradeSkill_PlusPlayerData(); //스킬레밸업
	// void ChangeMapSize(int Width, int Height); //맵사이즈변경
	
	void SavePlayerCharacter(string SaveFileName, int i); //플레이어데이터저장
	void LoadPlayerCharacter(string LoadFileName, int i); //플레이어데이터불러오기
	
	//인터페이스
	void ShowTotalStatus(); //종합스테이터스정보창
	string ClassNumbertoClassName(int ClassNumber); //스테이터스정보창에서 클래스번호를 이름으로 변환
	void UpGradeStatusPoint(); //스탯포인트분배시 표시할창
	void ShowClassChange(); //직업선택창
	void ShowMakeNameMenu(); //이름만들기메뉴
	void ShowSkillLearnError(); //습득불가능한 스킬을 배울려했을시 표시되는 창
	void StatPointError(); //스탯포인트 부족시 표시되는 창
	void GoldError(); //골드부족시 표시되는 창
	void MPError(); //마나부족시 표시되는 창 
	void LocationChange(int LocationX, int LocationY); //던전입장시 플레이어 좌표 던전중앙으로 이동
	void DrawCharacter(); //캐릭터그려주는 함수
	void ClearSkillData();
	//void PlayerMoveinDunGeon(char* ch); //던전안에서의 캐릭터움직임
	
	inline SkillManager GetSkillData()
	{
		return Skill_Manager;
	}

	inline int GetOwnedGold()
	{
		return m_iOwnedGold;
	}
	inline int GetCharacterMP() //캐릭터현재마나량내보내기
	{
		return m_iMP;
	}
	inline int GetCharacterMaxMP()
	{
		return m_iMaxMP;
	}
	inline int GetSkillPoint() //보유중인스킬포인트내보내기
	{
		return m_iSkillPoint;
	}
	inline int GetEquipWeaponNumber() //장착중인무기번호내보내기
	{
		return m_iEquipWeaponNumber;
	}
	inline Point GetPlayerLocation() //캐릭터위치좌표내보내기
	{
		return Location;
	}
	~PlayerManager();
};


