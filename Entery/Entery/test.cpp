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

//// ��������
//using namespace std;
//int main()
//{
//	int x, y;
//	char ch;
//	cin >> x >> y >> ch;
//	cout << x << " " << y << " " << ch;
//}

// ȱʡ������Ĭ�ϲ�����������������ʱ���������β�ָ����һ��Ĭ��ֵ��
// ������øú���δ���Σ���ʹ�����ȱʡ������������ʱ�����ˣ�������ʹ�ô��ݵ�ʵ��

//// ȫȱʡ
//int Add(int a = 10, int b = 20)
//{
//	return a + b;
//}
//
//// ��ȱʡ ��������������δ���ʵ�Σ����ܼ����Ծ��ʵ��
//void Print(int a, int b = 10, int c = 20)
//{
//	cout << a << "   " << b << "   "<< c <<endl;
//}

//int main()
//{
//	// ������øú���δ���Σ���ʹ�����ȱʡ������������ʱ�����ˣ�������ʹ�ô��ݵ�ʵ��
//	int ret1 = Add();
//	int ret2 = Add(1,2);
//	cout << ret1<<"   " << ret2 << endl;
//	// ��ȱʡ���� ��������������δ���ʵ�Σ����ܼ����Ծ��ʵ��
//	Print(11);
//	Print(11, 12);
//	Print(11, 12, 13);
//
//	return 0;
//}

//// ������������������,������ȱʡֵ�����岻Ҫ��
//int Mul(int a = 1, int b = 6);
//
//int main()
//{
//	return 0;
//}
//// ��ȱʡֵ�� C2572�ض���Ĭ�ϲ���
//int Mul(int a, int b)
//{
//	return a * b;
//}

//// �������أ�һ�ʶ��� C++�������ж��ͬ����������
//// ��ͬһ�������� ��������ͬ ������ͬ�����͡�������˳���뺯�����޹�
//
//// �������Ͳ�ͬ
//void Swap(int* a, int* b)
//{
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
//void Swap(double* x, double* y)
//{
//	double tmp = *x;
//	*x = *y;
//	*y = tmp;
//}
//
//// ����������ͬ
//void Print(int a)
//{
//	cout << a << endl;
//}
//void Print(int x, int y)
//{
//	cout << x << "  " << y << endl;
//}
//// ����˳��ͬ
//void f(int a, double b)
//{
//	cout<<"f(int a, double b)" << endl;
//}
//
//void f(double b, int a)
//{
//	cout << "f(double b, int a)" << endl;
//}
////// ����ֵ������Ϊ�ж�����
////// C2556 ֻ���ڷ��������ϲ�ͬ
////void fun(){}
////int fun(){}
//
////// ����������������������� ������Ҳ��֪�������ĸ�����
////// ��ȱʡֵȥ���󣬸�������ʵ�μ���˳������
////void f1()
////{
////	cout << "f()" << endl;
////}
////void f1(int a = 10)
////{
////	cout << "f(int a)" << endl;
////}
//
//
//int main()
//{
//	int a = 10, b = 20;
//	double x = 1.2, y = 2.4;
//	cout << a << "  " << b << endl;
//	cout << x << "  " << y << endl;
//	Swap(&a, &b);
//	Swap(&x, &y);
//	cout << a << "  " << b << endl;
//	cout << x << "  " << y << endl;
//
//	Print(2);
//	Print(1,2);
//	f(1,1.2);
//	f(2.1, 1);
//
//	//// C2668 �����غ����ĵ��ò���ȷ
//	//f1();
//	//f1(20);
//
//	return 0;
//}

//// ��ʾC++���������ι���
//void print(int);
//void print(double);
//int main()
//{
//	// error LNK2019: �޷��������ⲿ���� "void __cdecl print(int)" (?print@@YAXH@Z)������ main �������˸÷���
//	print(42);
//	//  error LNK2019: �޷��������ⲿ���� "void __cdecl print(double)" (?print@@YAXN@Z)������ main �������˸÷���
//	print(2.1);
//	return 0;
//}

//
//// ����&
//using namespace std;
//int main()
//{
//	int a = 1;
//	// �����ڶ���ʱ�����ʼ��  error C2530: ��nq��: �����ʼ������
//	//int& nq;
//	// һ�����������ж������
//	int& na = a;
//	int& nb = a;
//	int& nc = na;
//
//	int num = 20;
//	// ��ֵ
//	na = num;
//
//	// һ��ȷ����һ������ʵ��󣬾Ͳ�������������ʵ��
//	int b = 2;
//	int& np = b;
//	np = na; // �����Ǹ�ֵ�������Ǹı�����ָ��
//	
//	return 0;
//}
//
// 
//// const��������
//using namespace std;
//int main()
//{
//	const int a = 10;
//	// ������ aֻ�� ra�ɶ���д Ȩ�޷Ŵ�
//	// int& ra = a;
//
//	// ���� a��pa����ֻ�� Ȩ��ƽ��
//	const int& pa = a;
//
//	// ���� b�ɶ���д rbֻ�� Ȩ����С
//	int b = 10;
//	const int& rb = b;
//
//}

//// ����ת���ͱ��ʽ����������ʱ���� ��ʱ�������г���
//using namespace std;
//int main()
//{
//	int a = 20;
//	int c = 10;
//	double b = a;
//	// E0434 �ǳ����޶�
//	// int& rb = b;
//	const int& rb = b;
//
//	// E0461 �ǳ������õĳ�ʼֵ����Ϊ��ֵ
//	// int& plus = a + c;
//	const int& plus = a + c;
//
//	return 0;
//}

//using namespace std;
//int main()
//{
//	/*int numa = 10;
//	int* ptra = &numa;
//	cout << sizeof(int*) << endl;
//	cout << *ptra << endl;
//	cout << &numa << endl;
//	ptra++;
//	cout << *ptra << endl;
//
//	int& rnuma = numa;
//	cout << sizeof(rnuma) << endl;
//	cout << rnuma << endl;
//	cout << &numa << endl;
//	rnuma++;
//	cout << rnuma << endl;*/
//
//	int* ptr = nullptr;
//	int& rptr = *ptr;
//	/*cout << rptr <<endl;*/
//
//	return 0;
//}

// ��������
using namespace std;
inline int Add(int a = 10, int b = 30)
{
	return a + b;
}
int main()
{
	int a = 0, b = 3;
	Add(a, b);

	return 0;
}