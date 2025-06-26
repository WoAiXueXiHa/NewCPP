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

// 输入和输出
using namespace std;
int main()
{
	int x, y;
	char ch;
	cin >> x >> y >> ch;
	cout << x << " " << y << " " << ch;
}