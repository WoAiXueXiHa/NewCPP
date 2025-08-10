#include <iostream>
#include <stdbool.h>
#include <assert.h>
using namespace std;

class Date
{
public:
	bool operator==(const Date& d)
	{
		if (_year == d._year && _month == d._month && _day == d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	bool operator>(const Date& d)
	{
		if (_year > d._year)
		{
			if (_month > d._month)
			{
				if (_day > d._day)
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

	bool operator>=(const Date& d)
	{
		return (*this > d || *this == d);
	}
	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}

	bool operator<=(const Date& d)
	{
		return (*this < d || *this == d);
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
		_day += day;
		if (_day > GetMonthDay(_year, _month))
		{
			_day -= 
		}
	}
	Date& operator-=(int day);


private:
	size_t _year = 1;
	size_t _month = 1;
	size_t _day = 1;
};

int main()
{
	return 0;
}