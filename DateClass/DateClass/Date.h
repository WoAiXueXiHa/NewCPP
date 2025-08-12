#include <iostream>
#include <assert.h>
#include <stdbool.h>
using namespace std;
class Date
{
public:

	//  声明友元函数
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

	// 获取月份的天数
	int GetMonthDay(int year, int month);
	// 构造函数
	Date(int year = 1, int month = 1, int day = 1);
	// 判断日期合法性
	bool CheckDate();

	// 日期比大小
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;

	// 日期加减运算
	Date& operator+=(int day);
	Date operator+(int day) const;
	Date operator-(int day) const;
	int operator-(const Date& d);
	Date& operator-=(int day);

	Date& operator++();
	Date operator++(int) const;
	Date operator--(int) const;
	Date& operator--();

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in, Date& d);

// 测试比较运算符
void TestCompare();
// 测试日期加减天数（含月底/年底边界）
void TestAddSubDay();
// 测试两个日期相差的天数
void TestDateDiff();
// 测试自增自减
void TestIncDec();
// 测试非法日期处理
void TestInvalidDate();

