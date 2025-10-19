#include <iostream>
#include <string>
using namespace std;

// 定义一个基类
class Animal {
protected:
	string _name;
	int _age;
};

// 派生类
class Dog :public Animal {
	// Dog继承了Animal的成员变量和成员函数
	// 而Dog可以自己扩充自己的特点
	string _ability;
};