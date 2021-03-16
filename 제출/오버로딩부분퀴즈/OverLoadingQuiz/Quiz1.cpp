#include "Quiz1.h"

Quiz1::Quiz1()
{
	m_iX = 0;
	m_iY = 0;
	m_iDummyX = 0;
	m_iDummyY = 0;
}

Quiz1::Quiz1(int num1, int num2)
{
	m_iX = num1;
	m_iY = num2;
	m_iDummyX = 0;
	m_iDummyY = 0;
}

void Quiz1::ShowNumber()
{
	if (m_iDummyX != 0 && m_iDummyY != 0)
	cout << "x = " << m_iDummyX << ", y = " << m_iDummyY << endl;
	else if(m_iDummyX != 0 && m_iDummyY == 0)
	cout << "x = " << m_iDummyX << ", y = " << m_iY << endl;
	else if (m_iDummyX == 0 && m_iDummyY != 0)
	cout << "x = " << m_iX << ", y = " << m_iDummyY << endl;
	else
	cout << "x = " << m_iX << ", y = " << m_iY << endl;
}

Quiz1 Quiz1::operator/(Quiz1 tmp)
{
	Quiz1 NewQuiz1;
	if ((this->m_iX >= tmp.m_iX))
		NewQuiz1.m_iX = this->m_iX / tmp.m_iX;
	else 
		NewQuiz1.m_iDummyX = this->m_iX / (float)tmp.m_iX;

	if ((this->m_iY >= tmp.m_iY))
		NewQuiz1.m_iY = this->m_iY / tmp.m_iY;
	else
		NewQuiz1.m_iDummyY = this->m_iY / (float)tmp.m_iY;

	return NewQuiz1;
}

Quiz1::~Quiz1()
{

}