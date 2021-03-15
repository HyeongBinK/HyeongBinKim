#pragma once
#include"BaseHeader.h"
#include"Monster.h"
#include"DrawManager.h"

#define FIELDMAXMONSTER 10 //필드내 몬스터재한숫자
#define MAXBOSSGAGE 5 //보스소환게이지
#define NORMAL_MONSTER_MAKE_COOLTIME 1000 //몬스터생성쿨타임

class MonsterManager 
{
private:
	int m_iMonsterMakeClock; //몬스터생성클락
	int m_iFieldMonsterNum; //필드의몬스터숫자 
	int m_iBossSummonCount; //보스몹은 해당던전의 일반몬스터 5마리 처리시 최대한마리 등장
	int m_iMonsterMakeCoolTime; //몬스터생성쿨타임
	DrawManager Draw_Manager;  
	vector<Monster> MonstersData; //몬스터들의 데이터
	vector<Monster> InDungeonMonster; //던전에서 생성된 몬스터들의 위치좌표가 더해진 몬스터의 데이터
	Monster JowMobData; //몹조우시 조우한 몬스터의 정보를 담게되는 클래스
public:
	MonsterManager();
	void LoadMonsterData(string LoadFileName); //몬스터데이터 불러오기(몬스터가 성장하지않으므로 항상똑같은 파일명)
	void MakeMonsterInDungeon(int MonsterNumber, Point PlayerLocation); //(던전안에 몬스터 생성)
	void DrawMonster(); //던전내생성된몬스터 전체 다시그려주기(게임내 메뉴창, 배틀페이즈 다녀올시 활용)

	void EraseMonsterData(); //몬스터데이터지움(게임종료시)
	void ResetMonsterInDungeon(); //던전내몬스터지움(던전나갈시)
	void FieldMonsterDie(Point PlayerLocation); //몬스터사망시 필드의몬스터 숫자감소
	int MonsterSpecialItemDrop(int MonsterNumber); //몬스터처치시 아이템 드랍여부

	void ChangeMonsterMakeClock(int NewClock); //몬스터소환시간관리변수변경
	void ResetBossSummonCount(); //보스몬스터소환게이지 리셋
	void SetJowMobData(int MonsterNumber); //몹조우시 조우한 몹의 모든정보를 가져옴
	void BossSummonCountUp(); //몬스터처치시 보스소환게이지상승
	int MonsterJowCheck(Point PlayerLocation); //몬스터조우시 해당몬스터번호리턴
	
	int GetInDungeonMonsterVectorFileSize()
	{
		return InDungeonMonster.size();
	}

	inline int GetFieldMonsterNumber()
	{
		return m_iFieldMonsterNum;
	}
	inline int GetBossSummonCount()
	{
		return m_iBossSummonCount;
	}

	inline int GetMonsterClock()
	{
		return m_iMonsterMakeClock;
	}
	inline Monster GetJowMobData()
	{
		return JowMobData;
	}

	~MonsterManager();
};

