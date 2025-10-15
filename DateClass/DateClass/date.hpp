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
			assert(1 <= month && month <= 12 && "��������ȷ���·�");
			if (month == 2) return isLeapYear(year) ? 29 : 28;
			return dayArray[month];
		}


		// ����
		Date(int year = 2025, int month = 10, int day = 1)
			:_year(year)
			,_month(month)
			,_day(day)
		{
			assert(isValid(_year, _month, _day) && "���ڷǷ�");
		}

		// ��������
		Date(const Date& other)
			:_year(other._year)
			,_month(other._month)
			,_day(other._day)
		{ }

		// ��ֵ����
		Date& operator=(const Date& copyFrom) {
			if (this != &copyFrom) {
				_year = copyFrom._year;
				_month = copyFrom._month;
				_day = copyFrom._day;
			}
			return *this;
		}

		// ���������
		// ȷ�������߼� ʣ�¶����Ը���
		bool operator>(const Date& compObj) const {
			if (_year != compObj._year) return _year > compObj._year;
			if (_month != compObj._month) return _month > compObj._month;
			return _day > compObj._day;  // �����ꡢ����ȵ����
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

		// ǰ��++ --
		Date& operator++() {
			++_day;
			// ��Ҫ���Լӵ���һ���·�
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
			// ��Ҫ���Ǽ�����һ���·�
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
		
		// ����++ --
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

		// ���ڼӼ����� d1 += 12
		Date& operator+=(int day) {
			assert(day > 0 && "�������������˽ӿ�Ϊ���ڼ�����");
			while (day > 0) {
				++(*this);
				--day;
			}
			return *this;
		}
		Date& operator-=(int day) {
			assert(day > 0 && "�������������˽ӿ�Ϊ���ڼ�����");
			while (day > 0) {
				--(*this);
				--day;
			}
			return *this;
		}

		// ���޸��Լ�
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


		// ���ڼ����ڵõ������� O(n)
		int operator-(const Date& other) const {
			int count = 0;
			// ���޸��β�
			Date tmp = other;

			// ��ȣ���Ϊ 0
			if (*this == tmp) return 0;

			// *this > other
			if (*this > tmp) {
				while (tmp != *this) {
					++tmp;      
					++count;    // �����ۼӲ���
				}
				return count; 
			}

			// *this < other
			while (tmp != *this) {
				--tmp;          
				++count;        // �����ۼӲ���
			}
			return -count;
		}

	};
	// �����������
	std::istream& operator>>(std::istream& in, Vect::Date& date) {
		std::cout << "�밴�ո�ʽ�������ڣ�year-month-day:  >" << std::endl;
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

	//	std::cout << "============ ���ԱȽ� ============" << std::endl;
	//	std::cout << "2025-10-15�Ƿ����2027-6-20�� " << (d1 == d2) << std::endl;
	//	std::cout << "2025-10-15�Ƿ����2027-6-20�� " << (d1 > d2) << std::endl;
	//	std::cout << "2025-10-15�Ƿ���ڵ���2027-6-20�� " << (d1 >= d2) << std::endl;
	//	std::cout << "2025-10-15�Ƿ�С��2027-6-20�� " << (d1 < d2) << std::endl;
	//	std::cout << "2025-10-15�Ƿ�С�ڵ���2027-6-20�� " << (d1 <= d2) << std::endl;
	//}

	//void datePlusAndSub() {
	//	Date testDate1(2025, 1, 1);
	//	std::cout << "============ ���������Լ� ============" << std::endl;
	//	std::cout << "ԭ���ڣ� " << testDate1 << std::endl;
	//	std::cout << "ǰ��++�����ڣ� " << ++testDate1 << std::endl;
	//	testDate1 = { 2025,1,1 };
	//	std::cout << "����++�����ڣ� " << testDate1++ << std::endl;
	//	testDate1 = { 2025,1,1 };
	//	std::cout << "����--�����ڣ� " << testDate1-- << std::endl;
	//	testDate1 = { 2025,1,1 };
	//	std::cout << "ǰ��--�����ڣ� " << --testDate1 << std::endl;

	//	std::cout << "========================================" << std::endl;
	//	Date testDate2(2024, 3, 1);
	//	std::cout << "ԭ���ڣ� " << testDate2 << std::endl;
	//	std::cout << "ǰ��++�����ڣ� " << ++testDate2 << std::endl;
	//	testDate2 = { 2024, 3, 1 };
	//	std::cout << "����++�����ڣ� " << testDate2++ << std::endl;
	//	testDate2 = { 2024, 3, 1 };
	//	std::cout << "ǰ��--�����ڣ� " << --testDate2 << std::endl;
	//	testDate2 = { 2024, 3, 1 };
	//	std::cout << "����--�����ڣ� " << testDate2-- << std::endl;
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
		std::cout << "===== 1) �Ƚ�������� =====\n";
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

		std::cout << "===== 2) ǰ��/���� �����Լ� ���� =====\n";
		{
			Date d(2025, 1, 1);
			std::cout << "ԭʼ: " << d << "\n";
			std::cout << "++d : " << ++d << "\n";   // ǰ��++
			d = Date(2025, 1, 1);
			std::cout << "d++ : " << d++ << "  (��ӡ���Ǿ�ֵ)\n";
			std::cout << "����: " << d << "\n";
			d = Date(2025, 1, 1);
			std::cout << "--d : " << --d << "\n";   // ǰ��--
			d = Date(2025, 1, 1);
			std::cout << "d-- : " << d-- << "  (��ӡ���Ǿ�ֵ)\n";
			std::cout << "����: " << d << "\n\n";
		}

		std::cout << "===== 3) ++/-- �߽��飨����/����/���꣩ =====\n";
		{
			Date d1(2025, 1, 31);  ++d1;  std::cout << "2025-1-31 ++ => " << d1 << " (Ӧ�� 2025-2-1)\n";
			Date d2(2025, 12, 31); ++d2;  std::cout << "2025-12-31++ => " << d2 << " (Ӧ�� 2026-1-1)\n";
			Date d3(2024, 2, 28);  ++d3;  std::cout << "2024-2-28 ++ => " << d3 << " (���꣬Ӧ�� 2024-2-29)\n";
			Date d4(2024, 3, 1);   --d4;  std::cout << "2024-3-1  -- => " << d4 << " (������ˣ�Ӧ�� 2024-2-29)\n\n";
		}

		std::cout << "===== 4) += / -= �� + / - =====\n";
		{
			Date d(2025, 10, 15);
			std::cout << "���: " << d << "\n";
			d += 100;  std::cout << " +=100 => " << d << "\n";
			d -= 1000; std::cout << " -=1000 => " << d << "\n";

			Date e(2025, 10, 14);
			Date e_plus = e + 100;   // ���޸� e
			Date e_minus = e - 10;    // ���޸� e
			std::cout << "e=" << e << "  e+100=" << e_plus << "  e-10=" << e_minus << "\n\n";
		}

		std::cout << "===== 5) ���ڲO(n) �汾�� =====\n";
		{
			Date a(2025, 10, 15), b(2025, 10, 15);
			std::cout << a << " - " << b << " = " << (a - b) << " (ӦΪ 0)\n";
			Date c(2025, 10, 16), d(2025, 10, 15);
			std::cout << c << " - " << d << " = " << (c - d) << " (ӦΪ 1)\n";
			std::cout << d << " - " << c << " = " << (d - c) << " (ӦΪ -1)\n";
			Date e(2024, 3, 1), f(2024, 2, 28); // ����
			std::cout << e << " - " << f << " = " << (e - f) << " (ӦΪ 2)\n\n";
		}

		std::cout << "===== 6) ���� >> ���ԣ��Լ��ڿ���̨���룩 =====\n";
		{
			Date x(2000, 1, 1);
			std::cout << "��ǰ x: " << x << "\n";
			std::cout << "�볢������һ���Ϸ����ڣ�����2024-02-29��\n";
			std::cin >> x;   // ��� >> �ڲ�����ʾһ��
			std::cout << "��ȡ�� x: " << x << "\n\n";

			Date y(1999, 9, 9);
			std::cout << "��ǰ y: " << y << "\n";
			std::cout << "���ڹ�����һ���Ƿ��ģ����� 2024-02-30���� y �Ƿ񱣳ֲ��䣩\n";
			std::cin >> y;   // ��� >> ������ʧ�ܣ��Ƿ�ʱ y ���ᱻ�޸�
			std::cout << "��ȡ�� y: " << y << "  (�Ƿ�����ʱӦ���� 1999-9-9)\n\n";
		}
	}
}
