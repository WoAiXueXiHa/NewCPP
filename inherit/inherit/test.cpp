#include <iostream>
#include <string>
using namespace std;

//// ��Ʒ�ֵĻ���
//class Fish {
//protected:
//	bool isFreshWaterFish;
//public:
//	void swim() {
//		if (isFreshWaterFish) cout << "�ں���С�����������" << endl;
//		else cout << " �ں������������" << endl;
//	}
//};
//
//class Carp : public Fish {
//public:
//	Carp() { isFreshWaterFish = true; }
//};
//
//class Tuna : public Fish {
//public:
//	Tuna() { isFreshWaterFish = false; }
//};
//
//int main() {
//	Carp myLunch;
//	Tuna myDinner;
//
//	cout << "�ҵ�ʳ�" << endl;
//	cout << "��ͣ�";
//	myLunch.swim();
//	cout << "���:";
//	myDinner.swim();
//
//	return 0;
//}

// �����ʼ��--������ʼ��
/*�������������صĹ��캯������Ҫ��ʵ����ʱ�����ṩʵ�Σ�����ΰ��أ�
 *������������ʱ�����ʵ���������Ļ��ࣿ
 *�����ǣ�ʹ�ó�ʼ���б���ͨ��������Ĺ��캯�����ú��ʵĻ��๹�캯����
*/
//class Base {
//public:
//	Base(int someNumber){
//		//...
//	}
//};
//class Derived : public Base {
//public:
//	Derived()
//		:Base(5) // �û����߳�ʼ���б�
//	{ }
//};

//class Fish {
//protected:
//	bool isFreshWaterFish;
//public:
//	Fish(bool isFreshWaterFish)
//		: isFreshWaterFish(isFreshWaterFish)
//	{ }
//
//	void swim() {
//		if (isFreshWaterFish) cout << "�ں���С�����������" << endl;
//		else cout << " �ں������������" << endl;
//	}
//};
//
//class Carp : public Fish {
//public:
//	Carp()
//		:Fish(true)
//	{ }
//};
//
//class Tuna : public Fish {
//public:
//	Tuna()
//		:Fish(false)
//	{ }
//};
//
//int main() {
//	Carp myLunch;
//	Tuna myDinner;
//
//	cout << "�ҵ�ʳ�" << endl;
//	cout << "��ͣ�";
//	myLunch.swim();
//	cout << "���:";
//	myDinner.swim();
//
//	return 0;
//}

//// ���������и��ǻ���ķ���
//class Base {
//public:
//	void func() {
//		// ...
//	}
//};
//class Derived : public Base {
//public:
//	void func() {
//		// ...
//	}
//};

//class Livestock {
//protected:
//    bool isWoolProducer;
//public:
//    Livestock(bool isWoolProducer)
//        : isWoolProducer(isWoolProducer)
//    {
//    }
//
//    void introduce() {
//        if (isWoolProducer) cout << "����ëΪ��Ҫ��������������" << endl;
//        else cout << "����/��Ϊ��Ҫ��������������" << endl;
//    }
//};
//
//class Cow : public Livestock {
//public:
//    Cow()
//        : Livestock(false) 
//    { }
//    void introduce() {
//        cout << "���ػ��������ʽ�ʵ" << endl;
//    }
//};
//
//class Sheep : public Livestock {
//public:
//    Sheep()
//        : Livestock(true)  
//    { }
//    void introduce() {
//        cout << "���ػ���С����������" << endl;
//    }
//};
//
//int main() {
//    Cow myLunch;
//    Sheep myDinner;
//
//    cout << "�ҵ�ʳ�" << endl;
//    cout << "��ͣ�";
//    myLunch.introduce();
//    cout << "���:";
//    myDinner.introduce();
//
//    return 0;
//}

//// ���������е��û���ķ��� ::��ʽ����
//class Livestock {
//protected:
//    bool isWoolProducer;
//public:
//    Livestock(bool isWoolProducer)
//        : isWoolProducer(isWoolProducer)
//    {
//    }
//
//    void introduce() {
//        if (isWoolProducer) cout << "����ëΪ��Ҫ��������������" << endl;
//        else cout << " ����/��Ϊ��Ҫ��������������" << endl;
//    }
//};
//
//class Cow : public Livestock {
//public:
//    Cow()
//        : Livestock(false) 
//    { }
//    void introduce() {
//        cout << " ���ػ��������ʽ�ʵ" << endl;
//    }
//};
//
//class Sheep : public Livestock {
//public:
//    Sheep()
//        : Livestock(true)  
//    { }
//    void introduce() {
//        cout << "���ػ���С����������" << endl;
//    }
//};
//
//int main() {
//    Cow myLunch;
//    Sheep myDinner;
//
//    cout << "�ҵ�ʳ�" << endl;
//    cout << "��ͣ�";
//    myLunch.Livestock::introduce();
//    cout << "���:";
//    myDinner.Livestock::introduce();
//
//    return 0;
//}

//// ���أ��������г��ֺͻ���ͬ���ĳ�Ա ���ػ����Ա
//class Livestock {
//protected:
//    bool isWoolProducer;
//public:
//    Livestock(bool isWoolProducer)
//        : isWoolProducer(isWoolProducer)
//    {
//    }
//
//
//    void introduce(bool isWoolProducer) {
//        if (isWoolProducer) cout << "����ëΪ��Ҫ��������������" << endl;
//        else cout << " ����/��Ϊ��Ҫ��������������" << endl;
//    }
//    void introduece() { cout << "......" << endl; }
//};
//
//class Cow : public Livestock {
//public:
//    Cow()
//        : Livestock(false) 
//    { }
//    using Livestock::introduce;
//    void introduce() {
//        cout << " ���ػ��������ʽ�ʵ" << endl;
//    }
//};
//
//int main() {
//    Cow myLunch;
//
//    cout << "�ҵ�ʳ�" << endl;
//    cout << "��ͣ�";
//    myLunch.introduce();
//    // error C2660: ��Cow::introduce��: ���������� 1 ������
//    myLunch.introduce(false);
//    return 0;
//}

//// �������Ա������Ϊ
//
//// ��ӡ���֣��۲�˳��
//struct Tracker {
//	string _name;
//	Tracker(string n)
//		:_name(std::move(n)) {
//		cout << " ���� " << _name << endl;
//	}
//	~Tracker() { cout << " ���� " << _name << endl; }
//};
//
//class Livestock {
//protected:
//	bool _isWoolProducer;
//	int _age;
//	Tracker _baseInfo;
//
//	Livestock(bool w,int age) 
//		:_isWoolProducer(w) 
//		,_age(age)
//		,_baseInfo("Livestock.baseInfo")
//	{
//		cout << "Livestock����" << endl;
//	}
//
//	Livestock(const Livestock& other) 
//		:_isWoolProducer(other._isWoolProducer)
//		,_age(other._age)
//		,_baseInfo(other._baseInfo)
//	{
//		cout << "Livestock��������" << endl;
//	}
//	~Livestock() { cout << "Livestock����" << endl; }
//
//	Livestock& operator=(const Livestock& copy) {
//		if (this != &copy) {
//			_isWoolProducer = copy._isWoolProducer;
//			_age = copy._age;
//			_baseInfo = copy._baseInfo;
//			cout << "Livestock��ֵ����" << endl;
//		}
//		return* this;
//	}
//
//	void introduce(bool wool) {
//		if (wool) cout << "����ëΪ��Ҫ��������������" << endl;
//		else cout << "����/��Ϊ��Ҫ��������������" << endl;
//	}
//
//	void introduce() { cout << "......" << endl; }
//
//};
//
//class Cow : public Livestock {
//private:
//	int _weight;
//	Tracker _cowInfo;
//	const int _ID;
//	const int& _ageAlias;
//	
//	static int weightInitial(int baseAge) { return 400 + baseAge * 10; } // Ϲ���
//
//public:
//	Cow()
//		:Livestock(false, 3)			// ��������Ӷ��� ��Զ������
//		, _ID(1234)						// cosnt��Ա�����ڳ�ʼ���б�ֵ
//		, _cowInfo("Cow._cowInfo")		// ��������˳���߳�ʼ���б�
//		, _ageAlias(_age)				// �û����_age �����Ѿ������ ��ȫ
//		, _weight(weightInitial(_age))
//	{
//		cout << "Cow ����" << endl;
//		cout << "-->weight=" << _weight
//			<< ",age=" << _age
//			<< ",ID=" << _ID << endl;
//	}
//
//	Cow(const Cow& other)
//		:Livestock(other)		 // �ȿ�����������Ӷ��󣨰������б�˳��
//		, _weight(other._weight)
//		, _cowInfo(other._cowInfo)
//		, _ID(other._ID)
//		, _ageAlias(_age)          // ���Լ������ _age ������ other._ageAlias
//	{
//		cout << "Cow��������" << endl;
//	}
//
//	Cow& operator=(const Cow& copy) {
//		if (this != &copy) {
//			Livestock::operator=(copy);  // �ȸ������Ӷ���
//			_weight = copy._weight;
//			_cowInfo = copy._cowInfo;
//			// _ID �� const�����ɸ�ֵ������ԭֵ��
//			// _ageAlias �����ã��������°󶨣������á�������� _age����
//			cout << "Cow��ֵ����" << endl;
//		}
//		return *this;
//	}
//
//	~Cow() { cout << "Cow����" << endl; }
//
//	using Livestock::introduce;
//	void introduce() { cout << "���ػ��������ʽ�ʵ" << endl; }
//
//};
//
//int main() {
//	cout << "=== ���� ===" << endl;
//	Cow myLunch;
//	cout << "��ͣ�" << endl;
//	myLunch.introduce(); // ����Cow�޲ΰ汾
//	cout << "��ͣ��������أ�:" << endl;
//	myLunch.introduce(false); // ��using ���Է��ʵ�����
//
//
//	cout << "=== �������� ===" << endl;
//	Cow copyLunch = myLunch;   // ���� Cow(const Cow&)
//
//	cout << "=== ������ֵ ===" << endl;
//	Cow assigned;              // ��Ĭ�Ϲ���һ��
//	assigned = myLunch;        // ���� Cow::operator=(const Cow&)
//
//	cout << "=== ���� ===" << endl;
//	return 0;
//
//}

// �����������Ը�ֵ������Ķ���ָ�롢����
class Person {
protected:
	int _age;
	string _sex;
	string _name;
};

class Student : public Person {
protected:
	int _score;
};
int main() {
	Student stuObj;
	Person pA = stuObj;
	Person& pB = stuObj;
	Person* pC = &stuObj;

	// ��������ܸ�ֵ����������� С->�� ����
	//stuObj = pA;

	return 0;
}