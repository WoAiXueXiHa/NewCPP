#include <iostream>
#include <string>
using namespace std;

void test_member_functions() {
	// 默认构造 构造一个空字符串
	string s1;
	// 构造C格式的字符串(以\0结尾的字符串)
	string s2("Hello String");
	// 拷贝构造
	string s3(s2);
	// 从pos位置开始，拷贝len个长度的字符
	// len大于源字符串长度，一值拷贝到结尾
	string s4(s2, 3, 2);
	string s5(s2, 3, 30);// 从索引3开始，拷贝到结尾
	string s6(s2, 3);// 从索引3开始，拷贝到结尾

	// 用n个char类型字符填充字符串
	string s7(12, 'x');

	// 从s所指向的字符数组中索引n开始，复制到结尾
	string s8(s2, 4);

	// 拷贝字符数组中[first,last)区间的字符
	string s9(s2.begin(), s2.end()); // 迭代器

	// 赋值运算符重载
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
	// 使用迭代器 区间永远是[,)左闭右开的
	// 遍历字符串的方法
	string s1 = "hello,string";
	// 1.operator[] 
	// char& operator[] (size_t pos); 可以修改返回对象
	// const char& operator[] (size_t pos) const; 不能修改返回对象
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

	// 2. 迭代器
	// iterator begin();const_iterator begin() const;
	// iterator end();const_iterator end() const;
	// 现阶段可以把迭代器理解为类似指针的东西
	string::iterator it1 = s1.begin();
	while (it1 != s1.end()) {
		cout << *it1<< " ";
		++it1;
	}
	cout << endl;
	// iterator可读可写
	it1 = s1.begin();
	while (it1 != s1.end()) {
		cout << (*it1)++ << " ";
		++it1;
	}
	cout << endl;
	// const_iterator只读
	string::const_iterator it2 = s1.begin();
	while (it2 != s1.end()) {
		cout << *it2 << " ";
		//cout << (*it2)++ << " "; 不能修改
		++it2;
	}
	cout << endl;

	// 反向迭代器
	string::reverse_iterator it3 = s1.rbegin();
	while (it3 != s1.rend()) {
		cout << *it3 << " ";
		++it3;
	}
	cout << endl;

	// 3. 范围for 本质还是迭代器
	for (auto e : s1) cout << e << " ";
	cout << endl;
	// 也能修改
	for (auto e : s1) cout << e++ << " ";
}

void test_capacity_functions() {
	string s1 = "hello C++";
	// 返回字符串有效个数
	cout << s1.size() << endl;
	// 返回字符串的容量
	cout << s1.capacity() << endl;
	// 清空字符串，但不释放空间
	s1.clear();
	cout << "After clear,capacity:" << s1.capacity() << endl;
	// 检查字符串是否为空
	cout << s1.empty() << endl;

	// 预留存储空间
	string s2 = "abcdefghijk";
	s2.reserve(50);
	cout << "After reserve: " << s2.capacity() << endl;

	// 缩减容量以匹配实际大小
	s2.shrink_to_fit();
	cout << "After shrink_to_fit: " << s2.capacity() << endl;

	// 改变字符串大小
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