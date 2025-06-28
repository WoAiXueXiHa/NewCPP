#include <stdio.h>
#include <stdlib.h>
#include "head1.h"
#include <iostream>
//int rand = 10;
//int main()
//{
//	// C2365 rand重定义 以前是函数
//	printf("%d\n", rand);
//	return 0;
//}

//// 引入namespace进行命名隔离
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

//// 多文件下 命名空间同名会进行合并
//namespace Vect
//{
//	// 1. 命名空间可以定义变量/函数/类型
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
//	// 2. 命名空间可以嵌套定义
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

//// 使用方法
//
//// 1.域作用限定符指定访问
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
//	// 若域作用限定符左边无命名空间，默认查找全局域
//	printf("%d\n", ::num);
//	printf("%d\n", num);
//}

//// 2. using展开局部对象
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
//	// 若域作用限定符左边无命名空间，默认查找全局域
//}

//// 3. using展开全体对象
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
//	// 若域作用限定符左边无命名空间，默认查找全局域
//}

//// 输入和输出
//using namespace std;
//int main()
//{
//	int x, y;
//	char ch;
//	cin >> x >> y >> ch;
//	cout << x << " " << y << " " << ch;
//}

// 缺省参数（默认参数）函数声明或定义时，给函数形参指定的一个默认值，
// 如果调用该函数未传参，则使用这个缺省参数，若调用时传参了，则优先使用传递的实参

//// 全缺省
//int Add(int a = 10, int b = 20)
//{
//	return a + b;
//}
//
//// 半缺省 必须从左往右依次传递实参，不能间隔跳跃给实参
//void Print(int a, int b = 10, int c = 20)
//{
//	cout << a << "   " << b << "   "<< c <<endl;
//}

//int main()
//{
//	// 如果调用该函数未传参，则使用这个缺省参数，若调用时传参了，则优先使用传递的实参
//	int ret1 = Add();
//	int ret2 = Add(1,2);
//	cout << ret1<<"   " << ret2 << endl;
//	// 半缺省调用 必须从左往右依次传递实参，不能间隔跳跃给实参
//	Print(11);
//	Print(11, 12);
//	Print(11, 12, 13);
//
//	return 0;
//}

//// 函数声明定义分离情况,给声明缺省值，定义不要给
//int Mul(int a = 1, int b = 6);
//
//int main()
//{
//	return 0;
//}
//// 给缺省值了 C2572重定义默认参数
//int Mul(int a, int b)
//{
//	return a * b;
//}

//// 函数重载：一词多义 C++中允许有多个同名函数存在
//// 在同一作用域中 函数名相同 参数不同（类型、数量、顺序）与函数名无关
//
//// 参数类型不同
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
//// 参数数量不同
//void Print(int a)
//{
//	cout << a << endl;
//}
//void Print(int x, int y)
//{
//	cout << x << "  " << y << endl;
//}
//// 参数顺序不同
//void f(int a, double b)
//{
//	cout<<"f(int a, double b)" << endl;
//}
//
//void f(double b, int a)
//{
//	cout << "f(double b, int a)" << endl;
//}
////// 返回值不能作为判断条件
////// C2556 只是在返回类型上不同
////void fun(){}
////int fun(){}
//
////// 这两个函数会产生调用歧义 编译器也不知道调用哪个函数
////// 将缺省值去掉后，给出具体实参即可顺利编译
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
//	//// C2668 对重载函数的调用不明确
//	//f1();
//	//f1(20);
//
//	return 0;
//}

//// 演示C++函数名修饰规则
//void print(int);
//void print(double);
//int main()
//{
//	// error LNK2019: 无法解析的外部符号 "void __cdecl print(int)" (?print@@YAXH@Z)，函数 main 中引用了该符号
//	print(42);
//	//  error LNK2019: 无法解析的外部符号 "void __cdecl print(double)" (?print@@YAXN@Z)，函数 main 中引用了该符号
//	print(2.1);
//	return 0;
//}

//
//// 引用&
//using namespace std;
//int main()
//{
//	int a = 1;
//	// 引用在定义时必须初始化  error C2530: “nq”: 必须初始化引用
//	//int& nq;
//	// 一个变量可以有多个引用
//	int& na = a;
//	int& nb = a;
//	int& nc = na;
//
//	int num = 20;
//	// 赋值
//	na = num;
//
//	// 一旦确认了一个引用实体后，就不能再引用其他实体
//	int b = 2;
//	int& np = b;
//	np = na; // 这里是赋值，而不是改变引用指向
//	
//	return 0;
//}

// const修饰引用
using namespace std;
int main()
{
	const int a = 10;
	// 不可以 a只读 ra可读可写 权限放大
	// int& ra = a;

	// 可以 a和pa都是只读 权限平移
	const int& pa = a;

	// 可以 b可读可写 rb只读 权限缩小
	int b = 10;
	const int& rb = b;

}