#pragma once
#include <iostream>
#include <set>
using namespace std;


void testSetInsert() {
	set<int> s;
	s.insert(2);
	s.insert(5);
	s.insert(8);
	s.insert(3);
	s.insert(9);
	s.insert(11);
	s.insert(7);
	
	set<int>::iterator it = s.begin();
	while (it != s.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	// 不能插入重复的值
	s.insert(7);
	cout << "插入重复值7：\n";
	for (const auto& e : s) cout << e << " ";

	cout << "逆序遍历：\n";
	set<int>::reverse_iterator rit = s.rbegin();
	while (rit != s.rend()) {
		cout << *rit << " ";
		++rit;
	}

	cout << endl;
}

void testSetErase() {
	set<string> mySet;
	mySet.insert("123");
	mySet.insert("kunkun");
	mySet.insert("张三");
	mySet.insert("李四");
	mySet.insert("abc");
	
	auto it = mySet.begin();
	cout << "删除前:\n";
	for (const auto& e : mySet) cout << e << "  ";

	mySet.erase(mySet.find("123"));
	cout << "\n删除123之后：\n";
	for (const auto& e : mySet) cout << e << "  ";

	it = mySet.find("abc");
	it = mySet.erase(it);
	cout << "\n删除abc之后：\n";
	for (const auto& e : mySet) cout << e << "  ";

	// 全部删除 注意迭代器失效问题 
	it = mySet.begin();
	while (it != mySet.end()) {
		it = mySet.erase(it); // 返回删除后的下一个迭代器位置
	}
	cout << "\n全部删除之后：\n";
	cout << "剩余元素：" << mySet.size();
}
