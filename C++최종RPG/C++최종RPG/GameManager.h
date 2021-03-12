#pragma once
#include"BaseHeader.h"
#include"DrawManager.h"
#include"PlayerManager.h"
#include"MonsterManager.h"
#include"WeaponManager.h"

#define SAVELOADSLOTMAX 10

enum OUTDUNGEON
{
	OUTDUNGEON_eGOBSHOME =1,
	OUTDUNGEON_eMINOTASHOME,
	OUTDUNGEON_eCULSEDTEMPLE,
	OUTDUNGEON_eDRAGONNEST,
	OUTDUNGEON_eWEAPONTRADER,
	OUTDUNGEON_eCHARACTERINFORMATION,
	OUTDUNGEON_eGAMESAVE,
	OUTDUNGEON_eGAMELOAD,
	OUTDUNGEON_eENDGAME
};

enum INDUNGEON
{
	INDUNGEON_eCHARACTERINFORMATION = 1,
	INDUNGEON_eDUNGEONEXIT,
	INDUNGEON_eRETURNTODUNGEON
};

enum CHARACTERINFORMATION
{
	CHARACTERINFORMATION_eSTATUS = 1,
	CHARACTERINFORMATION_eUPGRADESTATUS,
	CHARACTERINFORMATION_eSKILL,
	CHARACTERINFORMATION_eCLASSCHANGE,
	CHARACTERINFORMATION_eWEAPON,
	CHARACTERINFORMATION_eRETURN,

};

enum BATTLEPHASESELECT
{
	BATTLEPHASESELECT_eNORMALATTACK =1,
	BATTLEPHASESELECT_eSKILLATTACK,
	BATTLEPHASESELECT_eRUNFROMBATTLE
};

enum BATTLERESULT
{
	BATTLERESULT_eNOTDEAD =1,
	BATTLERESULT_ePLAYERDEAD,
	BATTLERESULT_eMONSTERDEAD,
};

class GameManager
{
private:
	DrawManager Draw_Manager; //그림관리자
	PlayerManager Player_Manager; //플레이어블캐릭터 관리자
	MonsterManager Monster_Manager; //몬스터관리자
	WeaponManager Weapon_Manager; //무기관리자
	bool m_bPlayerDeadFlag; //기본적으론 false 플레이어가 죽으면 트루로변환후 던전밖으로나간후 다시 false 로 변환 
	bool m_bGameEndFlag; //종료체크플래그
	bool m_bExitDungeonFlag; //던전탈출체크플래그
protected:

public:
	GameManager();
	void PlayGame(); //게임시작(새게임, 기존데이터로딩해서 게임하기 등) 모든것의 시작부분
	
	//데이터저장로드
	void NewGame(); // 새로운게임시작(초기데이터로딩) 
	void SaveGame(int i); //게임저장
	void LoadGame(int i); //게임로드하기
	void DataClear(); //게임중간로드시 기존데이터 클리어
	
	//세이브와 로드 슬롯
	void SaveSlot(); //세이브슬롯창뛰우고 골라서 세이브(만들어지지않았을시엔 만들어지고 세이브)(파일이있다면 덮어쓰기)
	bool LoadSlot(); //로드슬롯창뛰우고 골라서 해당파일 로드(해당파일이없다면 로드불가)

	//던전밖(마을상태)
	void GameManipulation(); //전체적인 게임진행(아래 항목들이 들어감)
	void OutDungeonManipulation(); //던전밖 조작(던전, 캐릭터스태이터스창 등선택기능)
	void InDungeonSelectManipulation(); //던전내 메뉴조작
	//void WeaponTraderManipulation(); //무기상점내 조작
	void CharacterMenuManipulation(); //캐릭터정보창조작

	//인던전
	void InDungeonManipulation(int MonsterNumber); //던전내 몬스터생성및 캐릭터이동등 던전내부 조작
	void BattlePhase(int MonsterNumber);
	void BattleDammageCalculate(Monster* JowMob, int WeaponAtk, int WeaponShield, WeaponSkill WeaponSkillData, Skill UseSkill); //몬스터배틀중 데미지계산시스템(캐릭터 스탯 + 무기 +스킬등)
	void BattlePhase_MonsterDammage(Monster* JowMob, int WeaponShield); //몬스터가 플레이어한테주는데미지
	void BattlePhase_PlayerDammage(Monster* JowMob, int WeaponAtk, WeaponSkill WeaponSkillData, Skill UseSkill); //플레이어가 몬스터에게 주는데미지
	void ReDrawMap(); //인던전도중 메뉴창다녀왔을시 원래상태로 되돌리는기능
	bool PlayerDeadByMonster(int MemoPlayerOriginalSpeed); //플레이어 피가 0이하가 될시실행(플레이어가 반동턴에 죽을수도있기에 똑같은코드 2번쓰는거 방지용)

	//인터페이스
	void ShowVictory(int GiveExp, int Gold, int SpecialItem); //몬스터처치시 승리표시
	void YouDied(); //캐릭터사망시 유다이표시
	void ShowStartMenu(); //게임시작메뉴
	void ShowOutDungeonMenu(); //던전선택및 저장 로드 창
	void ShowInDungeonMenu(); //인던전 메뉴창
	void ShowCharacterMenu(); //캐릭터정보관련 창
	//void ShowWeaponTraderMenu(); //무기상점메뉴 창
	//void ShowWeaponNameAndPride(int WeaponNumber, int Line); //무기상점내 무기가격과 무기이름 줄
	void ShowSaveAndLoadComplete(); //세이브로드시 완료 표시창
	void ShowInDungeonKeyRule(); //인던전내 조작키설명
	//void UpgradeSkill(); //스킬쪽에있는게맞는거같으나 유저쪽 스킬포인트정보를 가져와야되기에 이클래스에 위치
	//void ChangeWeaponMenu(); //무기쪽에있는게바람직하나 유저의 장착중인 무기정보를 변경해야하기에 해당 클래스에 위치시킴
	void ChangeWeapon(int WeaponNumber); //장착무기변경
	void DontMoveByCoolTime(); //반동에의해 움직일수없다 표시하는창
	void ScreenSizeSetting(); //게임화면셋팅
	~GameManager();
};

