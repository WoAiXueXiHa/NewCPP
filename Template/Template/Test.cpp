#include <iostream>
using namespace std;

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
