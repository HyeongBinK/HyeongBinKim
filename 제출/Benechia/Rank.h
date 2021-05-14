#pragma once
#include "BaseHeader.h"

struct Data
{
	string PlayerName;
	int Score;
	int Stage;
};


class Rank
{
private:
	vector<Data> Records;
protected:
public:
	void SaveRank(string name, int score, int stage); //저장
	int LoadRank(); //로드로드 성공시 1 실패시 0
	//void SortRecords(); //기록 내림차순정렬(스테이지 스코어)
	void ShowRank(); //기록보여주기
	void ClearRankData(); //게임완전종료할떄 조건문을 걸어서 혹시 잔여파일이 남아있다면 클리어
};

