#include "Date.h"

// 获取月份的天数
int Date::GetMonthDay(int year, int month)
{
	static int GetMonthDayArr[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
	{
		return 29;
	}
	else
	{
		return GetMonthDayArr[month];
	}
}

// 判断日期合法性
bool Date::CheckDate()
{
	if (_day < 1 || _day > GetMonthDay(_year, _month)
		|| _month < 1 || _month >12)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// 构造函数
Date::Date(int year, int month, int day)
	:_year(year)
	, _month(month)
	, _day(day)
{
	if (!CheckDate())
	{
		cout << "日期非法" << endl;
	}
}
// 日期比大小
bool Date::operator>(const Date& d) const
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

bool Date::operator>=(const Date& d) const
{
	return *this > d || *this == d;
}

bool Date::operator<(const Date& d) const
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d) const
{
	return !(*this > d);
}

bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

// 日期加减运算
Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month > 12)
		{
			_month = 1;
			_year++;
		}
	}
	return *this;
}

Date  Date::operator+(int day) const
{
	Date tmp = *this;
	tmp += day;
	return tmp;
}

Date  Date::operator-(int day) const
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

int  Date::operator-(const Date& d)
{
	Date max = *this;
	Date min = d;
	int flag = 1;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}

	int num = 0;
	while (min != max)
	{
		++min;
		++num;
	}

	return flag * num;
}
Date& Date::operator-=(int day)
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
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

Date& Date::operator++()
{
	*this += 1;
	return *this;
}
Date  Date::operator++(int) const
{
	Date tmp = *this;
	++tmp;
	return tmp;
}
Date  Date::operator--(int) const
{
	Date tmp = *this;
	--tmp;
	return tmp;
}
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}


ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}
istream& operator>>(istream& in, Date& d)
{
	cout << "请依次输⼊年⽉⽇:>";
	in >> d._year >> d._month >> d._day;
	if (!d.CheckDate())
	{
		cout << "日期非法！" << endl;
	}
	return in;
}


// 测试比较运算符
void TestCompare()
{
	cout << "=== 测试比较运算符 ===" << endl;
	Date d1(2025, 8, 12);
	Date d2(2025, 8, 1);
	Date d3(2024, 8, 12);
	Date d4(2025, 9, 12);
	Date d5(2025, 8, 12);  // 与d1相同

	cout << "d1(2025-8-12) > d2(2025-8-1): " << (d1 > d2) << " (预期1)" << endl;
	cout << "d1 > d3(2024-8-12): " << (d1 > d3) << " (预期1)" << endl;
	cout << "d1 > d4(2025-9-12): " << (d1 > d4) << " (预期0)" << endl;
	cout << "d1 >= d5: " << (d1 >= d5) << " (预期1)" << endl;
	cout << "d1 < d2: " << (d1 < d2) << " (预期0)" << endl;
	cout << "d1 <= d4: " << (d1 <= d4) << " (预期1)" << endl;
	cout << "d1 == d5: " << (d1 == d5) << " (预期1)" << endl;
	cout << "d1 != d2: " << (d1 != d2) << " (预期1)" << endl << endl;
}

// 测试日期加减天数（含月底/年底边界）
void TestAddSubDay()
{
	cout << "=== 测试日期加减天数 ===" << endl;
	// 测试月底加天（非闰年2月）
	Date d1(2023, 2, 28);
	d1 += 1;
	cout << "2023-2-28 +1天: " << d1 << " (预期2023-3-1)" << endl;

	// 测试闰年2月加天
	Date d2(2024, 2, 28);
	d2 += 2;
	cout << "2024-2-28 +2天: " << d2 << " (预期2024-3-1)" << endl;

	// 测试年底加天
	Date d3(2025, 12, 31);
	Date d3_plus = d3 + 1;
	cout << "2025-12-31 +1天: " << d3_plus << " (预期2026-1-1)" << endl;

	// 测试月初减天
	Date d4(2025, 3, 1);
	d4 -= 1;
	cout << "2025-3-1 -1天: " << d4 << " (预期2025-2-28)" << endl;

}

// 测试自增自减
void TestIncDec()
{
	cout << "=== 测试自增自减 ===" << endl;
	Date d(2025, 8, 12);

	// 前置++
	++d;
	cout << "++d: " << d << " (预期2025-8-13)" << endl;

	// 后置++
	Date d_post = d++;
	cout << "d++后d_post: " << d_post << " (预期2025-8-13)，当前d: " << d << " (预期2025-8-14)" << endl;

	// 前置--
	--d;
	cout << "--d: " << d << " (预期2025-8-13)" << endl;

	// 后置--
	Date d_post_dec = d--;
	cout << "d--后d_post_dec: " << d_post_dec << " (预期2025-8-13)，当前d: " << d << " (预期2025-8-12)" << endl << endl;
}

// 测试两个日期相差的天数
void TestDateDiff()
{
	cout << "=== 测试日期差 ===" << endl;
	Date d1(2025, 8, 12);
	Date d2(2025, 8, 1);
	cout << "d1 - d2: " << (d1 - d2) << " 天 (预期11)" << endl;

	Date d3(2024, 12, 31);
	Date d4(2025, 1, 1);
	cout << "d4 - d3: " << (d4 - d3) << " 天 (预期1)" << endl;

	Date d5(2020, 2, 28);  // 闰年
	Date d6(2020, 3, 1);
	cout << "d6 - d5: " << (d6 - d5) << " 天 (预期2)" << endl;

	Date d7(2019, 1, 1);
	Date d8(2023, 1, 1);
	cout << "d8 - d7: " << (d8 - d7) << " 天 (预期1461，含2020闰年)" << endl << endl;
}

// 测试非法日期处理
void TestInvalidDate()
{
	cout << "=== 测试非法日期 ===" << endl;
	Date d1(2023, 2, 30);  // 2月无30日
	Date d2(2023, 13, 1);  // 月份13非法
	Date d3(2023, 5, 32);  // 5月无32日

	// 测试输入流
	Date d4;
	cin >> d4;  // 尝试输入 2023 2 30，应提示非法
	cout << endl;
}
