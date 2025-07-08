#include <iostream>
#include <assert.h>

using namespace std;

// 拷贝构造函数
// 构造函数的重载，第一个参数必须是类类型对象的引用
// 用于同类对象的拷贝初始化

class Date
{
public:
	Date()
	{
		_year = 1;
		_month = 1;
		_day = 1;
	}

	Date(Date& d)
	{
		cout << "call Date(Date& d)" << endl;
		// 如果不小心写反了会发生什么？
		d._year = _year;
		d._month = _month;
		d._day = _day;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	size_t _year;
	size_t _month;
	size_t _day;
};

int main()
{
	Date d1;
	Date d2 = d1;
	Date d3(d1);

	d1.Print();
	d2.Print();
	d3.Print();

	return 0;
}

