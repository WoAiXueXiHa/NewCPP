#include <iostream>
using namespace std;

//// const��Ա����
//class Date
//{
//public:
//
//	Date(int year, int month, int day)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{
//		// ...
//	}
//
//	// Date* const this -> const Date* const this
//	void Print()const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	// d1���Ե���Print Ȩ�޵���С
//	Date d1(2025, 8, 13);
//	d1.Print();
//
//	// Ȩ�޵�ƽ��
//	const Date d2(2025, 8, 14);
//	d2.Print();
//
//	return 0;
//}

//// ȡ��ַ���������
//class show
//{
//public:
//    // ��const�����ȡ��ַ���������
//    show* operator&()
//    {
//        // ���ص�ǰ����ĵ�ַ
//        return this;
//    }
//    show(int num = 0, char ch = '\0') 
//        : _num(num), 
//        _ch(ch) 
//    {
//        // ...
//    }
//
//    // const�����ȡ��ַ���������
//    const show* operator&() const
//    {
//        // ���ؿ�ָ����Ϊʾ����ʵ����Ӧ�������󷵻�������ĵ�ַ
//        return nullptr; 
//    }
//
//private:
//    int _num;
//    char _ch;
//};
//
//int main()
//{
//    show obj1;
//    const show obj2;
//
//    std::cout << "��const����ĵ�ַ: " << &obj1 << std::endl;
//    std::cout << "const����ĵ�ַ: " << &obj2 << std::endl;
//
//    return 0;
//}

// ��ʼ���б�
///* const��Ա���������ó�Ա������û��Ĭ�Ϲ���ĳ�Ա������
//   ������ڳ�ʼ���б�λ�ó�ʼ��������ᱨ��
//*/
//class Time
//{
//public:
//	 ��Ĭ�Ϲ���
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "����Time�Ĺ���" << endl;
//	}
//private:
//	int _hour;
//};
//class Date
//{
//public:
//	Date(int year, int month, int day, int& x,int num)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//		 ,_t(6) // δ�ڳ�ʼ���б��ʼ��
//		 ,_ref(x) // δ�ڳ�ʼ���б��ʼ��
//		 ,_n(num) // δ�ڳ�ʼ���б��ʼ��
//	{		
//		 error C2512: ��Time��: û�к��ʵ�Ĭ�Ϲ��캯������
//		_t = 6;
//		 error C2530: ��Date::_ref��: �����ʼ������
//		ref = x;
//		 error C2789: ��Date::_n��: �����ʼ�������޶����͵Ķ���
//		_n = num;
//	}
//
//		void Print()const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t; // û��Ĭ�Ϲ���
//	int& _ref;
//	const int _n;
//
//};
//
//int main()
//{
//	int i = 0;
//	Date d1(2025,8,14,i,100);
//	d1.Print();
//
//	return 0;
//}

//// �����汾��
//class Time
//{
//public:
//	// ��Ĭ�Ϲ���
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "����Time�Ĺ���" << endl;
//	}
//private:
//	int _hour;
//};
//class Date
//{
//public:
//	Date(int year, int month, int day, int& x, int num)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//		 ,_t(6) 
//		 ,_ref(x) 
//		 ,_n(num) 
//	{
//		// ...
//	}
//
//	void Print()const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t; // û��Ĭ�Ϲ���
//	int& _ref;
//	const int _n;
//
//};
//
//int main()
//{
//	int i = 0;
//	Date d1(2025, 8, 14, i, 100);
//	d1.Print();
//
//	return 0;
//}

//// ������ʱ����ȱʡֵ�Ǹ���ʼ���б��Ա��ʼ��ʹ��
//class Time
//{
//public:
//	// ��Ĭ�Ϲ���
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "����Time�Ĺ���" << endl;
//	}
//private:
//	int _hour;
//};
//class Date
//{
//public:
//	Date(int year, int month, int day, int& x, int num)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{
//		// ...
//	}
//
//	void Print()const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	// C++11 ��ȱʡֵ���ڲ����б��Ա��ʼ�� �˴������� δ����
//	Time _t = 6; 
//	const int _n = 100;
//	const int& _ref = _n;
//
//};
//
//int main()
//{
//	int i = 0;
//	Date d1(2025, 8, 14, i, 100);
//	d1.Print();
//
//	return 0;
//}

/*��Щ���ڳ�ʼ���б��ʼ���ĳ�ԱҲ������һ���ʼ���б�
  ��������Ա����ȱʡֵ����ʼ���б��ʹ��ȱʡֵ��ʼ����
  ���û��ȱʡֵ������û�г����ڳ�ʼ���б�����ó�Ա���Ƿ��ʼ��ȡ���ڱ�������
  ����û�г����ڳ�ʼ���б���Զ������ͳ�Ա������������Ա���͵�Ĭ�Ϲ��캯����
  û��Ĭ�Ϲ��캯���ᱨ��
*/

//class Time
//{
//public:
//    // ��Ĭ�Ϲ���
//    Time(int hour)
//        :_hour(hour)
//    {
//        cout << "����Time�Ĺ���" << endl;
//    }
//private:
//    int _hour;
//};
//
//class Show
//{
//public:
//    // û�г�ʼ���б�Ĺ��캯��
//    Show(int num2, char ch2, Time t2)
//    {
//        // ����ֻ�Ǹ�ֵ�����ǳ�ʼ��
//        _num = num2;
//        _ch = ch2;
//        // _t = t2;  // ��ʹ����дҲ���ȳ���Ĭ�Ϲ���_t
//    }
//    void Print()const
//    {
//        cout << _num << "   " << _ch << endl;
//    }
//private:
//    int _num;              // �������ͣ���ȱʡֵ
//    char _ch = 'a';        // �������ͣ���ȱʡֵ
//    Time _t;               // �Զ������ͣ���Ĭ�Ϲ��죬��ȱʡֵ
//    // Time _t2 = Time(10); // ���������ȱʡֵ��Ҳ����ͨ������
//};
//
//int main()
//{
//    Time t(10);
//    Show s(1, 'b', t);  
//    return 0;
//}

// ��ʼ���б��ʼ����˳��ͳ�Ա�������ֵ�˳��һ��
class A
{
public:
	A(int a)
		:_a1(a)
		, _a2(_a1)
	{

	}
	void Print() {
		cout << _a1 << " " << _a2 << endl;
	}
private:
	int _a2 = 2;
	int _a1 = 2;
};
int main()
{
	A aa(1);
	aa.Print();
	return 0;
}