#include<iostream>
using namespace std;

//void main()
//{
//	cout << 3 + 4 << endl;
//	cout << "korea" + 1 << endl;
//	cout << "korea" + 2 << endl;
//	cout << "korea" + 3 << endl;
//	cout << 4 + "korea" << endl;
//	cout << 3 + "korea" << endl;
//	//cout << "kor" + "ea" << endl;
//}

//Object + Essence
//class Point
//{
//private :
//	int x, y;
//public :
//	Point(int a, int b)
//	{
//		x = a;
//		y = b;
//	}
//	void Print()
//	{
//		cout << "x = " << x << ", y = " << y << "\n";
//	}
//	friend Point operator + (Point tmp, int data);
//};
//
//Point operator + (Point tmp, int data)
//{
//	cout << "객체 + 정수" << "\n";
//	tmp.x = tmp.x + data;
//	tmp.y = tmp.y = data;
//	return tmp;
//}
//
//void main()
//{
//	Point ov1(10, 20), ov2(0, 0);
//	ov2 = ov1 + 10;
//	ov2.Print();
//}

//Object == Object
//class Point
//{
//private : 
//	int x, y;
//public :
//	Point(int a, int b)
//	{
//		x = a;
//		y = b;
//	}
//	void Print()
//	{
//		cout << "x = " << x << ", y = " << y << "\n";
//	}
//	bool operator == (Point tmp);
//};
//
//bool Point::operator==(Point tmp)
//{
//	if((this->x == tmp.x) && (this->y== tmp.y))
//		return true;
//	else
//		return false;
//}
//void main()
//{
//	Point ov1(10, 20), ov2(10, 20);
//	if(ov1 == ov2)
//	cout << "같다." << "\n";
//}

//Increment/Decrement_Operator
class Count
{
	int cnt1;
	int cnt2;
public:
	Count()
	{
		cnt1 = 0;
		cnt2 = 0;
	}
	Count(int n1, int n2)
	{
		cnt1 = n1;
		cnt2 = n2;
	}
	int GetCnt1()
	{
		return cnt1;
	}
	int GetCnt2()
	{
		return cnt2;
	}
	void operator ++() 
	{ 
		++cnt1; 
		++cnt2;
	}
	void operator --()
	{
		--cnt1;
		--cnt2;
	}
};

void main()
{
	Count co1(5, 10), co2;
	++co1;
	--co2;
	cout << "co1.cnt1 : " << co1.GetCnt1() << "\nco1.cnt2 : " << co1.GetCnt2() << endl;
	cout << "co2.cnt1 : " << co2.GetCnt1() << "\nco2.cnt2 : " << co2.GetCnt2() << endl;

}