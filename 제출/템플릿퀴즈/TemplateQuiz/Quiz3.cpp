#include "Quiz3.h"

template<typename Type>
Type Max(Type num1, Type num2, Type num3)
{
	if (num1 >= num2 && num1 >= num3)
		return num1;
	else if(num2 <= num3)
		return num3;
	else
		return num2;
}

void Quiz3::InputNumber()
{
	cout << "숫자입력 : ";
	cin >> m_fnum1 >> m_fnum2 >> m_fnum3;
}

void Quiz3::ShowNumber()
{
	cout << "최대값 = " << Max(m_fnum1, m_fnum2, m_fnum3) << endl;
}

void Quiz3::PlayQuiz3()
{
	InputNumber();
	ShowNumber();
}