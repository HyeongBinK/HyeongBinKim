#include "Quiz2.h"

template<typename Type>
Type Min(Type num1, Type num2)
{
	if (num1 > num2)
		return num2;
	else
		return num1;
}

void Quiz2::InputNumber()
{
	cout << "숫자입력 : ";
	cin >> m_fnum1 >> m_fnum2;
}

void Quiz2::ShowNumber()
{
	cout << "작은수 = " << Min(m_fnum1, m_fnum2) << endl;
}

void Quiz2::PlayQuiz2()
{
	InputNumber();
	ShowNumber();
}