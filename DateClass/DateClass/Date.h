#include <iostream>
#include <assert.h>
#include <stdbool.h>
using namespace std;
class Date
{
public:

	//  ������Ԫ����
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

	// ��ȡ�·ݵ�����
	int GetMonthDay(int year, int month);
	// ���캯��
	Date(int year = 1, int month = 1, int day = 1);
	// �ж����ںϷ���
	bool CheckDate();

	// ���ڱȴ�С
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;

	// ���ڼӼ�����
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

// ���ԱȽ������
void TestCompare();
// �������ڼӼ����������µ�/��ױ߽磩
void TestAddSubDay();
// ��������������������
void TestDateDiff();
// ���������Լ�
void TestIncDec();
// ���ԷǷ����ڴ���
void TestInvalidDate();

