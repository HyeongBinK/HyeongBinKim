#pragma once
#include "BaseHeader.h"
#include "Ward.h"

#define FIRSTSTAGEENEMYMAKETERM 2000
#define FIRSTSTAGEENEMYSPEED 500
#define FIRSTSTAGEENEMYSCORE 100

class WardManager
{
private:
	vector<string> Wards;
	vector<Ward> Enemy;
	int m_iCurClock;
	int m_iEnemyMakeTerm;
	int m_iEnemyFallenSpeed;
	int m_iEnemyKillScore;
	bool m_iStopEnemyFallFlag; //평상시엔 false 이다가 유저가 적군 스탑아이템 사용시 일정시간 트루로 변환되어 적군낙하 멈추는용도

protected:
public:
	WardManager();
	void LoadWards(); //단어 가져오기
	int MakeRandomXLocation(); //적군생성할떄 랜덤한 위치값 생성
	void MakeRandomEnemy(); //적군 생성관리함수
	void FallEnemy(int* PlayerScroe, int* PlayerLife); //적군 낙하관리함수
	void PlayerAttackEnenmy(string AttackWard); //플레이어가 적군을 공격하고 플레이어 점수상승
	void StageUp(); //목표점수도달후 스테이지 상승에 따른 난이도 상승
	void SetDefaultState(); //다시게임시작시 디폴트상태로 되돌리는역할
	void ClearData(); //게임종료할떄 혹시 벡터공간에 데이터가남아있으면 clear 

	//아이템
	void Item_SpeedUP(); //아이템기능1 : 적군스피드증가
	void Item_SpeedDown(); //아이템기능2 : 적군스피드하락
	void Item_StopEnemy(); //아이템기능3 : 적군일시정지
	void Item_ClearEnemy(); //아이템기능4 : 화면클리어

	~WardManager();
};