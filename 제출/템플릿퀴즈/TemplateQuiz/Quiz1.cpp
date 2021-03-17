#include "Quiz1.h"

template<typename Type>
Type Plus1(Type num)
{
	num += 1;
	return num;
}

void Quiz1::InputNumber()
{
	float Number;
	cout << "숫자입력 : ";
	cin >> Number;

	m_fnum = Number;
	m_inum = Number;

	if (m_inum == m_fnum)
		m_inum = Plus1(m_inum);
	else
		m_fnum = Plus1(m_fnum);
}

void Quiz1::ShowNumber()
{
	if (m_inum == m_fnum+1)
		cout << m_inum - 1 << " + " << 1 << " = " << m_inum << endl;
	else
		cout << m_fnum - 1 << " + " << 1 << " = " << m_fnum << endl;
}

void Quiz1::PlayQuiz1()
{
	InputNumber();
	ShowNumber();
}