#include <iostream>
using namespace std;
//int globalVar = 1;
//
//static int staticGlobalVar = 1;
//void Test()
//{
//	static int staticVar = 1;
//	
//	int localVar = 1;
//	int num1[10] =			{ 1, 2, 3, 4 };
//	char char2[] =			"abcd";
//	
//	const char* pChar3 =	"abcd";
//	
//	int* ptr1 =				(int*)malloc(sizeof(int) * 4);
//	int* ptr2 =				(int*)calloc(4, sizeof(int));
//	int* ptr3 =				(int*)realloc(ptr2, sizeof(int) * 4);
//	
//	free(ptr1);
//	free(ptr3);
//}

//void Test()
//{
//	// 动态申请一个int类型空间
//	int* ptr1 = new int;
//
//	// 动态申请一个int类型空间，并初始化为1
//	int* ptr2 = new int(1);
//
//	// 动态申请10个float类型的空间
//	float* ptr3 = new float[10];
//
//	// 动态申请3个float类型的空间,并分别初始化为1.1，1.2，1.3
//	float* ptr4 = new float[10] {1.1, 1.2, 1.3};
//
//	delete ptr1;
//	delete ptr2;
//	delete[] ptr3;
//	delete[] ptr4;
//}

//class A
//{
//public:
//	A(int a1 = 1, int a2 = 2)
//		:_a1(a1)
//		, _a2(a2)
//	{
//		cout << "A(int a1, int a2)" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//
//private:
//	int _a1;
//	int _a2;
//};
//
//int main()
//{
//	// 与C的malloc、realloc、calloc、free不同 new和delete对于自定义类型除了开辟空间还会调用构造和析构
//	A* ptr1 = (A*)malloc(sizeof(A));
//	A* ptr2 = new A{1,2};
//	free(ptr1);
//	delete ptr2;
//
//	// 内置类型几乎一样
//	int* ptr3 = (int*)malloc(sizeof(int));
//	int* ptr4 = new int;
//	free(ptr3);
//	delete ptr4;
//
//	A* ptr5 = (A*)malloc(sizeof(A) * 10);
//	A* ptr6 = new A[10];
//
//	free(ptr5);
//	delete[] ptr6;
//}

//// 演示malloc和new的区别
//int main()
//{
//    // 演示new分配失败时抛异常
//    try {
//        // 尝试分配一个极大的内存块，大概率会失败
//        size_t largeSize = 1024ULL * 1024 * 1024 * 1024; // 1TB
//        int* ptr1 = new int[largeSize];
//
//        // 如果成功分配（几乎不可能），释放内存
//        delete[] ptr1;
//        std::cout << "new 分配成功" << std::endl;
//    }
//    catch (const std::bad_alloc& e) {
//        // 捕获new分配失败的异常
//        std::cout << "new 分配失败: " << e.what() << std::endl;
//    }  
//
//    size_t largeSize = 1024ULL * 1024 * 1024 * 1024; 
//    int* ptr2 = (int*)malloc(sizeof(largeSize));
//    if (ptr2 == nullptr)
//    {
//        cout << "malloc 失败" << endl;
//    }
//    else
//    {
//        free(ptr2);
//        ptr2 = nullptr;
//        cout << "malloc 成功" << endl;
//    }
//
//    return 0;
//};

//// new delete原理
//class obj
//{
//public:
//	obj(int o)
//		:_o(o)
//	{
//		cout << "调用obj(int o)" << endl;
//	}
//	~obj()
//	{
//		cout << "调用~obj()" << endl;
//	}
//private:
//	int _o;
//};
//
//int main()
//{
//	// new的原理：调用operator new函数申请空间，执行构造函数完成对象的构造
//	// 00007FF75AE32651  call        operator new (07FF75AE3104Bh) 
//	obj* ptr = new obj(1);
//  // delete的原理：执行析构函数，完成对象的析构，调用operator delete完成空间清理
//	// 00007FF75AE326C6  call        obj::`scalar deleting destructor' (07FF75AE31280h)  
//	delete ptr;
//}

// new[] delete[]原理
class obj
{
public:
	obj(int o = 1)
		:_o(o)
	{
		cout << "obj(int o)" << endl;
	}
	~obj()
	{
		cout << "~obj()"<<endl;
	}
private:
	int _o;
};

int main()
{
	// new[]的原理：调用operator new[]申请3个空间，在申请的空间上执行构造函数
	// 00007FF630742771  call        operator new[] (07FF630741212h)
	obj* ptr = new obj[3];// 16 要多开一个4字节空间存对象个数，方便知道调用几次析构函数，如果没有显式写析构，则为12
	// delete[]的原理： 执行三次析构函数，完成函数的析构，调用operator delete[]释放三个空间
	// 00007FF630742832  call        obj::`vector deleting destructor' (07FF63074105Ah)  
	delete[] ptr;

	return 0;
}