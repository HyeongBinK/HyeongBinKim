#pragma once
#include "BaseHeader.h"

template<typename Type>
Type Min(Type Num1, Type Num2);

class Quiz2
{
private:
	float m_fnum1;
	float m_fnum2;
protected:
public:
	void PlayQuiz2();
	void InputNumber();
	void ShowNumber();
};

