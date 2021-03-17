#pragma once
#include "MainHeader.h"

class Quiz1
{
private : 
	int m_iX;
	int m_iY;
	//X,Y를 float 로 선언하면 필요없는코드지만 예외를처리할필요도없으므로 이런방식으로만들어봤습니다
	//작은수에서 큰수로 나눌수있게 예외처리하기위해 추가
	float m_iDummyX;
	float m_iDummyY;
protected :
public :
	Quiz1();
	Quiz1(int num1, int num2);
	void ShowNumber();
	Quiz1 operator /(Quiz1 tmp);

	~Quiz1();
};

