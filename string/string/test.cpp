#include <iostream>
#include <string>
using namespace std;

void test_member_functions() {
	// Ĭ�Ϲ��� ����һ�����ַ���
	string s1;
	// ����C��ʽ���ַ���(��\0��β���ַ���)
	string s2("Hello String");
	// ��������
	string s3(s2);
	// ��posλ�ÿ�ʼ������len�����ȵ��ַ�
	// len����Դ�ַ������ȣ�һֵ��������β
	string s4(s2, 3, 2);
	string s5(s2, 3, 30);// ������3��ʼ����������β
	string s6(s2, 3);// ������3��ʼ����������β

	// ��n��char�����ַ�����ַ���
	string s7(12, 'x');

	// ��s��ָ����ַ�����������n��ʼ�����Ƶ���β
	string s8(s2, 4);

	// �����ַ�������[first,last)������ַ�
	string s9(s2.begin(), s2.end()); // ������

	// ��ֵ���������
	string s10 = s6;
	string s11 = "hahaha";

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7 << endl;
	cout << s8 << endl;
	cout << s9 << endl;
	cout << s10 << endl;
	cout << s11 << endl;
}
void test_iterator_functions(){
	// ʹ�õ����� ������Զ��[,)����ҿ���
	// �����ַ����ķ���
	string s1 = "hello,string";
	// 1.operator[] 
	// char& operator[] (size_t pos); �����޸ķ��ض���
	// const char& operator[] (size_t pos) const; �����޸ķ��ض���
	for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i]++ << " ";
	}
	cout << endl;

	// 2. ������
	// iterator begin();const_iterator begin() const;
	// iterator end();const_iterator end() const;
	// �ֽ׶ο��԰ѵ��������Ϊ����ָ��Ķ���
	string::iterator it1 = s1.begin();
	while (it1 != s1.end()) {
		cout << *it1<< " ";
		++it1;
	}
	cout << endl;
	// iterator�ɶ���д
	it1 = s1.begin();
	while (it1 != s1.end()) {
		cout << (*it1)++ << " ";
		++it1;
	}
	cout << endl;
	// const_iteratorֻ��
	string::const_iterator it2 = s1.begin();
	while (it2 != s1.end()) {
		cout << *it2 << " ";
		//cout << (*it2)++ << " "; �����޸�
		++it2;
	}
	cout << endl;

	// ���������
	string::reverse_iterator it3 = s1.rbegin();
	while (it3 != s1.rend()) {
		cout << *it3 << " ";
		++it3;
	}
	cout << endl;

	// 3. ��Χfor ���ʻ��ǵ�����
	for (auto e : s1) cout << e << " ";
	cout << endl;
	// Ҳ���޸�
	for (auto e : s1) cout << e++ << " ";
}

void test_capacity_functions() {
	string s1 = "hello C++";
	// �����ַ�����Ч����
	cout << s1.size() << endl;
	// �����ַ���������
	cout << s1.capacity() << endl;
	// ����ַ����������ͷſռ�
	s1.clear();
	cout << "After clear,capacity:" << s1.capacity() << endl;
	// ����ַ����Ƿ�Ϊ��
	cout << s1.empty() << endl;

	// Ԥ���洢�ռ�
	string s2 = "abcdefghijk";
	s2.reserve(50);
	cout << "After reserve: " << s2.capacity() << endl;

	// ����������ƥ��ʵ�ʴ�С
	s2.shrink_to_fit();
	cout << "After shrink_to_fit: " << s2.capacity() << endl;

	// �ı��ַ�����С
	s2.resize(20, '!');
	cout << "After resize: " << s2 << endl;
	cout << "After resize, size: " << s2.size() << endl;
	cout << "After resize, capacity: " << s2.capacity() << endl;
}
int main() {
	// test_member_functions();
	// test_iterator_functions();
	test_capacity_functions();
	return 0;
}