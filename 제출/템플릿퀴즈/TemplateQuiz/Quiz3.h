#pragma once
#include "BaseHeader.h"

template<typename Type>
Type Max(Type Num1, Type Num2, Type Num3);

class Quiz3
{
private:
	float m_fnum1;
	float m_fnum2;
	float m_fnum3;
protected:
public:
	void PlayQuiz3();
	void InputNumber();
	void ShowNumber();
};