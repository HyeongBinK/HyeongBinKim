#include<iostream>
using namespace std;

//1¹ø
//template<typename Type>
//class Point
//{
//private :
//	Type x, y;
//public :
//	Point(Type a, Type b)
//	{
//		x = a;
//		y = b;
//	}
//	void DisPlay()
//	{
//		cout << "x : " << x << "\n";
//		cout << "y : " << y << "\n";
//	}
//};
//
//void main()
//{
//	Point<int> PInt(10, 20);
//	Point<double> PDouble(10.4, 20.6);
//	PInt.DisPlay();
//	PDouble.DisPlay();
//}

//2¹ø
//template<typename Type>
//class Point
//{
//private:
//	Type x, y;
//public:
//	Point(Type a, Type b)
//	{
//		x = a;
//		y = b;
//	}
//	void DisPlay();
//};
//
//template<typename Type>
//void Point<Type>::DisPlay()
//{
//	cout << "x : " << x << "\n";
//	cout << "y : " << y << "\n";
//}
//
//void main()
//{
//	Point<int> PInt(10, 20);
//	Point<double> PDouble(10.4, 20.6);
//	PInt.DisPlay();
//	PDouble.DisPlay();
//}

//3¹ø 
//template<typename A, typename B>
//class Size
//{
//private:
//	int a, b;
//public:
//	Size()
//	{
//		a = sizeof(A);
//		b = sizeof(B);
//	}
//	void print()
//	{
//		cout << "a = " << a << ",b = " << b << endl;
//	}
//};
//
//void main()
//{
//	Size<char, int > si1;
//	Size<float, double> si2;
//	si1.print();
//	si2.print();
//}

template<typename T>
class STACK
{
private :
	T* top;
	int size;
public :
	STACK(int s)
	{
		size = s;
		top = new T[size];
	}
	void push(T a)
	{
		*top = a;
		top++;
	}
	void pop()
	{
		cout << *--top << endl;
	}
};

void main()
{
	STACK<float> stack(3);
	stack.push(2.2f);
	stack.push(1.1f);
	stack.pop();
	stack.pop();
}