#include <iostream>
#include <string>
using namespace std;

// ����һ������
class Animal {
protected:
	string _name;
	int _age;
};

// ������
class Dog :public Animal {
	// Dog�̳���Animal�ĳ�Ա�����ͳ�Ա����
	// ��Dog�����Լ������Լ����ص�
	string _ability;
};