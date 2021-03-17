#pragma once
#include "BaseHeader.h"

template<typename Type>
Type Plus1(Type num);

class Quiz1
{
private:
	//자료형을 플로트만 선언하면 더편하지만 template에 
	//인트형도 프로트형도 따로갈수있게끔 코드를꼬았음
	int m_inum; 
	float m_fnum;
protected:
public:
	void PlayQuiz1();
	void InputNumber();
	void ShowNumber();
};


