#include <iostream>
using namespace std;

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