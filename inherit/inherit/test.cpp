#include <iostream>
#include <string>
using namespace std;

//// 鱼品种的基类
//class Fish {
//protected:
//	bool isFreshWaterFish;
//public:
//	void swim() {
//		if (isFreshWaterFish) cout << "在湖泊小河中生存的鱼" << endl;
//		else cout << " 在海洋中生存的鱼" << endl;
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
//	cout << "我的食物：" << endl;
//	cout << "午餐：";
//	myLunch.swim();
//	cout << "晚餐:";
//	myDinner.swim();
//
//	return 0;
//}

// 基类初始化--向基类初始化
/*如果基类包含重载的构造函数，需要在实例化时给它提供实参，该如何办呢？
 *创建派生对象时将如何实例化这样的基类？
 *方法是：使用初始化列表，并通过派生类的构造函数调用合适的基类构造函数，
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
//		:Base(5) // 用基类走初始化列表
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
//		if (isFreshWaterFish) cout << "在湖泊小河中生存的鱼" << endl;
//		else cout << " 在海洋中生存的鱼" << endl;
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
//	cout << "我的食物：" << endl;
//	cout << "午餐：";
//	myLunch.swim();
//	cout << "晚餐:";
//	myDinner.swim();
//
//	return 0;
//}

//// 在派生类中覆盖基类的方法
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
//        if (isWoolProducer) cout << "以羊毛为主要产出的畜牧动物" << endl;
//        else cout << "以奶/肉为主要产出的畜牧动物" << endl;
//    }
//};
//
//class Cow : public Livestock {
//public:
//    Cow()
//        : Livestock(false) 
//    { }
//    void introduce() {
//        cout << "体重基数大，肉质紧实" << endl;
//    }
//};
//
//class Sheep : public Livestock {
//public:
//    Sheep()
//        : Livestock(true)  
//    { }
//    void introduce() {
//        cout << "体重基数小，肉质软嫩" << endl;
//    }
//};
//
//int main() {
//    Cow myLunch;
//    Sheep myDinner;
//
//    cout << "我的食物：" << endl;
//    cout << "午餐：";
//    myLunch.introduce();
//    cout << "晚餐:";
//    myDinner.introduce();
//
//    return 0;
//}

//// 在派生类中调用基类的方法 ::显式调用
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
//        if (isWoolProducer) cout << "以羊毛为主要产出的畜牧动物" << endl;
//        else cout << " 以奶/肉为主要产出的畜牧动物" << endl;
//    }
//};
//
//class Cow : public Livestock {
//public:
//    Cow()
//        : Livestock(false) 
//    { }
//    void introduce() {
//        cout << " 体重基数大，肉质紧实" << endl;
//    }
//};
//
//class Sheep : public Livestock {
//public:
//    Sheep()
//        : Livestock(true)  
//    { }
//    void introduce() {
//        cout << "体重基数小，肉质软嫩" << endl;
//    }
//};
//
//int main() {
//    Cow myLunch;
//    Sheep myDinner;
//
//    cout << "我的食物：" << endl;
//    cout << "午餐：";
//    myLunch.Livestock::introduce();
//    cout << "晚餐:";
//    myDinner.Livestock::introduce();
//
//    return 0;
//}

//// 隐藏：派生类中出现和基类同名的成员 隐藏基类成员
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
//        if (isWoolProducer) cout << "以羊毛为主要产出的畜牧动物" << endl;
//        else cout << " 以奶/肉为主要产出的畜牧动物" << endl;
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
//        cout << " 体重基数大，肉质紧实" << endl;
//    }
//};
//
//int main() {
//    Cow myLunch;
//
//    cout << "我的食物：" << endl;
//    cout << "午餐：";
//    myLunch.introduce();
//    // error C2660: “Cow::introduce”: 函数不接受 1 个参数
//    myLunch.introduce(false);
//    return 0;
//}

//// 派生类成员函数行为
//
//// 打印名字，观察顺序
//struct Tracker {
//	string _name;
//	Tracker(string n)
//		:_name(std::move(n)) {
//		cout << " 构造 " << _name << endl;
//	}
//	~Tracker() { cout << " 析构 " << _name << endl; }
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
//		cout << "Livestock构造" << endl;
//	}
//
//	Livestock(const Livestock& other) 
//		:_isWoolProducer(other._isWoolProducer)
//		,_age(other._age)
//		,_baseInfo(other._baseInfo)
//	{
//		cout << "Livestock拷贝构造" << endl;
//	}
//	~Livestock() { cout << "Livestock析构" << endl; }
//
//	Livestock& operator=(const Livestock& copy) {
//		if (this != &copy) {
//			_isWoolProducer = copy._isWoolProducer;
//			_age = copy._age;
//			_baseInfo = copy._baseInfo;
//			cout << "Livestock赋值重载" << endl;
//		}
//		return* this;
//	}
//
//	void introduce(bool wool) {
//		if (wool) cout << "已羊毛为主要产出的畜牧动物" << endl;
//		else cout << "以奶/肉为主要产出的畜牧动物" << endl;
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
//	static int weightInitial(int baseAge) { return 400 + baseAge * 10; } // 瞎编的
//
//public:
//	Cow()
//		:Livestock(false, 3)			// 构造基类子对象 永远在最先
//		, _ID(1234)						// cosnt成员必须在初始化列表赋值
//		, _cowInfo("Cow._cowInfo")		// 根据声明顺序走初始化列表
//		, _ageAlias(_age)				// 用基类的_age 基类已经构造好 安全
//		, _weight(weightInitial(_age))
//	{
//		cout << "Cow 构造" << endl;
//		cout << "-->weight=" << _weight
//			<< ",age=" << _age
//			<< ",ID=" << _ID << endl;
//	}
//
//	Cow(const Cow& other)
//		:Livestock(other)		 // 先拷贝构造基类子对象（按基类列表顺序）
//		, _weight(other._weight)
//		, _cowInfo(other._cowInfo)
//		, _ID(other._ID)
//		, _ageAlias(_age)          // 绑定自己本体的 _age 而不是 other._ageAlias
//	{
//		cout << "Cow拷贝构造" << endl;
//	}
//
//	Cow& operator=(const Cow& copy) {
//		if (this != &copy) {
//			Livestock::operator=(copy);  // 先赋基类子对象
//			_weight = copy._weight;
//			_cowInfo = copy._cowInfo;
//			// _ID 是 const：不可赋值（保持原值）
//			// _ageAlias 是引用：不可重新绑定（仍引用“本对象的 _age”）
//			cout << "Cow赋值重载" << endl;
//		}
//		return *this;
//	}
//
//	~Cow() { cout << "Cow析构" << endl; }
//
//	using Livestock::introduce;
//	void introduce() { cout << "体重基数大，肉质紧实" << endl; }
//
//};
//
//int main() {
//	cout << "=== 构造 ===" << endl;
//	Cow myLunch;
//	cout << "午餐：" << endl;
//	myLunch.introduce(); // 调用Cow无参版本
//	cout << "午餐（基类重载）:" << endl;
//	myLunch.introduce(false); // 有using 可以访问到基类
//
//
//	cout << "=== 拷贝构造 ===" << endl;
//	Cow copyLunch = myLunch;   // 调用 Cow(const Cow&)
//
//	cout << "=== 拷贝赋值 ===" << endl;
//	Cow assigned;              // 先默认构造一个
//	assigned = myLunch;        // 调用 Cow::operator=(const Cow&)
//
//	cout << "=== 析构 ===" << endl;
//	return 0;
//
//}

// 派生类对象可以赋值给基类的对象、指针、引用
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

	// 基类对象不能赋值给派生类对象 小->大 不行
	//stuObj = pA;

	return 0;
}