#include <iostream>
#include <assert.h>
#include <stdbool.h>
using namespace std;
//
//// 拷贝构造函数
//// 构造函数的重载，第一个参数必须是类类型对象的引用
//// 用于同类对象的拷贝初始化
//
//class Date
//{
//public:
//	Date()
//	{
//		_year = 1;
//		_month = 1;
//		_day = 1;
//	}
//
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//
//	//// 不可以写成传值传参 会引发无穷递归调用
//	//// C2652: “Date”: 非法的复制构造函数: 第一个参数不应是“Date”
//	//Date(Date d)
//	//{
//	//	_year = d._year;
//	//	_month = d._month;
//	//	_day = d._day;
//	//}
//
//	//Date(Date& d)
//	//{
//	//	cout << "call Date(Date& d)" << endl;
//	//	// 如果不小心写反了会发生什么？
//	//	d._year = _year;
//	//	d._month = _month;
//	//	d._day = _day;
//	//}
//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//
//private:
//	size_t _year;
//	size_t _month;
//	size_t _day;
//};
//
//int main()
//{
//	Date d1;
//	Date d2 = d1;
//	Date d3(d1);
//
//	d1.Print();
//	d2.Print();
//	d3.Print();
//
//	return 0;
//}

//// 自定义类型对象进行拷贝行为必须调用拷贝构造
//// 自定定义类型传值传参和传值返回都会调用拷贝构造完成
//class Date
//{
//public:
//	Date(size_t year, size_t month, size_t day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	Date(const Date& d)
//	{
//		cout << "调用 Date(const Date& d)" << endl;
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	size_t _year;
//	size_t _month;
//	size_t _day;
//};
//void func(Date d)
//{
//	d.Print();
//}
//
//int main()
//{
//	Date d1(2025, 7, 9);
//	func(d1);
//	return 0;
//}

// 如果不显式写拷贝构造，编译器会默认生成拷贝构造，
// 自动⽣成的拷贝构造对内置类型成员变量会完成值拷贝/浅拷贝(⼀个字节⼀个字节的拷贝)，
// 对自定义类型成员变量会调用它的拷贝构造
//class Stack
//{
//public:
//	Stack(size_t n = 4)
//	{
//		// cout << "Stack(size_t n = 4) 构造" << endl;
//		_arr = (int*)malloc(sizeof(int) * n);
//		if (_arr == nullptr)
//		{
//			perror("malloc err!");
//			return;
//		}
//
//		_capacity = n;
//		_top = 0;
//	}
//
//	// 深拷贝
//	// Stack st2 = st1;
//	Stack(const Stack& st)
//	{
//		_arr = (int*)malloc(sizeof(int) * st._capacity);
//		if (_arr == nullptr)
//		{
//			perror("malloc err!");
//			return;
//		}
//
//		memcpy(_arr, st._arr, sizeof(int)* st._capacity);
//
//		_capacity = st._capacity;
//		_top = st._top;
//	}
//
//	void Push(int data)
//	{
//		_arr[_top++] = data;
//	}
//
//	~Stack()
//	{
//		// cout << "~Stack() 析构" << endl;
//		assert(_arr);
//		free(_arr);
//		_arr = nullptr;
//		_capacity = _top = 0;
//	}
//
//private:
//	int* _arr;
//	int _capacity;
//	int _top;
//};
//
//int main()
//{
//	Stack st1;
//	st1.Push(1);
//	st1.Push(1);
//	st1.Push(1);
//
//	Stack st2 = st1;
//
//	return 0;
//}


// 运算符重载
// 参数类型必须要有一个是类类型
// “operator -”必须至少有一个类类型的形参
//void operator-(int a, int b){}

// 对于自定义类型，使用操作符会调用该操作符具体的指令
//int main()
//{
//	int num1 = 10;
//	int num2 = 30;
//	int mul = num1 * num2;
//	int plus = num1 + num2;
//
//	return 0;
//}


// 自定义类型呢？
//class Date
//{
//public:
//	Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	~Date()
//	{
//		_year = -1;
//		_month = -1;
//		_day = -1;
//	}
//	bool operator>(const Date& d2)
//	{
//		if (this->_year > d2._year)
//		{
//			if (this->_month > d2._month)
//			{
//				if (this->_day > d2._day)
//				{
//					return true;
//				}
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1(2025, 7, 17);
//	Date d2(2025, 7, 20);
//	// 转换成调用 operator>(d1, d2)
//	cout << (d1 > d2) << endl;
//	// 可以显式调用
//	cout << d1.operator>(d2) << endl;
//
//	return 0;
//}

//// .*不能重载
//class A
//{
//public:
//	void func()
//	{
//		cout << "A::func()" << endl;
//	}
//};
//typedef void(A::* PF)(); //成员函数指针类型
//
//int main()
//{
//	// C++规定成员函数要加&才能取到函数指针
//	PF pf = &A::func;
//
//	A obj;//定义ob类对象temp
//
//	// 对象调⽤成员函数指针时，使⽤.*运算符
//	(obj.*pf)();
//
//	return 0;
//}

//int main()
//{
//	int i, j, k;
//
//	i = j = k = 1;
//
//	return 0;
//}

class Date
{
public:
	// 构造
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// 拷贝构造
	Date(const Date& d)
	{
		cout << "Date(const Date & d)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	// 赋值运算符重载
	Date& operator=(const Date& d)
	{
		// 防止自己给自己赋值
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		// 返回值是Date类
		return *this;
	}
	// 析构 
	~Date()
	{
		cout << "~Date()" << endl;
		_year = _month = _day = -1;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

//int main()
//{
//	Date d1(2025, 7, 20);
//	Date d2(2024, 7, 28);
//	// 拷贝构造
//	Date d3 = d1;
//	// 赋值运算符重载
//	// 缺少返回值 二元“=”: 没有找到接受“void”类型的右操作数的运算符(或没有可接受的转换)
//	d1 = d2 = d3;
//
//	d1.Print();
//	d2.Print();
//	d3.Print();
//}

//// 传值返回
//Date func()
//{
//	Date d1;
//	Date d2;
//
//	if (time(0) % 2)
//	{
//		return d1;  // 编译器无法预测 取消优化
//	}
//	else
//	{
//		return d2;
//	}
//}
//
//int func1()
//{
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	return a + b + c;
//}
//
//int main()
//{
//	Date ref = func();
//	ref.Print();
//	return 0;
//}

//// 传引用返回
//Date& func()
//{
//	Date d1;
//	Date d2;
//
//	if (time(0) % 2)
//	{
//		return d1;  // 编译器无法预测 取消优化
//	}
//	else
//	{
//		return d2;
//	}
//}
//
//int func1()
//{
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	return a + b + c;
//}
//
//int main()
//{
//	Date& ref = func();
//	ref.Print();
//	return 0;
//}

// 