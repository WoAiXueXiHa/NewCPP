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

class Date
{
public:
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
// private:
	int _year;
	int _month;
	int _day;
};
bool operator>(const Date& d1, const Date& d2)
{
	if (d1._year > d2._year)
	{
		if (d1._month > d2._month)
		{
			if (d1._day > d2._day)
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}

int main()
{
	Date d1(2025, 7, 17);
	Date d2(2025, 7, 20);

	cout << (d1 > d2) << endl;

	return 0;

}