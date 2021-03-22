#include<iostream>
using namespace std;

//¿øº»
//struct Point
//{
//	int m_i_Data;
//	Point* link;
//};
//
//void EnQueue(Point **Front, Point **Rear, int Data)
//{
//	Point* newNode = new Point;
//	if (*Front == NULL)
//	{
//		*Front = newNode;
//		*Rear = newNode;
//	}
//	//newNode->link = *Rear;
//
//	if (*Front != NULL)
//	{
//		Point * tmp;
//		tmp = *Rear;
//		*Rear = newNode;
//		tmp->link = newNode;
//	}
//
//
//	newNode->m_i_Data = Data;
//}
//
//void DeQueue(Point **Front)
//{
//	Point*tmp;
//	tmp = *Front;
//	cout << tmp->m_i_Data << endl;
//	*Front = tmp->link;
//	delete tmp;
//
//}
//
//void main()
//{
//	Point* Front = NULL, *Rear = NULL;
//
//	EnQueue(&Front, &Rear, 10);
//	EnQueue(&Front, &Rear, 7);
//	EnQueue(&Front, &Rear, 23);
//
//	DeQueue(&Front);
//	DeQueue(&Front);
//	DeQueue(&Front);
//}

template<typename Q>
class Point
{
private:
	Q m_i_Data;
	Point* link;
public:
	void EnQueue(Point** Front, Point** Rear, Q Data)
	{
		Point* newNode = new Point;
		if (*Front == NULL)
		{
			*Front = newNode;
			*Rear = newNode;
		}
		else if (*Front != NULL)
		{
			Point * tmp;
			tmp = *Rear;
			*Rear = newNode;
			tmp->link = newNode;
		}
		newNode->m_i_Data = Data;
	}

	void DeQueue(Point **Front)
	{
		Point*tmp;
		tmp = *Front;
		cout << tmp->m_i_Data << endl;
		*Front = tmp->link;
		delete tmp;
	}
};

void main()
{
	Point<float> Queue;
	Point<float>* Front = NULL, *Rear = NULL;

	Queue.EnQueue(&Front, &Rear, 10);
	Queue.EnQueue(&Front, &Rear, 7);
	Queue.EnQueue(&Front, &Rear, 23);

	Queue.DeQueue(&Front);
	Queue.DeQueue(&Front);
	Queue.DeQueue(&Front);
}