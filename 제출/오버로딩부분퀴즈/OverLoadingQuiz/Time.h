#pragma once
#include "MainHeader.h"

class Time
{
private :
	int m_iHour;
	int m_iMin;
protected :
public :
	void ShowTime();
	Time operator + (Time time);
	Time();
	Time(int Hour, int Min);
	~Time();
};

