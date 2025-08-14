#include <iostream>
using namespace std;

//// const成员函数
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
//	// d1可以调用Print 权限的缩小
//	Date d1(2025, 8, 13);
//	d1.Print();
//
//	// 权限的平移
//	const Date d2(2025, 8, 14);
//	d2.Print();
//
//	return 0;
//}

//// 取地址运算符重载
//class show
//{
//public:
//    // 非const对象的取地址运算符重载
//    show* operator&()
//    {
//        // 返回当前对象的地址
//        return this;
//    }
//    show(int num = 0, char ch = '\0') 
//        : _num(num), 
//        _ch(ch) 
//    {
//        // ...
//    }
//
//    // const对象的取地址运算符重载
//    const show* operator&() const
//    {
//        // 返回空指针作为示例，实际中应根据需求返回有意义的地址
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
//    std::cout << "非const对象的地址: " << &obj1 << std::endl;
//    std::cout << "const对象的地址: " << &obj2 << std::endl;
//
//    return 0;
//}

// 初始化列表
///* const成员变量、引用成员变量、没有默认构造的成员变量，
//   必须放在初始化列表位置初始化，否则会报错
//*/
//class Time
//{
//public:
//	 非默认构造
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "调用Time的构造" << endl;
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
//		 ,_t(6) // 未在初始化列表初始化
//		 ,_ref(x) // 未在初始化列表初始化
//		 ,_n(num) // 未在初始化列表初始化
//	{		
//		 error C2512: “Time”: 没有合适的默认构造函数可用
//		_t = 6;
//		 error C2530: “Date::_ref”: 必须初始化引用
//		ref = x;
//		 error C2789: “Date::_n”: 必须初始化常量限定类型的对象
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
//	Time _t; // 没有默认构造
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

//// 修正版本：
//class Time
//{
//public:
//	// 非默认构造
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "调用Time的构造" << endl;
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
//	Time _t; // 没有默认构造
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

//// 在声明时给的缺省值是给初始化列表成员初始化使用
//class Time
//{
//public:
//	// 非默认构造
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "调用Time的构造" << endl;
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
//	// C++11 给缺省值用于参数列表成员初始化 此处仅声明 未定义
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

/*那些不在初始化列表初始化的成员也会先走一遍初始化列表，
  如果这个成员给了缺省值，初始化列表会使用缺省值初始化，
  如果没有缺省值，对于没有出现在初始化列表的内置成员，是否初始化取决于编译器，
  对于没有出现在初始化列表的自定义类型成员，会调用这个成员类型的默认构造函数，
  没有默认构造函数会报错
*/

//class Time
//{
//public:
//    // 无默认构造
//    Time(int hour)
//        :_hour(hour)
//    {
//        cout << "调用Time的构造" << endl;
//    }
//private:
//    int _hour;
//};
//
//class Show
//{
//public:
//    // 没有初始化列表的构造函数
//    Show(int num2, char ch2, Time t2)
//    {
//        // 这里只是赋值，不是初始化
//        _num = num2;
//        _ch = ch2;
//        // _t = t2;  // 即使这样写也会先尝试默认构造_t
//    }
//    void Print()const
//    {
//        cout << _num << "   " << _ch << endl;
//    }
//private:
//    int _num;              // 内置类型，无缺省值
//    char _ch = 'a';        // 内置类型，有缺省值
//    Time _t;               // 自定义类型，无默认构造，无缺省值
//    // Time _t2 = Time(10); // 如果这样给缺省值，也可以通过编译
//};
//
//int main()
//{
//    Time t(10);
//    Show s(1, 'b', t);  
//    return 0;
//}

//// 初始化列表初始化的顺序和成员变量出现的顺序一致
//class A
//{
//public:
//	A(int a)
//		:_a1(a)
//		, _a2(_a1)
//	{
//
//	}
//	void Print() {
//		cout << _a1 << " " << _a2 << endl;
//	}
//private:
//	int _a2 = 2;
//	int _a1 = 2;
//};
//int main()
//{
//	A aa(1);
//	aa.Print();
//	return 0;
//}

//// 类型转换
//class ShowA
//{
//public:
//	// 单参数构造
//	ShowA(int aa)
//		:_a(aa)
//	{
//		cout << "调用构造ShowA(int aa)" << endl;
//	}
//	// 多参数构造
//	ShowA(int aa, int aaa)
//		:_a(aa)
//		, _aa(aaa)
//	{
//		cout << "调用构造ShowA(int aa, int aaa)" << endl;
//	}
//	void Print()
//	{
//		cout << _a << "   " << _aa << endl;
//	}
//	int GetA() const
//	{
//		return _a + _aa;
//	}
//private:
//	int _a;
//	int _aa;
//};
//class ShowB
//{
//public:
//	ShowB(const ShowA& a)
//		:_b(a.GetA())
//	{
//		// ...
//	}
//private:
//	int _b;
//};
//int main()
//{
//	ShowA aaa1(10);
//	aaa1.Print();
//	// 拷贝构造
//	ShowA aaa2 = aaa1;
//
//	// 3(int)隐式类型转换成ShowA类 构造一个3的临时对象，再用临时对象拷贝构造aaa3
//	// 编译器遇到连续的构造+拷贝构造 会优化成->直接构造
//	ShowA aaa3 = 3;
//	aaa3.Print();
//	// C++11支持多参数转化
//	ShowA aaa4 = { 1,2 };
//	aaa4.Print();
//
//	ShowB bbb1 = aaa4;
//	// 引用的是aaa1构造的临时对象
//	const ShowB& rb =aaa1;
//
//	return 0;
//}

//class A
//{
//public:
//	
//private:
//	int _a = 1;
//	float _fa = 2.1;
//	// 静态成员变量在类内声明
//	static int _aa;
//};
//// 静态成员变量在类外初始化
//int A::_aa = 100;
//
//class B
//{
//public:
//private:
//	int _b = 0;
//};
//
//int main()
//{
//	cout << sizeof(A); // 8
//
//	return 0;
//}
//

// 实现一个类，计算程序出现多少个类对象
//class Calculate
//{
//public:
//	Calculate()
//	{
//		++_count;
//	}
//
//	Calculate(const Calculate& copy)
//	{
//		++_count;
//	}
//
//	~Calculate()
//	{
//		--_count;
//	}
//	static int GetCount()
//	{
//		return _count;
//	}
//private:
//	// 类内声明
//	static int _count;
//};
//// 类外初始化
//int Calculate::_count = 0;
//
//int main()
//{
//	cout << Calculate::GetCount() << endl;
//	Calculate a1, a2;
//	Calculate a3(a1);
//	cout << Calculate::GetCount() << endl;
//	cout << a1.GetCount() << endl;
//	//  error C2248: “Calculate::_count”: 无法访问 private 成员(在“Calculate”类中声明)
//	// cout << Calculate::_count << endl;
//	return 0;
//}

