#include<iostream>
using namespace std;

//Friend 멤버함수 예제
//class A
//{
//private :
//	int x, y;
//public :
//	friend void Setxy(A& a);
//	A() { x = 0; y = 0; }
//	void Showxy()
//	{
//		cout << "x = " << x << endl;
//		cout << "y = " << y << endl;
//	}
//};
//
//void Setxy(A& a)
//{
//	cout << "x,y 좌표입력 : " << endl;
//	cin >> a.x >> a.y;
//}
//
//void main()
//{
//	A a;
//	a.Showxy();
//	Setxy(a);
//	a.Showxy();
//}

//Friend Class 예제
//class A
//{
//private :
//	int x, y;
//public :
//	friend class B;
//	A(int a, int b) :x(a), y(b) {}
//	void Showxy()
//	{
//		cout << "x = " << x << endl;
//		cout << "y = " << y << endl;
//	}
//};
//class B
//{
//private :
//	int x, y;
//public :
//	B() : x(0), y(0) {}
//	void GetA(A& a)
//	{
//		x = a.x; y = a.y;
//	}
//	void Showxy()
//	{
//		cout << "x = " << x << endl;
//		cout << "y = " << y << endl;
//	}
//};
//
//void main()
//{
//	A a(10, 15);
//	B b;
//	a.Showxy();
//	b.Showxy();
//	b.GetA(a);
//	a.Showxy();
//	b.Showxy();
//}

//Friend 전역함수 예제
class A
{
private :
	int x, y;
public :
	A(int a, int b) : x(a), y(b) {}
	friend void Showxy(A& a)
	{
		cout << "x = " << a.x << endl;
		cout << "y = " << a.y << endl;	
	}
};

void main()
{
	A a(10, 15);
	Showxy(a);
}
