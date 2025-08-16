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
//	// ��̬����һ��int���Ϳռ�
//	int* ptr1 = new int;
//
//	// ��̬����һ��int���Ϳռ䣬����ʼ��Ϊ1
//	int* ptr2 = new int(1);
//
//	// ��̬����10��float���͵Ŀռ�
//	float* ptr3 = new float[10];
//
//	// ��̬����3��float���͵Ŀռ�,���ֱ��ʼ��Ϊ1.1��1.2��1.3
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
//	// ��C��malloc��realloc��calloc��free��ͬ new��delete�����Զ������ͳ��˿��ٿռ仹����ù��������
//	A* ptr1 = (A*)malloc(sizeof(A));
//	A* ptr2 = new A{1,2};
//	free(ptr1);
//	delete ptr2;
//
//	// �������ͼ���һ��
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

//// ��ʾmalloc��new������
//int main()
//{
//    // ��ʾnew����ʧ��ʱ���쳣
//    try {
//        // ���Է���һ��������ڴ�飬����ʻ�ʧ��
//        size_t largeSize = 1024ULL * 1024 * 1024 * 1024; // 1TB
//        int* ptr1 = new int[largeSize];
//
//        // ����ɹ����䣨���������ܣ����ͷ��ڴ�
//        delete[] ptr1;
//        std::cout << "new ����ɹ�" << std::endl;
//    }
//    catch (const std::bad_alloc& e) {
//        // ����new����ʧ�ܵ��쳣
//        std::cout << "new ����ʧ��: " << e.what() << std::endl;
//    }  
//
//    size_t largeSize = 1024ULL * 1024 * 1024 * 1024; 
//    int* ptr2 = (int*)malloc(sizeof(largeSize));
//    if (ptr2 == nullptr)
//    {
//        cout << "malloc ʧ��" << endl;
//    }
//    else
//    {
//        free(ptr2);
//        ptr2 = nullptr;
//        cout << "malloc �ɹ�" << endl;
//    }
//
//    return 0;
//};

//// new deleteԭ��
//class obj
//{
//public:
//	obj(int o)
//		:_o(o)
//	{
//		cout << "����obj(int o)" << endl;
//	}
//	~obj()
//	{
//		cout << "����~obj()" << endl;
//	}
//private:
//	int _o;
//};
//
//int main()
//{
//	// new��ԭ������operator new��������ռ䣬ִ�й��캯����ɶ���Ĺ���
//	// 00007FF75AE32651  call        operator new (07FF75AE3104Bh) 
//	obj* ptr = new obj(1);
//  // delete��ԭ��ִ��������������ɶ��������������operator delete��ɿռ�����
//	// 00007FF75AE326C6  call        obj::`scalar deleting destructor' (07FF75AE31280h)  
//	delete ptr;
//}

// new[] delete[]ԭ��
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
	// new[]��ԭ������operator new[]����3���ռ䣬������Ŀռ���ִ�й��캯��
	// 00007FF630742771  call        operator new[] (07FF630741212h)
	obj* ptr = new obj[3];// 16 Ҫ�࿪һ��4�ֽڿռ��������������֪�����ü����������������û����ʽд��������Ϊ12
	// delete[]��ԭ�� ִ������������������ɺ���������������operator delete[]�ͷ������ռ�
	// 00007FF630742832  call        obj::`vector deleting destructor' (07FF63074105Ah)  
	delete[] ptr;

	return 0;
}