#include <stdio.h>
#include <stdlib.h>
#include "head1.h"
#include <iostream>
//int rand = 10;
//int main()
//{
//	// C2365 rand�ض��� ��ǰ�Ǻ���
//	printf("%d\n", rand);
//	return 0;
//}

//// ����namespace������������
//namespace Vect
//{
//	int rand = 0;
//}
//
//int main()
//{
//	printf("%d", Vect::rand);
//	return 0;
//}

//// ���ļ��� �����ռ�ͬ������кϲ�
//namespace Vect
//{
//	// 1. �����ռ���Զ������/����/����
//	int num = 10;
//	int* ptr = &num;
//
//	void Print()
//	{
//		printf("HELLO,C++!\n");
//	}
//
//	struct node
//	{
//		int val;
//		struct node* next;
//	};
//
//	// 2. �����ռ����Ƕ�׶���
//	namespace coke
//	{
//		// ...
//	}
//}
//
//int main()
//{
//	return 0;
//}

//// ʹ�÷���
//
//// 1.�������޶���ָ������
//int num = 10;
//namespace Vect
//{
//	int num = 0;
//	char ch = '?';
//}
//
//int main()
//{
//	printf("%d\n", Vect::num);
//	printf("%c\n", Vect::ch);
//	// ���������޶�������������ռ䣬Ĭ�ϲ���ȫ����
//	printf("%d\n", ::num);
//	printf("%d\n", num);
//}

//// 2. usingչ���ֲ�����
//namespace Vect
//{
//	int num = 0;
//	char ch = '?';
//}
//using Vect::num;
//int main()
//{
//	printf("%d\n", num);
//	printf("%c\n", Vect::ch);
//	// ���������޶�������������ռ䣬Ĭ�ϲ���ȫ����
//}

//// 3. usingչ��ȫ�����
//namespace Vect
//{
//	int num = 0;
//	char ch = '?';
//}
//using namespace Vect;
//int main()
//{
//	printf("%d\n", num);
//	printf("%c\n", ch);
//	// ���������޶�������������ռ䣬Ĭ�ϲ���ȫ����
//}

// ��������
using namespace std;
int main()
{
	int x, y;
	char ch;
	cin >> x >> y >> ch;
	cout << x << " " << y << " " << ch;
}