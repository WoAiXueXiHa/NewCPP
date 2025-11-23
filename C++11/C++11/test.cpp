#include<iostream>
using namespace std;

/*****************************************************************************************/

void initialCpp98() {
	// C++98 用{}对数组和结构体进行统一的列表初始化
	int arr[] = { 10,20,34,2,2 };
	struct showEG {
		double x;
		double y;
		double z;
	};
	struct showEG pos = { 0.1,0.8 ,1.8};
}

void initialCpp11() {
	// C++11 对所有内置类型和自定义类型 {}进行初始化 =可以省略
	struct Point {
		double x;
		double y;
		double z;
	};
	struct Point pos{1.1,1.1,1.1};

	int num{ 10 };
	long long len{ 1024 };

	int arr[]{ 1,2,3,4,6,7 };

	class Date {
	private:
		int _year = 1;
		int _month = 1;
		int _day = 1;
	public:
		Date(int year,int month, int day)
			:_year(year)
			,_month(month)
			,_day(day)
		{ }
	};
	// 之前的初始化方式
	Date d(2020, 1, 1);
	// C++11引入的初始化方式
	Date d1{ 2025,11,11 };
}

#include <map>
#include <vector>
void initialList() {
	// initial_list 是什么类型
	auto il = { 1,2,3,4 };
	cout << typeid(il).name() << endl << endl;

	// 要和Date d1{ 2025,11,11 }区分开
	// {}里的元素个数取决于Date类中成员变量个数

	// 而以下{}里元素个数不限

	vector<int> v = { 1,2,3,4 };

	map<string, string> dict = { {"书","book"},{"排序","sort"} };
}

void showAuto() {
	auto num = 10.4;
	cout << typeid(num).name() << endl << endl;

	map<int, string> m = { {10,"hh"}, {12,"aa"} };
	cout << typeid(m).name() << endl;

}

template<class T1, class T2>
void Func(T1 num1, T2 num2) {
	decltype(num1 * num2) ret;
	cout << typeid(ret).name() << endl;
}

void showDecltype() {
	const int x = 1;
	double y = 2.6;

	decltype(x * y) ret;
	decltype(&x) pos;
	cout << typeid(ret).name() << endl;
	cout << typeid(pos).name() << endl;

	Func('a', 1.5);
}
/***********************************************************************************************/


void showLeftValue() {
	// num dnum *pnum 都是左值
	int num = 10;
	double dnum = 1.5;
	const int* pnum = &num;

	// rnum rdnum rpnum 都是左值引用
	int& rnum = num;			// 引用int类型变量
	double& rdnum = dnum;		// 引用double类型变量
	const int*& rpnum = pnum;	// 引用const指针类型变量

	// 可以给左值赋值
	num = 20;
	// 左值可以出现在=右侧
	dnum = (double)num;
}

#include <string>;
bool Fmin(char a, char b) { return a < b ? a : b; }

void showRightValue() {
	// "13245" 1.1 2.2 Fmin('a', 'c') (x + y)都是右值
	string s = "13245";
	double x = 1.1, y = 2.2;
	Fmin('a', 'c');
	double plus = x + y;

	// 以下都是右值引用
	int&& rrnum = 10;
	double&& rrplus = x + y;
	char&& ret = Fmin('a', 'c');

	// 右值不能出现在=左边
	//  error C2106: “=”: 左操作数必须为左值
	//10 = x;
	//x + y = 2.0;
	//Fmin('a', 'b') = 0;

}

void visitLow() {
	int num = 10;

	int& rnum = num;
	int&& rrnum = 10;
}

void leftVSright() {
	// 左值引用只能引用左值
	int val = 10;
	int& rval1 = val;
	// C2440: “初始化”: 无法从“int”转换为“int &” 非常量引用只能绑定到左值
	//int& rval2 = 10;

	// const左值引用可以引用右值
	const int&& rrval = 10;

	// 右值引用只能引用右值
	double num = 1.1;
	double&& rrnum1 = 1.1;
	// C2440: “初始化”: 无法从“double”转换为“double &&” 无法将左值绑定到右值引用
	//double&& rrnum2 = num;

	// 右值引用可以引用move后的左值
	double&& rrnum = move(num);
}

class buffer {
public:
	// 普通构造 开一块空间
	buffer(size_t n)
		:_data(new int[n])
		, _size(n) 
	{
		cout << "构造buffer(" << n << ")" << endl;
	}

	// 拷贝构造 深拷贝
	buffer(const buffer& other)
		:_data(new int[other._size])
		, _size(other._size)
	{
		cout << "拷贝构造 buffer" << endl;
		for (size_t i = 0; i < _size; i++)
		{
			_data[i] = other._data[i];
		}
	}
	// 析构
	~buffer() {
		cout << "析构buffer" << endl;
		delete[] _data;
	}
private:
	int* _data;
	size_t _size;

};

buffer MakeBuffer() {
	buffer buf(10);   // 构造一块 10 个 int 的数组
	// ... 
	return buf;       // 返回局部对象
}

int main() {
	buffer b = MakeBuffer();
	return 0;
}

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