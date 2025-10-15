#pragma once
#include <iostream>
#include <cassert>
#include <array>

namespace Vect {
	class Date {
	private:
		int _year;
		int _month;
		int _day;
	public:

		friend std::ostream& operator<<(std::ostream& os, const Vect::Date& d);
		friend std::istream& operator>>(std::istream& is, Vect::Date& d);


		static inline bool isValid(int year, int month, int day) {
			if (month < 1 || month > 12) return false;
			int monthDay = getMonthDay(year, month);
			return day >= 1 && day <= monthDay;
		}

		static inline bool isLeapYear(int year) {
			return (year % 400 == 0) 
				|| (year % 4 == 0 && year % 100 != 0);
		}

		static constexpr int getMonthDay(int year, int month) {
			std::array<int, 13> dayArray = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
			assert(1 <= month && month <= 12 && "请输入正确的月份");
			if (month == 2) return isLeapYear(year) ? 29 : 28;
			return dayArray[month];
		}


		// 构造
		Date(int year = 2025, int month = 10, int day = 1)
			:_year(year)
			,_month(month)
			,_day(day)
		{
			assert(isValid(_year, _month, _day) && "日期非法");
		}

		// 拷贝构造
		Date(const Date& other)
			:_year(other._year)
			,_month(other._month)
			,_day(other._day)
		{ }

		// 赋值重载
		Date& operator=(const Date& copyFrom) {
			if (this != &copyFrom) {
				_year = copyFrom._year;
				_month = copyFrom._month;
				_day = copyFrom._day;
			}
			return *this;
		}

		// 运算符重载
		// 确定两个逻辑 剩下都可以复用
		bool operator>(const Date& compObj) const {
			if (_year != compObj._year) return _year > compObj._year;
			if (_month != compObj._month) return _month > compObj._month;
			return _day > compObj._day;  // 覆盖年、月相等的情况
		}


		bool operator==(const Date& compObj) const {
			return _year == compObj._year
				&& _month == compObj._month
				&& _day == compObj._day;
		}

		bool operator>=(const Date& compObj) const {
			return (*this > compObj)
				|| (*this == compObj);
		}

		bool operator<(const Date& compObj) const { return !(*this >= compObj); }

		bool operator<=(const Date& compObj) const { return !(*this > compObj); }

		bool operator!=(const Date& compObj) const { return !(*this == compObj); }

		// 前置++ --
		Date& operator++() {
			++_day;
			// 需要考略加到下一个月否
			if (_day > getMonthDay(_year, _month)) {
				++_month;
				if (_month > 12) {
					_month = 1;
					++_year;
				}

				_day = 1;
			}
			return *this;
		}

		Date& operator--() {
			--_day;
			// 需要考虑减到下一个月否
			if (_day == 0) {
				--_month;
				if (_month == 0) {
					_month = 12;
					--_year;
				}
				_day = getMonthDay(_year, _month);
			}

			return *this;
		}
		
		// 后置++ --
		Date operator++(int) {
			Date tmp = *this;
			++(*this);
			return tmp;
		}

		Date operator--(int) {
			Date tmp = *this;
			--(*this);
			return tmp;
		}

		// 日期加减天数 d1 += 12
		Date& operator+=(int day) {
			assert(day > 0 && "请输入正数，此接口为日期加天数");
			while (day > 0) {
				++(*this);
				--day;
			}
			return *this;
		}
		Date& operator-=(int day) {
			assert(day > 0 && "请输入正数，此接口为日期减天数");
			while (day > 0) {
				--(*this);
				--day;
			}
			return *this;
		}

		// 不修改自己
		Date operator+(int day) const {  
			Date tmp = *this;
			tmp += day;                  
			return tmp;
		}
		Date operator-(int day) const {
			Date tmp = *this;
			tmp -= day;
			return tmp;
		}


		// 日期减日期得到天数差 O(n)
		int operator-(const Date& other) const {
			int count = 0;
			// 不修改形参
			Date tmp = other;

			// 相等：差为 0
			if (*this == tmp) return 0;

			// *this > other
			if (*this > tmp) {
				while (tmp != *this) {
					++tmp;      
					++count;    // 正向累加步数
				}
				return count; 
			}

			// *this < other
			while (tmp != *this) {
				--tmp;          
				++count;        // 正向累加步数
			}
			return -count;
		}

	};
	// 重载输入输出
	std::istream& operator>>(std::istream& in, Vect::Date& date) {
		std::cout << "请按照格式输入日期：year-month-day:  >" << std::endl;
		int  year, month, day;
		char sep1, sep2;
		if (in >> year >> sep1 >> month >> sep2 >> day && sep1 == '-' && sep2 == '-') {
			if (Vect::Date::isValid(year, month, day)) {
				date._year = year;
				date._month = month;
				date._day = day;
			}
		}
		return in;
	}

	std::ostream& operator<<(std::ostream& os, const Vect::Date& d) {
		return os << d._year << "-" 
			<< d._month << "-" 
			<< d._day;
	}


	//void dateCompare() {
	//	Date d1(2025, 10, 15);
	//	Date d2(2027, 6, 20);

	//	std::cout << "============ 测试比较 ============" << std::endl;
	//	std::cout << "2025-10-15是否等于2027-6-20： " << (d1 == d2) << std::endl;
	//	std::cout << "2025-10-15是否大于2027-6-20： " << (d1 > d2) << std::endl;
	//	std::cout << "2025-10-15是否大于等于2027-6-20： " << (d1 >= d2) << std::endl;
	//	std::cout << "2025-10-15是否小于2027-6-20： " << (d1 < d2) << std::endl;
	//	std::cout << "2025-10-15是否小于等于2027-6-20： " << (d1 <= d2) << std::endl;
	//}

	//void datePlusAndSub() {
	//	Date testDate1(2025, 1, 1);
	//	std::cout << "============ 测试自增自减 ============" << std::endl;
	//	std::cout << "原日期： " << testDate1 << std::endl;
	//	std::cout << "前置++后日期： " << ++testDate1 << std::endl;
	//	testDate1 = { 2025,1,1 };
	//	std::cout << "后置++后日期： " << testDate1++ << std::endl;
	//	testDate1 = { 2025,1,1 };
	//	std::cout << "后置--后日期： " << testDate1-- << std::endl;
	//	testDate1 = { 2025,1,1 };
	//	std::cout << "前置--后日期： " << --testDate1 << std::endl;

	//	std::cout << "========================================" << std::endl;
	//	Date testDate2(2024, 3, 1);
	//	std::cout << "原日期： " << testDate2 << std::endl;
	//	std::cout << "前置++后日期： " << ++testDate2 << std::endl;
	//	testDate2 = { 2024, 3, 1 };
	//	std::cout << "后置++后日期： " << testDate2++ << std::endl;
	//	testDate2 = { 2024, 3, 1 };
	//	std::cout << "前置--后日期： " << --testDate2 << std::endl;
	//	testDate2 = { 2024, 3, 1 };
	//	std::cout << "后置--后日期： " << testDate2-- << std::endl;
	//}

	//void datePlusAndSubDays() {
	//	Date d1(2025, 10, 15);
	//	std::cout << (d1 += 100) <<std::endl;
	//	std::cout << (d1 -= 1000) << std::endl;
	//	Date d2(2025, 10, 14);
	//	std::cout << (d2 + 100) << std::endl;
	//	d2 = { 2011,10,30 };
	//	Date d3 = { 2028,10,14 };
	//	std::cout << (d2 - d3) << std::endl;
	//}

	void test() {
		std::cout << "===== 1) 比较运算测试 =====\n";
		{
			Date a(2025, 10, 15);
			Date b(2027, 6, 20);
			std::cout << "a=" << a << "  b=" << b << "\n";
			std::cout << "a==b: " << (a == b) << "\n";
			std::cout << "a!=b: " << (a != b) << "\n";
			std::cout << "a>b : " << (a > b) << "\n";
			std::cout << "a>=b: " << (a >= b) << "\n";
			std::cout << "a<b : " << (a < b) << "\n";
			std::cout << "a<=b: " << (a <= b) << "\n\n";
		}

		std::cout << "===== 2) 前置/后置 自增自减 测试 =====\n";
		{
			Date d(2025, 1, 1);
			std::cout << "原始: " << d << "\n";
			std::cout << "++d : " << ++d << "\n";   // 前置++
			d = Date(2025, 1, 1);
			std::cout << "d++ : " << d++ << "  (打印的是旧值)\n";
			std::cout << "现在: " << d << "\n";
			d = Date(2025, 1, 1);
			std::cout << "--d : " << --d << "\n";   // 前置--
			d = Date(2025, 1, 1);
			std::cout << "d-- : " << d-- << "  (打印的是旧值)\n";
			std::cout << "现在: " << d << "\n\n";
		}

		std::cout << "===== 3) ++/-- 边界检查（跨月/跨年/闰年） =====\n";
		{
			Date d1(2025, 1, 31);  ++d1;  std::cout << "2025-1-31 ++ => " << d1 << " (应是 2025-2-1)\n";
			Date d2(2025, 12, 31); ++d2;  std::cout << "2025-12-31++ => " << d2 << " (应是 2026-1-1)\n";
			Date d3(2024, 2, 28);  ++d3;  std::cout << "2024-2-28 ++ => " << d3 << " (闰年，应是 2024-2-29)\n";
			Date d4(2024, 3, 1);   --d4;  std::cout << "2024-3-1  -- => " << d4 << " (闰年回退，应是 2024-2-29)\n\n";
		}

		std::cout << "===== 4) += / -= 与 + / - =====\n";
		{
			Date d(2025, 10, 15);
			std::cout << "起点: " << d << "\n";
			d += 100;  std::cout << " +=100 => " << d << "\n";
			d -= 1000; std::cout << " -=1000 => " << d << "\n";

			Date e(2025, 10, 14);
			Date e_plus = e + 100;   // 不修改 e
			Date e_minus = e - 10;    // 不修改 e
			std::cout << "e=" << e << "  e+100=" << e_plus << "  e-10=" << e_minus << "\n\n";
		}

		std::cout << "===== 5) 日期差（O(n) 版本） =====\n";
		{
			Date a(2025, 10, 15), b(2025, 10, 15);
			std::cout << a << " - " << b << " = " << (a - b) << " (应为 0)\n";
			Date c(2025, 10, 16), d(2025, 10, 15);
			std::cout << c << " - " << d << " = " << (c - d) << " (应为 1)\n";
			std::cout << d << " - " << c << " = " << (d - c) << " (应为 -1)\n";
			Date e(2024, 3, 1), f(2024, 2, 28); // 闰年
			std::cout << e << " - " << f << " = " << (e - f) << " (应为 2)\n\n";
		}

		std::cout << "===== 6) 输入 >> 测试（自己在控制台输入） =====\n";
		{
			Date x(2000, 1, 1);
			std::cout << "当前 x: " << x << "\n";
			std::cout << "请尝试输入一个合法日期（例：2024-02-29）\n";
			std::cin >> x;   // 你的 >> 内部会提示一次
			std::cout << "读取后 x: " << x << "\n\n";

			Date y(1999, 9, 9);
			std::cout << "当前 y: " << y << "\n";
			std::cout << "现在故意输一个非法的，比如 2024-02-30（看 y 是否保持不变）\n";
			std::cin >> y;   // 你的 >> 不会置失败；非法时 y 不会被修改
			std::cout << "读取后 y: " << y << "  (非法输入时应保持 1999-9-9)\n\n";
		}
	}
}
