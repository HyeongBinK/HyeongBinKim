#include<iostream>
using namespace std;


//TemplateFunction
//void Sum(int su1, int su2)
//{
//	int sum;
//	sum = su1 + su2;
//	cout << sum << endl;
//}
//
//void main()
//{
//	int a = 1, b = 2;
//	Sum(a, b);
//}

//template<typename Type>
//void Sum(Type su1, Type su2)
//{
//	Type sum;
//	sum = su1 + su2;
//	cout << sum << endl;
//}
//
//void main()
//{
//	int a = 1, b = 2;
//	Sum(a, b);
//}

//template<typename Type>
//void Add(Type n1, Type n2);
//
//void main()
//{
//	int su1, su2;
//	double num1, num2;
//	cout << "두 정수 입력 : ";
//	cin >> su1 >> su2;
//	cout << "두 실수 입력 : ";
//	cin >> num1 >> num2;
//	Add(su1, su2);
//	Add(num1, num2);
//}
//
//template<typename Type>
//void Add(Type n1, Type n2)
//{
//	Type sum;
//	sum = n1 + n2;
//	cout << "n1 + n2 =" << sum;
//	cout << endl;
//}

//template<typename t1, typename t2>
//t1 func(t2 num)
//{
//	cout << num << endl;
//	return num;
//}
//
//void main()
//{
//	double su = 10.2;
//	//func(su);
//	cout << func<int>(su) << endl;
//	//cout << func<float>(su) << endl;
//}

template<typename val>
void func(val v)
{
	cout << "Template Function \t" << v << endl;
}

template<>
void func<char>(char v)
{
	cout << "Specialization Template Function \t" << v << endl;
}

void main()
{
	func(10);
	func(10.1);
	func(0x10);
	func('a');
	func("abc");
}