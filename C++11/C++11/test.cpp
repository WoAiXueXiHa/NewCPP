//#include<iostream>
//using namespace std;
//
///*****************************************************************************************/
//
//void initialCpp98() {
//	// C++98 用{}对数组和结构体进行统一的列表初始化
//	int arr[] = { 10,20,34,2,2 };
//	struct showEG {
//		double x;
//		double y;
//		double z;
//	};
//	struct showEG pos = { 0.1,0.8 ,1.8};
//}
//
//void initialCpp11() {
//	// C++11 对所有内置类型和自定义类型 {}进行初始化 =可以省略
//	struct Point {
//		double x;
//		double y;
//		double z;
//	};
//	struct Point pos{1.1,1.1,1.1};
//
//	int num{ 10 };
//	long long len{ 1024 };
//
//	int arr[]{ 1,2,3,4,6,7 };
//
//	class Date {
//	private:
//		int _year = 1;
//		int _month = 1;
//		int _day = 1;
//	public:
//		Date(int year,int month, int day)
//			:_year(year)
//			,_month(month)
//			,_day(day)
//		{ }
//	};
//	// 之前的初始化方式
//	Date d(2020, 1, 1);
//	// C++11引入的初始化方式
//	Date d1{ 2025,11,11 };
//}
//
//#include <map>
//#include <vector>
//void initialList() {
//	// initial_list 是什么类型
//	auto il = { 1,2,3,4 };
//	cout << typeid(il).name() << endl << endl;
//
//	// 要和Date d1{ 2025,11,11 }区分开
//	// {}里的元素个数取决于Date类中成员变量个数
//
//	// 而以下{}里元素个数不限
//
//	vector<int> v = { 1,2,3,4 };
//
//	map<string, string> dict = { {"书","book"},{"排序","sort"} };
//}
//
//void showAuto() {
//	auto num = 10.4;
//	cout << typeid(num).name() << endl << endl;
//
//	map<int, string> m = { {10,"hh"}, {12,"aa"} };
//	cout << typeid(m).name() << endl;
//
//}
//
//template<class T1, class T2>
//void Func(T1 num1, T2 num2) {
//	decltype(num1 * num2) ret;
//	cout << typeid(ret).name() << endl;
//}
//
//void showDecltype() {
//	const int x = 1;
//	double y = 2.6;
//
//	decltype(x * y) ret;
//	decltype(&x) pos;
//	cout << typeid(ret).name() << endl;
//	cout << typeid(pos).name() << endl;
//
//	Func('a', 1.5);
//}
///***********************************************************************************************/
//
//
//void showLeftValue() {
//	// num dnum *pnum 都是左值
//	int num = 10;
//	double dnum = 1.5;
//	const int* pnum = &num;
//
//	// rnum rdnum rpnum 都是左值引用
//	int& rnum = num;			// 引用int类型变量
//	double& rdnum = dnum;		// 引用double类型变量
//	const int*& rpnum = pnum;	// 引用const指针类型变量
//
//	// 可以给左值赋值
//	num = 20;
//	// 左值可以出现在=右侧
//	dnum = (double)num;
//}
//
//#include <string>;
//bool Fmin(char a, char b) { return a < b ? a : b; }
//
//void showRightValue() {
//	// "13245" 1.1 2.2 Fmin('a', 'c') (x + y)都是右值
//	string s = "13245";
//	double x = 1.1, y = 2.2;
//	Fmin('a', 'c');
//	double plus = x + y;
//
//	// 以下都是右值引用
//	int&& rrnum = 10;
//	double&& rrplus = x + y;
//	char&& ret = Fmin('a', 'c');
//
//	// 右值不能出现在=左边
//	//  error C2106: “=”: 左操作数必须为左值
//	//10 = x;
//	//x + y = 2.0;
//	//Fmin('a', 'b') = 0;
//
//}
//
//void visitLow() {
//	int num = 10;
//
//	int& rnum = num;
//	int&& rrnum = 10;
//}
//
//void leftVSright() {
//	// 左值引用只能引用左值
//	int val = 10;
//	int& rval1 = val;
//	// C2440: “初始化”: 无法从“int”转换为“int &” 非常量引用只能绑定到左值
//	//int& rval2 = 10;
//
//	// const左值引用可以引用右值
//	const int&& rrval = 10;
//
//	// 右值引用只能引用右值
//	double num = 1.1;
//	double&& rrnum1 = 1.1;
//	// C2440: “初始化”: 无法从“double”转换为“double &&” 无法将左值绑定到右值引用
//	//double&& rrnum2 = num;
//
//	// 右值引用可以引用move后的左值
//	double&& rrnum = move(num);
//}
//
//class buffer {
//public:
//	// 普通构造 开一块空间
//	buffer(size_t n)
//		:_data(new int[n])
//		, _size(n) 
//	{
//		cout << "构造buffer(" << n << ")" << endl;
//	}
//
//	// 拷贝构造 深拷贝
//	buffer(const buffer& other)
//		:_data(new int[other._size])
//		, _size(other._size)
//	{
//		cout << "拷贝构造 buffer" << endl;
//		for (size_t i = 0; i < _size; i++)
//		{
//			_data[i] = other._data[i];
//		}
//	}
//
//	// 移动构造 偷资源
//	// other的资源即将释放 this拿来直接用
//	buffer(buffer&& other) noexcept
//		:_data(other._data)
//		, _size(other._size)
//	{
//		cout << "移动构造 buffer" << endl;
//		other._data = nullptr;
//		other._size = 0;
//	}
//	
//	// 拷贝赋值：深拷贝+释放旧资源
//	buffer& operator=(const buffer& other) {
//		cout << "拷贝赋值 buffer" << endl;
//		if (this != &other) {
//			// 先备份旧数据 避免自拷贝
//			int* newData = other._size ? new int[other._size] : nullptr;
//			for (size_t i = 0; i < other._size; i++)
//			{
//				newData[i] = other._data[i];
//			}
//			delete[] _data;
//			_data = newData;
//			_size = other._size;
//		}
//		return *this;
//	}
//
//	// 移动赋值
//	buffer& operator=(buffer&& other) noexcept {
//		cout << "移动赋值 buffer" << endl;
//		if (this != &other) {
//			delete[] _data;	// 先释放旧资源
//
//			_data = other._data; // 直接接管对方资源
//			_size = other._size;
//			other._data = nullptr;
//			other._size = 0;
//		}
//		return *this;
//	}
//
//	// 析构
//	~buffer() {
//		cout << "析构buffer" << endl;
//		delete[] _data;
//	}
//
//	size_t size() const { return _size; }
//private:
//	int* _data;
//	size_t _size;
//
//};
//
//void testNoExpand() {
//	cout << "=== 不扩容场景： push_back 左值/右值 ===" << endl;
//	vector<buffer> v;
//	v.reserve(3);
//
//	cout << "\n---插入左值---\n";
//	buffer b1(10);
//	v.push_back(b1);
//
//	cout << "\n---插入右值---\n";
//	v.push_back(buffer(20));
//
//	cout << "\n---插入move(b1)---\n";
//	v.push_back(move(b1));
//
//	cout << "=== 析构 ===" << endl;
//}
//
//void testExpand() {
//	cout << "=== 扩容场景： vector 重新分配 ===" << endl;
//	vector<buffer> v;
//	v.reserve(2);
//
//	cout << "\n push_back(b1) \n";
//	buffer b1(10);
//	v.push_back(b1);
//
//	cout << "\n push_back(b1) \n";
//	buffer b2(20);
//	v.push_back(b2);
//
//	cout << "\n 第三次 触发扩容机制 \n";
//	buffer b3(30);
//	v.push_back(b3);
//
//	cout << "=== 析构 ===" << endl;
//}

//int main() {
//	//testNoExpand();
//	testExpand();
//
//	return 0;
//}

//buffer MakeBuffer() {
//	buffer buf(10);   // 构造一块 10 个 int 的数组
//	// ... 
//	return buf;       // 返回局部变量
//}
//
//int main() {
//	buffer b = MakeBuffer();
//	return 0;
//}

//
// 
//int main() {
//	//initialList();
//	//showAuto();
//
//	//showDecltype();
//
//	/*showLeftValue();
//	showRightValue();*/
//
//	//visitLow();
//	leftVSright();
//	return 0;
//}



/***********************************************************************************************/
#include <iostream>
using namespace std;
//
//void F(int& x) { cout << "F(int& 左值)" << endl; }
//void F(const int& x) { cout << "F(const int& 左值)" << endl; }
//void F(int&& x) { cout << "F(int&& 右值)" << endl; }
//void F(const int&& x) { cout << "F(const int&& 右值)" << endl; }
//
//// 错误写法：
//template<class T>
//void Relay(T t) {
//	cout << "Relay\n";
//	F(t);	// 会发生什么？
//}
//
//int main() {
//	int a = 10;
//	Relay(a);		// 传左值
//	Relay(10);		// 传右值
//
//	return 0;
//}

//// 正确写法：万能引用+完美转发
//
//void F(int& x) { cout << "F(int& 左值)" << endl; }
//void F(const int& x) { cout << "F(const int& 左值)" << endl; }
//void F(int&& x) { cout << "F(int&& 右值)" << endl; }
//void F(const int&& x) { cout << "F(const int&& 右值)" << endl; }
//
//// 错误示范：丢失右值
//template<class T>
//void BadForward(T&& t) {
//	cout << "BadForward(T&& t)：" ;
//	F(t);		// t永远是左值
//}
//
//// 完美转发
//template<class T>
//void PerfectForward(T&& t) {
//	cout << "PerfectForward(T&& t)：";
//	F(forward<T>(t));
//}
//
//int main() {
//	int a = 10;
//	const int ca = 20;
//
//	cout << "=== 传左值a ===\n";
//	BadForward(a);
//	PerfectForward(a);
//
//	cout << "\n=== 传const左值ca ===\n";
//	BadForward(ca);
//	PerfectForward(ca);
//
//	cout << "\n=== 传右值10 ===\n";
//	BadForward(10);
//	PerfectForward(10);
//
//	cout << "\n=== 传const右值10 ===\n";
//	BadForward(10);
//	PerfectForward(10);
//
//	return 0;
//}

/***********************************************************************************************/
//#include <vector>
//
//struct Widget {
//	Widget(int x, int y) {
//		cout << "构造Widget(" << x << "," << y << ")\n";
//	}
//	Widget(const Widget&) {
//		cout << "拷贝构造Widget\n";
//	}
//	Widget(Widget&&) noexcept {
//		cout << "移动构造Widget\n";
//	}
//};
//
//int main() {
//	vector<Widget> v;
//	v.reserve(4);
//
//	/*cout << "push_back\n";
//	v.push_back(Widget(1, 2));
//
//	cout << "emplace_back\n";
//	v.emplace_back(1, 2);*/
//	Widget w(1, 2);
//	v.push_back(w);				// 左值：拷贝构造
//	v.emplace_back(w);			// 拷贝构造
//
//	v.push_back(move(w));		// 右值：移动构造
//	v.emplace_back(move(w));	// 移动构造
//
//	return 0;
//}

#include <map>

void test() {
	map<int, string> m;

	// 写法一： 传pair所需的参数
	m.emplace(2, "hh");

	// 写法二： make_pair
	m.emplace(make_pair(2, string("hh")));
}