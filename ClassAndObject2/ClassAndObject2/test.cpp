#include <iostream>
#include <assert.h>

using namespace std;

// �������캯��
// ���캯�������أ���һ�����������������Ͷ��������
// ����ͬ�����Ŀ�����ʼ��

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
		// �����С��д���˻ᷢ��ʲô��
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

