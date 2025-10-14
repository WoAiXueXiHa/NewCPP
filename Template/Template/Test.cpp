#include <iostream>
#include <stdbool.h>
using namespace std;

/*=============================== 初阶 ==========================================*/
//// 思考：如何实现一个通用的交换函数？
//// 传统方式：函数重载，但是遇到类型不同，反复的写重复的代码
//void Swap(int& left, int& right)
//{
//	int tmp = left;
//	left = right;
//	right = tmp;
//}
//
//void Swap(double& left, double& right)
//{
//	int tmp = left;
//	left = right;
//	right = tmp;
//}
//
//void Swap(int*& left, int*& right)
//{
//	int* tmp = left;
//	left = right;
//	right = tmp;
//}
//
//// 泛型编程：写与类型无关的通用代码，是代码服用的一种手段
//
//// 函数模板
//template<typename T>
//void Swap(T& left, T& right)
//{
//	T tmp = left;
//	left = right;
//	right = tmp;
//}
//
//int main()
//{
//	int a = 1;
//	int b = 6;
//	Swap(a, b);
//
//	double x = 2.1;
//	double y = 3.3;
//	Swap(x, y);
//
//	int* ptra = &a;
//	int* ptrb = &b;
//	Swap(ptra, ptrb);
//
//	return 0;
//}

//// 隐式实例化
//template<typename T>
//T Add(const T left, const T right)
//{
//	return left + right;
//}
//
//int main()
//{
//	int a = 10;
//	int b = 20;
//	double x = 2.1;
//	double y = 3.0;
//
//	cout << Add(a, b) << endl;
//	cout<<Add(x, y)<<endl;
//
//	//  “T Add(const T,const T)”: 无法从“double”推导出“const T”的 模板 参数
//	//  函数模板只有一个参数T，编译器不知道要将此处的T推演成int类型还是double类型
//	// 此时有两种解决办法： 1. 强制类型转换 2. 显式实例化
//	/*Add(a, y);
//	Add(x, b);*/
//
//	cout << Add(x, (double)b) << endl;;
//	cout << Add(a, (int)y) << endl;;
//
//	// 显式实例化
//	Add<int>(x, b);
//	return 0;
//}

//// 一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还能被实例化成这个非模板函数
//
//// 专门处理int类型的乘法函数
//int Mul(const int left, const int right)
//{
//	return left * right;
//}
//// 通用乘法模板函数
//template<typename T>
//T Mul(const T left, const T right)
//{
//	return left * right;
//}
//
//int main()
//{
//	// 00007FF62E3818D6  call        Mul (07FF62E3813E8h)  
//	Mul(3, 7);// 与非模板函数匹配，编译器不要推演
//	// 00007FF62E3818E6  call        Mul<int> (07FF62E3813EDh)  
//	Mul<int>(9, 2);// 调用编译器推演的版本
//
//	return 0;
//}

// 对于非模板函数和同名的模板函数，如果其他条件都相同，在调用时会优先调用非模板函数而不会实例化。
// 如果模板可以产生一个更好匹配的函数，则选择模板

//// 处理int类型的加法函数
//int Add(const int left, const int right)
//{
//	return left + right;
//}
//
//// 通用加法模板函数
//template<typename T1, typename T2>
//T1 Add(const T1 left, const T2 right)
//{
//	return left + right;
//}
//
//int main()
//{
//	// 00007FF7E02318D6  call        Add (07FF7E02313F7h)  
//	Add(1, 2);// 与非函数模板类型完全匹配，不需要函数模板实例化
//	// 00007FF7E02318E9  call        Add<int,double> (07FF7E02313F2h)  
//	Add(1, 2.1);// 模板函数可以生成更加匹配的版本，编译器根据实参生成更加匹配的Add
//
//	return 0;
//	
//}

//// 动态顺序表
//// 注意：Vector不是具体的类，是编译器根据被实例化的类型生成具体类的模具
//template<class T>
//class Vector
//{
//public:
//	Vector(size_t capacity = 10)
//		: _pData(new T[capacity])
//		, _size(0)
//		, _capacity(capacity)
//	{
//	}
//
//	// 使用析构函数演示：在类中声明，在类外定义。
//	~Vector();
//
//	void PushBack(const T& data)；
//		void PopBack()；
//		// ...
//
//		size_t Size() { return _size; }
//
//	T& operator[](size_t pos)
//	{
//		assert(pos < _size);
//		return _pData[pos];
//	}
//
//private:
//	T* _pData;
//	size_t _size;
//	size_t _capacity;
//};
//// 注意：类模板中函数放在类外进行定义时，需要加模板参数列表
//template <class T>
//Vector<T>::~Vector()
//{
//	if (_pData)
//		delete[] _pData;
//	_size = _capacity = 0;
//}

//

//// Vector类名 Vector<int>才是类型
//Vector<int> t1;
//Vector<double> t2;


/*=============================== 进阶 ==========================================*/

//// 1. 非类型模板参数
//template<typename T, size_t size = 10>
//class Array {
//public:
//	T& operator[](size_t index) { return _array[index]; }
//	const T& operator[](size_t index) const { return _array[index]; }
//	size_t size() const { return _size; }
//	bool empty() const { return _size == 0; }
//private:
//	T _array[size];
//	size_t _size;
//};

// 2. 模板的特化
//// 2.1.实现一个小于比较的函数模板
//template<class T>
//bool Less(const T& left,  const T& right) { return left < right; }
//
//class Date {
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	Date(int year = 2025, int month = 10, int day = 15)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{ }
//	bool operator<(const Date& other) const noexcept {
//		if (_year < other._year) return true;
//		if (_year > other._year) return false;
//
//		if (_month < other._month) return true;
//		if (_month > other._month) return false;
//
//		return _day < other._day; 
//	}
//};
//// 特化指针比较
//template<>
//// const T& val 修饰的是这个值不可修改 
//// 那么对应指针就是指向的内容不可修改 而不是指针不能修改
//// 这个写法太怪了 函数模板特化不建议使用 需要特化的版本直接实现一个函数更好
//bool Less<Date*>(Date* const& left, Date* const& right) { return *left < *right; }
//
//bool Less(Date* left, Date* right) { return *left < *right; }
//int main() {
//	Date d1(2025, 10, 20);
//	Date d2(2025, 10, 15);
//	Date* ptr1 = &d1;
//	Date* ptr2 = &d2;
//	cout << Less(ptr1, ptr2) << endl; 
//}

//int main() {
//	cout << Less(1, 2) << endl; // 正确
//	cout << Less('X', 'Y') << endl; // 正确
//	
//	Date d1(2025, 10, 20);
//	Date d2(2025, 10, 15);
//	cout << Less(d1, d2) << endl; // 比较正确
//
//	// 这里比较的是地址 并非指向的内容
//	Date* ptr1 = &d1;
//	Date* ptr2 = &d2;
//	cout << Less(ptr1, ptr2) << endl; // 可以比较 结果错误 
//}

// 2.2. 全特化
// 类模板
template <class T1, class T2>
class Show {
public:
	Show() { cout << "Show<T1,T2>"<<endl; }
private:
	T1 _showInt;
	T2 _showChar;
};
// 全特化
//template<>
//class Show<int, char> {
//public:
//	Show() { cout << "Show<int,char>"<<endl; }
//private:
//	int _showInt;
//	char _showChar;
//};
//
//int main() {
//	Show<int, int> s1;
//	Show<int, char> s2;
//}

// 2.3. 偏特化
// 1>将第一个参数特化为int
template <class T2>
class Show<int,T2> {
public:
	Show() { cout << "Show<int,T2>" << endl; }
private:
	int _showInt;
	T2 _showChar;
};

// 2>  按”两个参数同种类型“特化 两个参数特化为指针类型
template <typename T1, typename T2>
class Show<T1*,T2*> {
public:
	Show() { cout << "Show<T1*,T2*>" << endl; }
private:
	T1* _showInt;
	T2* _showChar;
};

//int main() {
//	Show<int, double> s1;
//	Show<char, double> s2;
//	Show<int*, double*> s3;
//
//	return 0;
//}
#include <vector>
template <class T>
void printVector(const vector<T>& data) {
	typename vector<T>::const_iterator it = data.begin();
	while (it != data.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

int main() {
	vector<int> arr1 = { 1, 2, 3, 4, 5 };
	vector<double> arr2 = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	printVector(arr1);
	printVector(arr2);
}

template <class T>
struct Has {
	template <class U>
	void bar(U) {}
};

template <class X>
void call(Has<X>& h) {
	//  这里要写 template，表示 bar 是“成员模板”
	h.template bar<int>(42);
}