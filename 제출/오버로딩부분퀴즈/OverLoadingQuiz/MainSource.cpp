#include "MainHeader.h"
#include "Quiz1.h"
#include "Time.h"

void main()
{
	cout << "1번문제" << endl;
	Quiz1 q1(10,20), q2(5,40);
	q1.ShowNumber();
	q2.ShowNumber();
	cout << "q1/q2(객체/객체)" << endl;
	q1.operator/(q2).ShowNumber();

	system("pause");

	int Select = 0;
	int Day = 1;
	int NewHour, NewMinute;
	Time TotalTime;

	while (Select != 2)
	{
		system("cls");
		cout << "2번문제" << endl;
		TotalTime.ShowTime();
		cout << "====공부 시간 관리 프로그램<" << Day << "Day>====" << endl;
		cout << "1.시간등록" << endl;
		cout << "2.종료" << endl;
		cout << "입력 : ";
		cin >> Select;

		if (Select == 1)
		{
			cout << "시간 : ";
			cin >> NewHour;
			cout << "분 : ";
			cin >> NewMinute;

			Time NewTime(NewHour, NewMinute);
			TotalTime.operator+(NewTime);
			Day++;
		}

	}







}
