#pragma once
#include <iostream>
#include <set>
using namespace std;


void testSet() {
	// 1. ����+����
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
	// ���ܲ����ظ���ֵ
	s.insert(7);
	cout << "�����ظ�ֵ7��\n";
	for (const auto& e : s) cout << e << " ";

	cout << "���������\n";
	set<int>::reverse_iterator rit = s.rbegin();
	while (rit != s.rend()) {
		cout << *rit << " ";
		++rit;
	}

	cout << endl;

	// 2. ɾ��
	int x = 0;
	cin >> x;
	auto pos = s.find(x);
	if (pos != s.end()) s.erase(pos);
	else cout << x << "�����ڣ�\n";
	cout << "ɾ��������У�\n";
	for (const auto& e : s) cout << e << " ";

}
