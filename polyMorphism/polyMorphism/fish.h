#pragma once
#include <iostream>
using namespace std;

namespace test1 {

	// == ��̬�� ��ͬ���͵Ķ�����ͬһ����Ϊ�������Ľ����ͬ ==
	// == ���磺 ͬһ�����С��Ķ��� �� è ţ ���ڽ� ���Ƿ����Ľ����ͬ
	// == ��̬���������� 1. �麯�������д----> ��д����ʵ�֣������壩����ֵ ������ �����б���ͬ
	// ===============  2. ����ָ��������õ����麯�� =====================

	class Fish {
	public:
		// ����Ϊ�麯�� ��ʵ�ֶ�̬��Ϊ
		virtual void swim() { cout << "Fish swims" << endl; }
	};

	class Carp : public Fish {
	public:
		virtual void swim() { cout << "Carp swims" << endl; } // ��дswim
	};
	class Tuna : public Fish {
	public:
		virtual void swim() { cout << "Tuna swims" << endl; } // ��дswim
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
		Fish() { cout << "Fish ����" << endl; }
		virtual ~Fish() { cout << "Fish ����" << endl; }
	};

	class Carp : public Fish {
	public:
		Carp() { cout << "Carp ����" << endl; }
		~Carp() { cout << "Carp ����" << endl; }
	};

	// ʹ��new�ڶ�����ʵ��������������� ������丳������ָ��
	// ��ͨ����ָ����� delete ������������������������
	// ����ܵ�����Դδ�ͷ� �ڴ�й¶������
	void deleteFishMemory(Fish* pFish) { delete pFish; }

	void test2() {
		cout << "== ��ʾ��ʼ" << endl;
		// ʹ��new�ڶ�����ʵ��������������� ������丳������ָ��
		// ��ͨ����ָ����� delete ������������������������
		// ����ܵ�����Դδ�ͷ� �ڴ�й¶������
		Carp* pCarp = new Carp;
		cout << "==��ʼɾ��" << endl;
		// ������������ ��Ҫ����������ص����� ���ǣ�������
		deleteFishMemory(pCarp); // û�ж�Carp�������������� ---->������������������麯��������

		cout << endl << "Carp ��ջ��" << endl;
		Carp myDinner;
		cout << "== ������Ϊ" << endl;
	}
}

// ���ܽ��̬������
// 1. ��������д�麯����ʵ��
// 2. �������û���ָ������麯��
// Ŀ���ǣ�ָ��˭ ����˭

namespace test3 {
	class Car {
	public:
		virtual void drive() { cout << "Car" << endl; }
	};
	class Benz : public Car{
	public:
		virtual void drive() final { cout << " Benz ����" << endl; } // �麯�������ٱ���д
	};
	class BMW : public Car {
	public:
		virtual void drive() override { cout << "BWM �˶�" << endl; }
	};
}

namespace virtualFun {
	class Base {
	public:
		virtual void fun1() { cout << "Base::fun1\n"; }   // �麯�� #0
		virtual void fun2() { cout << "Base::fun2\n"; }   // �麯�� #1
		void fun3() { cout << "Base::fun3\n"; }   // ���麯��
		virtual ~Base() { cout << "~Base\n"; }     // ������
	};

	class Derived : public Base {
	public:
		void fun1() override { cout << "Derived::fun1\n"; } 
		void fun2() override { cout << "Derived::fun2\n"; } 
		~Derived() override { cout << "~Derived\n"; }
	};

	void test() {
		Base* ptr= new Derived();  // ����ָ��ָ����������
		ptr->fun1();                   // 1) ����� 
		ptr->fun2();                   // 2) �����
		ptr->fun3();                   // 3) ���� 
		delete ptr;                 // ���������� ~Derived �� ~Base
	}
}

namespace abstractClass {
	class Fish {
	public:
		virtual void swim() = 0; // �������麯��
	};

	class Carp : public Fish {
	public:
		void swim() override { cout << "Carp swims" << endl; } // ������д���麯��
	};

	class Tuna : public Fish {
	public:
		void swim() override { cout << "Tuna swims" << endl; } // ������д���麯��
	};

	void test() {
		Fish* carp = new Carp;
		carp->swim();
		Fish* tuna = new Tuna;
		tuna->swim();
	}
}