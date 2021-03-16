#pragma once
#include"BaseHeader.h"
#include"Skill.h"
#include"DrawManager.h"

class SkillManager  
{
private:
	DrawManager Draw_Manager;
	vector<Skill> Skills;
	//Skill UseSkill;
protected:
public:
	SkillManager();
	//데이터관리부분
	void SaveSkillData(string SaveFileName); //스킬데이터(레밸등 정보) 저장
	void LoadSkillData(string LoadFileName); //스킬데이터 불러오기
	void ClearSkillData(); //게임종료나 중간로드시 기존데이터초기화

	//기능함수부분
	void ChangeSkillCanBeAcquiredBySkillNumber(int SkillNumber); //스킬번호를 받아와서 스킬습득가능불가능여부 변경
	//void SetSkillData(int SkillNumber); //사용한스킬데이터 받아옴
	void UpGradeSkill(int PlayerClassNumber, int* SkillPoint); //스킬레밸업
	void SkillLevelUp(int SKillNumber); //스킬레밸업시 스킬위력변경
	void UseSkillInBattlePhase(); //배틀페이즈에서 스킬사용입력시 표시될 스킬선택창
	Skill GetSkillAllDataBySkillNumber(int SkillNumber); //스킬번호로 스킬을조회해서 그스킬데이터를 전부가져옴
	//int GetSkillMpCostbySkillNumber(int SkillNumber); //스킬번호로 소모되는 마나량 가져옴 
	//int GetSkillDammageBySkillNumber(int SkillNumber); //스킬번호로 데미지증가퍼센트 가져옴
	//인터페이스
	void ShowAndUpgradeSkill(int PlayerClass, int SkillPoint); //스킬포인트분배시 표시할창
	void ShowCanLearn(int SkillNumber, int Line); //배울수있는지없는지
	void SkillUseError(); //사용할수없는 스킬을 사용하려했을떄 표시하는 에러창
	void ShowCanNotLearnSkill(); //습득할수없는 스킬을 배울려했을떄 표시하는 에러창
	void SkillPointError(); //스킬포인트부족시 표시되는 창
	/*inline Skill GetUseSkillData()
	{
		return UseSkill;
	}*/
	~SkillManager();
};

