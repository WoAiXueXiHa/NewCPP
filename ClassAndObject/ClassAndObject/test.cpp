#include <iostream>
#include <assert.h>
using namespace std;

//// 定义一个类
//class stuInfo
//{
//public:
//	// 将实现接口公开
//	// 成员函数
//private:
//	// 将信息数据隐藏
//	unsigned int _age;
//	unsigned int _numArr[8];
//	char* _nameArr[10];
//};
//

//// 实现一个简单的栈
//class Stack
//{
//public:
//	// 成员函数
//	void Init(int n = 4)
//	{
//		_valArr = (int*)malloc(sizeof(int) * n);
//		if (_valArr == nullptr)
//		{
//			perror("malloc err!");
//			return;
//		}
//		_top = 0;
//		_capacity = n;
//	}
//
//	void push(int inPut = 1)
//	{
//		_valArr[_top++] = inPut;
//	}
//
//	size_t top()
//	{
//		assert(_top > 0);
//		return _valArr[_top - 1];
//	}
//
//	void Destroy()
//	{
//		assert(_valArr);
//		free(_valArr);
//		_valArr = nullptr;
//		_capacity = _top = 0;
//	}
//
//private:
//	size_t _top;
//	size_t _capacity;
//	int* _valArr;
//};
//
//int main()
//{
//	Stack st;
//	st.Init(12);
//
//	st.push(0);
//	st.push(1);
//	st.push(2);
//	st.push(3);
//
//	st.top();
//
//	st.Destroy();
//
//	return 0;
//}


//class Stack
//{
//public:
//	// 成员函数
//	void Init(int n = 4);
//	void push(int inPut = 1);
//	size_t top();
//	void Destroy();
//private:
//	size_t _top;
//	size_t _capacity;
//	int* _valArr;
//};
//// 声明和定义分离
//	// 缺省参数声明给
//	void Stack::Init(int n)
//	{
//		_valArr = (int*)malloc(sizeof(int) * n);
//		if (_valArr == nullptr)
//		{
//			perror("malloc err!");
//			return;
//		}
//		_top = 0;
//		_capacity = n;
//	}
//
//	void Stack::push(int inPut)
//	{
//		_valArr[_top++] = inPut;
//	}
//
//	size_t Stack::top()
//	{
//		assert(_top > 0);
//		return _valArr[_top - 1];
//	}
//
//	void Stack::Destroy()
//	{
//		assert(_valArr);
//		free(_valArr);
//		_valArr = nullptr;
//		_capacity = _top = 0;
//	}
//int main()
//{
//	Stack st;
//	st.Init(12);
//
//	st.push(0);
//	st.push(1);
//	st.push(2);
//	st.push(3);
//
//	st.top();
//
//	st.Destroy();
//
//	return 0;
//}
//
//

//class Date
//{
//public:
//	void Init(size_t year, size_t month, size_t day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << "/" << _month << "/" << _day << endl;
//	}
//private:
//	// 声明
//	size_t _year;
//	size_t _month;
//	size_t _day;
//};
//
//int main()
//{
//	// 实例化
//	Date d1;
//	d1.Init(2025, 7, 3);
//	d1.Print();
//
//	return 0;	 
//}

//class Person
//{
//public:
//	void SetPersonInfo(){}
//	void PrintPersonInfo(){}
//
//private:
//	char* _name;
//	bool _gender;
//	size_t _age;
//};
//int main()
//{
//	Person p1;
//	p1.SetPersonInfo();
//	Person p2;
//	p2.SetPersonInfo();
//	return 0;
//}

//
//#include<iostream>
//using namespace std;
//// 计算⼀下A/B/C实例化的对象是多⼤？
//// 8
//class A
//{
//public:
//	void Print()
//	{
//		cout << _ch << endl;
//	}
//private:
//	char _ch;
//	int _i;
//};
//// 1
//class B
//{
//public:
//	void Print()
//	{
//		//...
//	}
//};
//// 1
//class C
//{
//};
//int main()
//{
//	A a;
//	B b;
//	C c;
//	cout << sizeof(a) << endl;
//	cout << sizeof(b) << endl;
//	cout << sizeof(c) << endl;
//	return 0;
//}

// 
//using namespace std;
//class Date
//{
//public:
//	// void Init(Date* const this, size_t year, size_t month, size_t day)
//	void Init(size_t year, size_t month, size_t day)
//	{
//		// this->_year = year
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	// void Print(Date* const this)
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	size_t _year;
//	size_t _month;
//	size_t _day;
//};
//
//int main()
//{
//	Date d1;
//	d1.Init(2025, 7, 5);
//	Date d2;
//	d2.Init(2008, 1, 1);
//	d1.Print();
//	d2.Print();
//}

//#include<iostream>
//using namespace std;
//class A
//{
//public:
//	void Print()
//	{
//		cout << "A::Print()" << endl;
//	}
//private:
//	int _a;
//};
//
//int main()
//{
//	// 正常运行，并没有解引用空指针
//	A* p = nullptr;
//	p->Print();
//	return 0;
//}
//#include<iostream>
//using namespace std;
//class A
//{
//public:
//	void Print()
//	{
//		cout << "A::Print()" << endl;
//		// p->_a 解引用了空指针 运行奔溃
//		cout << _a << endl;
//	}
//private:
//	int _a;
//};
//int main()
//{
//	A* p = nullptr;
//	p->Print();
//	return 0;
//}

//// 构造函数
//// 1. 函数名和类名同名 2. 可以重载 3. 没有返回值 4. 用户不写编译器会默认生成无参的构造函数
//class Date
//{
//public:
//	// 无参构造
//	Date()
//	{
//		_year = 1;
//		_month = 1;
//		_day = 1;
//	}
//
//	// 带参数构造
//	Date(size_t year, size_t month, size_t day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	//// 全缺省构造
//	//Date(size_t year = 1, size_t month = 1, size_t day = 1)
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//	//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	size_t _year;
//	size_t _month;
//	size_t _day;
//};
//
//int main()
//{
//	// 调用带参数的构造
//	Date d1(2025,7,5);
//	d1.Print();
//
//	//// 无参构造和全缺省构造会产生调用歧义
//	//Date d2;
//	//d2.Print();
//
//	// 无参的不能这么写 会和函数声明搞混 eg: void func
//	// 这是函数声明还是函数定义呢？
//	/*Date d2();
//	d2.Print();*/
//
//	//// 如果注释掉无参的构造和全缺省构造，会报错
//	//// C2512 没有合适的默认构造函数可用
//	//Date d2;
//	//d2.Print();
//
//	// 调用无参的构造函数
//	Date d3;
//	d3.Print();
//
//	return 0;
//}
//using namespace std;
//class Time
//{
//public:
//	/*Time()
//	{
//		_hour = 1;
//		_minute = 1;
//		_second = 1;
//	}*/
//
//private:
//	// C++11 在声明时给缺省值
//	size_t _hour = 1;
//	size_t _minute = 1;
//	size_t _second = 1;
//};
//
//class Date
//{
//public:
//	// 不写构造函数 编译器会自动生成默认构造函数
//	// 对于内置类型 编译器是否处理没有明确要求
//	// 对于自定义类型 调用该类型的默认构造函数
//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	// C++11 在声明时给缺省值
//	size_t _year = 1;	
//	size_t _month = 1;
//	size_t _day = 1;
//	Time _t;
//};
//
//int main()
//{
//	// 此时 Time类和Date类只有编译器默认生成的构造函数
//	Date d1;
//	d1.Print();
//	
//	return 0;
//}

// 析构函数
// 1. 函数名和类名同名，函数名前加'~' 2. 不能重载 3. 用户不显式定义，编译器会默认生成析构函数
class tmp
{
public:
	~tmp()
	{
		cout << "~tmp() 析构" << endl;
	}
private:
	int _num;
};
class Stack
{
public:
	Stack(size_t n = 4)
	{
		cout << "Stack(size_t n = 4) 构造" << endl;
		_arr = (int*)malloc(sizeof(int) * n);
		if (_arr == nullptr)
		{
			perror("malloc err!");
			return;
		}

		_capacity = n;
		_top = 0;
	}

	~Stack()
	{
		cout << "~Stack() 析构" << endl;
		assert(_arr);
		free(_arr);
		_arr = nullptr;
		_capacity = _top = 0;
	}

private:
	int* _arr;
	int _capacity;
	int _top;
	/*tmp _t;*/

};

int main()
{
	Stack st1;

	return 0;
}
