#include <iostream>
#include <stdbool.h>
#include <assert.h>
using namespace std;

class Date
{
public:
	friend ostream& operator<<(ostream& out, const Date& d);

	Date(int year = 1, int month = 1, int day = 1)
		: _year(year), _month(month), _day(day)
	{
		// 检查日期是否合法
		assert(month >= 1 && month <= 12);
		assert(day >= 1 && day <= GetMonthDay(year, month));
	}

	bool operator>(const Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month > d._month)
			{
				return true;
			}
			else if (_month == d._month)
			{
				return _day > d._day;
			}
		}
		
		return false;
	}

	bool operator>=(const Date& d)
	{
		return *this > d || *this == d;
	}

	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}

	bool operator<=(const Date& d)
	{
		return !(*this > d);
	}

	bool operator==(const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}


	int GetMonthDay(int year, int month)
	{
		assert(month > 0 && month < 13);
		static int GetMonthDayArr[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month == 2 && ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0) )
		{
			return 29;
		}
		else 
		{
			return GetMonthDayArr[month];
		}
	}

	Date& operator+=(int day)
	{
		if (day < 0)
		{
			return *this -= -day;
		}

		_day += day;
		while(_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			++_month;
			if (_month > 12)
			{
				_month = 1;
				++_year;
			}
		}

		return *this;
	}

	Date operator+(int day)
	{
		Date tmp = *this;
		tmp += day;
		return tmp;
	}

	Date& operator-=(int day)
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_month = 12;
				--_year;
			}
			_day += GetMonthDay(_year,_month);
		}

		return *this;
	}

	Date operator-(int day)
	{
		Date tmp = *this;
		tmp -= day;
		return tmp;
	}

	// 前置++，返回++后的值
	Date& operator++()
	{
		return *this += 1;
	}
	// 后置++，返回++前的值，C++规定，参数里有个int表示后置++
	Date operator++(int)
	{
		Date tmp = *this;
		*this += 1;

		return tmp;
	}

	Date& operator--()
	{
		return *this -= 1;
	}

	Date operator--(int) 
	{
		Date tmp = *this;
		*this -= 1;

		return tmp;
	}

	int operator-(const Date& d)
	{
		Date max = *this;
		Date min = d;
		int flag = 1;
		if (max < min)
		{
			max = d;
			min = *this;
		}

		int num = 0;
		while (min != max)
		{
			++min;
			++num;
		}

		return flag * num;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year = 1;
	int _month = 1;
	int _day = 1;
};

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}
void test1()
{
	Date d1(2025, 8, 11);
	Date d2(2025, 8, 1);

	cout << (d1 > d2) << endl;
	cout << (d1 >= d2) << endl;
	cout << (d1 < d2) << endl;
	cout << (d1 <= d2) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;

}

void test2()
{
	Date d1(2025, 8, 11);
	Date d2(2019, 8, 1);

	cout << (d1 - d2) << endl;
	cout << (d1 += 500);
	cout << (d1 -= 500);
	cout << (d1 -= -500);
	cout << (d1 += -500);
}

int main()
{
	test2();

	return 0;
}