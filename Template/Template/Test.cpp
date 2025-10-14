#include <iostream>
#include <stdbool.h>
using namespace std;

/*=============================== ���� ==========================================*/
//// ˼�������ʵ��һ��ͨ�õĽ���������
//// ��ͳ��ʽ���������أ������������Ͳ�ͬ��������д�ظ��Ĵ���
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
//// ���ͱ�̣�д�������޹ص�ͨ�ô��룬�Ǵ�����õ�һ���ֶ�
//
//// ����ģ��
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

//// ��ʽʵ����
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
//	//  ��T Add(const T,const T)��: �޷��ӡ�double���Ƶ�����const T���� ģ�� ����
//	//  ����ģ��ֻ��һ������T����������֪��Ҫ���˴���T���ݳ�int���ͻ���double����
//	// ��ʱ�����ֽ���취�� 1. ǿ������ת�� 2. ��ʽʵ����
//	/*Add(a, y);
//	Add(x, b);*/
//
//	cout << Add(x, (double)b) << endl;;
//	cout << Add(a, (int)y) << endl;;
//
//	// ��ʽʵ����
//	Add<int>(x, b);
//	return 0;
//}

//// һ����ģ�庯�����Ժ�һ��ͬ���ĺ���ģ��ͬʱ���ڣ����Ҹú���ģ�廹�ܱ�ʵ�����������ģ�庯��
//
//// ר�Ŵ���int���͵ĳ˷�����
//int Mul(const int left, const int right)
//{
//	return left * right;
//}
//// ͨ�ó˷�ģ�庯��
//template<typename T>
//T Mul(const T left, const T right)
//{
//	return left * right;
//}
//
//int main()
//{
//	// 00007FF62E3818D6  call        Mul (07FF62E3813E8h)  
//	Mul(3, 7);// ���ģ�庯��ƥ�䣬��������Ҫ����
//	// 00007FF62E3818E6  call        Mul<int> (07FF62E3813EDh)  
//	Mul<int>(9, 2);// ���ñ��������ݵİ汾
//
//	return 0;
//}

// ���ڷ�ģ�庯����ͬ����ģ�庯�������������������ͬ���ڵ���ʱ�����ȵ��÷�ģ�庯��������ʵ������
// ���ģ����Բ���һ������ƥ��ĺ�������ѡ��ģ��

//// ����int���͵ļӷ�����
//int Add(const int left, const int right)
//{
//	return left + right;
//}
//
//// ͨ�üӷ�ģ�庯��
//template<typename T1, typename T2>
//T1 Add(const T1 left, const T2 right)
//{
//	return left + right;
//}
//
//int main()
//{
//	// 00007FF7E02318D6  call        Add (07FF7E02313F7h)  
//	Add(1, 2);// ��Ǻ���ģ��������ȫƥ�䣬����Ҫ����ģ��ʵ����
//	// 00007FF7E02318E9  call        Add<int,double> (07FF7E02313F2h)  
//	Add(1, 2.1);// ģ�庯���������ɸ���ƥ��İ汾������������ʵ�����ɸ���ƥ���Add
//
//	return 0;
//	
//}

//// ��̬˳���
//// ע�⣺Vector���Ǿ�����࣬�Ǳ��������ݱ�ʵ�������������ɾ������ģ��
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
//	// ʹ������������ʾ�������������������ⶨ�塣
//	~Vector();
//
//	void PushBack(const T& data)��
//		void PopBack()��
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
//// ע�⣺��ģ���к�������������ж���ʱ����Ҫ��ģ������б�
//template <class T>
//Vector<T>::~Vector()
//{
//	if (_pData)
//		delete[] _pData;
//	_size = _capacity = 0;
//}

//

//// Vector���� Vector<int>��������
//Vector<int> t1;
//Vector<double> t2;


/*=============================== ���� ==========================================*/

//// 1. ������ģ�����
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

// 2. ģ����ػ�
//// 2.1.ʵ��һ��С�ڱȽϵĺ���ģ��
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
//// �ػ�ָ��Ƚ�
//template<>
//// const T& val ���ε������ֵ�����޸� 
//// ��ô��Ӧָ�����ָ������ݲ����޸� ������ָ�벻���޸�
//// ���д��̫���� ����ģ���ػ�������ʹ�� ��Ҫ�ػ��İ汾ֱ��ʵ��һ����������
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
//	cout << Less(1, 2) << endl; // ��ȷ
//	cout << Less('X', 'Y') << endl; // ��ȷ
//	
//	Date d1(2025, 10, 20);
//	Date d2(2025, 10, 15);
//	cout << Less(d1, d2) << endl; // �Ƚ���ȷ
//
//	// ����Ƚϵ��ǵ�ַ ����ָ�������
//	Date* ptr1 = &d1;
//	Date* ptr2 = &d2;
//	cout << Less(ptr1, ptr2) << endl; // ���ԱȽ� ������� 
//}

// 2.2. ȫ�ػ�
// ��ģ��
template <class T1, class T2>
class Show {
public:
	Show() { cout << "Show<T1,T2>"<<endl; }
private:
	T1 _showInt;
	T2 _showChar;
};
// ȫ�ػ�
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

// 2.3. ƫ�ػ�
// 1>����һ�������ػ�Ϊint
template <class T2>
class Show<int,T2> {
public:
	Show() { cout << "Show<int,T2>" << endl; }
private:
	int _showInt;
	T2 _showChar;
};

// 2>  ������������ͬ�����͡��ػ� ���������ػ�Ϊָ������
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
	//  ����Ҫд template����ʾ bar �ǡ���Աģ�塱
	h.template bar<int>(42);
}