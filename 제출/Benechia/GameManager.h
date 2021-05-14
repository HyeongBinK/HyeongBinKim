#pragma once
#include "BaseHeader.h"
#include "WardManager.h"
#include "Ward.h"
#include "Rank.h"

#define FINALSTAGE 10
#define NAMELENGTHLIMIT 10
#define ATTACKWARDLENGTHLIMIT 20

enum ITEM
{
	ITEM_eENEMYSPEEDUP = 1,
	ITEM_eENEMYSPEEDDOWN,
	ITEM_eENEMYSTOP,
	ITEM_eENEMYCLEAR
};

//PlayClass역할
class GameManager
{
private :
	string m_strPlayerName; //플레이어이름
	int m_iPlayerLife; //플레이어라이프(10개의 값을 생성자에서 주며 게임오버시 다시 10개로 초기화) 0이되면 게임오버
	int m_iScore; //점수
	int m_iStage; //도달스테이지
	bool m_bGameClearFlag; //게임마지막스테이지클리어시 트루로 바뀜
	int m_iEnemySpeedUpItem; //적속도상승아이템갯수
	int m_iEnemySpeedDownItem; //적속도다운 아이템갯수
	int m_iEnemyStopItem; //적멈춤아이템갯수
	int m_iEnemyClearItem; //적군전멸(점수는 오르지않음) 아이템갯수
	int m_iScreenWidth; //화면 가로크기(화면크기변경기능은 없으므로 생성자에서 드로우매니저에 선언된 기본값(define WIDTH) 줄예정)
	int m_iScreenHeight; //화면 세로크기(화면크기변경기능은 없으므로 생성자에서 드로우매니저에 선언된 기본값(define HEIGHT) 줄예정)
	WardManager Ward_Manager;
	Rank Rank_Manager;
protected :
public:
	GameManager();
	void GameSelect(); //게임프로그램 실행시 게임제목 게임시작 랭크 종료 보여줄 기능(함수)
	void GameStart(); //게임시작(베네치아게임) //하늘에서 영단어가떨어지는거를 타이핑해서 부수는게임
	void MakeName(); //이름만들기 이벤트
	void StageChange(); //일정점수 도달후 스테이지변경
	void ShowRank(); //랭킹보여주기 (이름 스테이지 점수순)
	void ShowStage(); // 새 스테이지 시작시 화면 정리후 Stage1 같은거 표시
	bool GameOverCheck(); //라이프가 0이되면 게임오버표시와함께 sleep이나 pause를 걸어서 게임select 창으로 이동
	void ShowStory(); //게임시작시 스토리설명 s키를 눌러 스킵가능
	void ShowStatus(); //게임화면하단의 라이프상태 점수 이름을 보여주는 기능(함수)
	void SetToDefault(); //게임스테이지 이름 기타등등 디포트상태로
	~GameManager();

};

