#pragma once
#include <iostream>
using namespace std;

namespace test1 {

	// == 多态： 不同类型的对象，做同一种行为，产生的结果不同 ==
	// == 例如： 同一个“叫”的动作 狗 猫 牛 羊都在叫 但是发声的结果不同
	// == 多态构成条件： 1. 虚函数完成重写----> 重写的是实现（函数体）返回值 函数名 参数列表相同
	// ===============  2. 基类指针或者引用调用虚函数 =====================

	class Fish {
	public:
		// 声明为虚函数 可实现多态行为
		virtual void swim() { cout << "Fish swims" << endl; }
	};

	class Carp : public Fish {
	public:
		virtual void swim() { cout << "Carp swims" << endl; } // 重写swim
	};
	class Tuna : public Fish {
	public:
		virtual void swim() { cout << "Tuna swims" << endl; } // 重写swim
	};

	void makeFishSwim(Fish& fish) { fish.swim(); }

	void test1() {
		Carp myLunch;
		Tuna mydinner;
		makeFishSwim(myLunch); 
		makeFishSwim(mydinner);
	}
}

namespace test2 {
	class Fish {
	public:
		Fish() { cout << "Fish 构造" << endl; }
		virtual ~Fish() { cout << "Fish 析构" << endl; }
	};

	class Carp : public Fish {
	public:
		Carp() { cout << "Carp 构造" << endl; }
		~Carp() { cout << "Carp 析构" << endl; }
	};

	// 使用new在堆区中实例化的派生类对象 如果将其赋给基类指针
	// 并通过该指针调用 delete 将不会调用派生类的析构函数
	// 这可能导致资源未释放 内存泄露等问题
	void deleteFishMemory(Fish* pFish) { delete pFish; }

	void test2() {
		cout << "== 演示开始" << endl;
		// 使用new在堆区中实例化的派生类对象 如果将其赋给基类指针
		// 并通过该指针调用 delete 将不会调用派生类的析构函数
		// 这可能导致资源未释放 内存泄露等问题
		Carp* pCarp = new Carp;
		cout << "==开始删除" << endl;
		// 在析构过程中 需要调用所有相关的析构 但是！！！！
		deleteFishMemory(pCarp); // 没有对Carp进行清理！！！！ ---->基类析构函数构造成虚函数！！！

		cout << endl << "Carp 在栈区" << endl;
		Carp myDinner;
		cout << "== 析构行为" << endl;
	}
}

// 再总结多态条件：
// 1. 派生类重写虚函数的实现
// 2. 基类引用或者指针调用虚函数
// 目的是：指向谁 调用谁

namespace test3 {
	class Car {
	public:
		virtual void drive() { cout << "Car" << endl; }
	};
	class Benz : public Car{
	public:
		virtual void drive() final { cout << " Benz 豪华" << endl; } // 虚函数不能再被重写
	};
	class BMW : public Car {
	public:
		virtual void drive() override { cout << "BWM 运动" << endl; }
	};
}

namespace virtualFun {
	class Base {
	public:
		virtual void fun1() { cout << "Base::fun1\n"; }   // 虚函数 #0
		virtual void fun2() { cout << "Base::fun2\n"; }   // 虚函数 #1
		void fun3() { cout << "Base::fun3\n"; }   // 非虚函数
		virtual ~Base() { cout << "~Base\n"; }     // 虚析构
	};

	class Derived : public Base {
	public:
		void fun1() override { cout << "Derived::fun1\n"; } 
		void fun2() override { cout << "Derived::fun2\n"; } 
		~Derived() override { cout << "~Derived\n"; }
	};

	void test() {
		Base* ptr= new Derived();  // 基类指针指向派生对象
		ptr->fun1();                   // 1) 虚调用 
		ptr->fun2();                   // 2) 虚调用
		ptr->fun3();                   // 3) 非虚 
		delete ptr;                 // 虚析构：先 ~Derived 再 ~Base
	}
}

namespace abstractClass {
	class Fish {
	public:
		virtual void swim() = 0; // 声明纯虚函数
	};

	class Carp : public Fish {
	public:
		void swim() override { cout << "Carp swims" << endl; } // 必须重写纯虚函数
	};

	class Tuna : public Fish {
	public:
		void swim() override { cout << "Tuna swims" << endl; } // 必须重写纯虚函数
	};

	void test() {
		Fish* carp = new Carp;
		carp->swim();
		Fish* tuna = new Tuna;
		tuna->swim();
	}
}