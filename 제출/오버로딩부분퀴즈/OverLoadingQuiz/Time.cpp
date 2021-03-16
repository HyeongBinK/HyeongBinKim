#include "Time.h"

Time::Time()
{
	m_iHour = 0;
	m_iMin = 0;
}

Time::Time(int Hour, int Min)
{
	m_iHour = Hour;
	while (Min > 60)
	{
		if (Min >= 60)
		{
			Min -= 60;
			m_iHour++;
		}
	}
	m_iMin = Min;
}

void Time::ShowTime()
{
	cout << "총 공부 시간 : "<< m_iHour << "시 " << m_iMin << "분" << endl;
}

Time Time::operator+(Time time)
{
	this->m_iHour += time.m_iHour;
	this->m_iMin += time.m_iMin;

	if (this->m_iMin >= 60)
	{
		this->m_iHour++;
		this->m_iMin -= 60;
	}

	return Time();
}

Time::~Time()
{

}
