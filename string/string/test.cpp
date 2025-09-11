//#include <iostream>
//#include <string>
//using namespace std;
//
//void test_member_functions() {
//	// 默认构造 构造一个空字符串
//	string s1;
//	// 构造C格式的字符串(以\0结尾的字符串)
//	string s2("Hello String");
//	// 拷贝构造
//	string s3(s2);
//	// 从pos位置开始，拷贝len个长度的字符
//	// len大于源字符串长度，一值拷贝到结尾
//	string s4(s2, 3, 2);
//	string s5(s2, 3, 30);// 从索引3开始，拷贝到结尾
//	string s6(s2, 3);// 从索引3开始，拷贝到结尾
//
//	// 用n个char类型字符填充字符串
//	string s7(12, 'x');
//
//	// 从s所指向的字符数组中索引n开始，复制到结尾
//	string s8(s2, 4);
//
//	// 拷贝字符数组中[first,last)区间的字符
//	string s9(s2.begin(), s2.end()); // 迭代器
//
//	// 赋值运算符重载
//	string s10 = s6;
//	string s11 = "hahaha";
//
//	cout << s1 << endl;
//	cout << s2 << endl;
//	cout << s3 << endl;
//	cout << s4 << endl;
//	cout << s5 << endl;
//	cout << s6 << endl;
//	cout << s7 << endl;
//	cout << s8 << endl;
//	cout << s9 << endl;
//	cout << s10 << endl;
//	cout << s11 << endl;
//}
//void test_iterator_functions(){
//	// 使用迭代器 区间永远是[,)左闭右开的
//	// 遍历字符串的方法
//	string s1 = "hello,string";
//	// 1.operator[] 
//	// char& operator[] (size_t pos); 可以修改返回对象
//	// const char& operator[] (size_t pos) const; 不能修改返回对象
//	for (size_t i = 0; i < s1.size(); i++)
//	{
//		cout << s1[i] << " ";
//	}
//	cout << endl;
//	for (size_t i = 0; i < s1.size(); i++)
//	{
//		cout << s1[i]++ << " ";
//	}
//	cout << endl;
//
//	// 2. 迭代器
//	// iterator begin();const_iterator begin() const;
//	// iterator end();const_iterator end() const;
//	// 现阶段可以把迭代器理解为类似指针的东西
//	string::iterator it1 = s1.begin();
//	while (it1 != s1.end()) {
//		cout << *it1<< " ";
//		++it1;
//	}
//	cout << endl;
//	// iterator可读可写
//	it1 = s1.begin();
//	while (it1 != s1.end()) {
//		cout << (*it1)++ << " ";
//		++it1;
//	}
//	cout << endl;
//	// const_iterator只读
//	string::const_iterator it2 = s1.begin();
//	while (it2 != s1.end()) {
//		cout << *it2 << " ";
//		//cout << (*it2)++ << " "; 不能修改
//		++it2;
//	}
//	cout << endl;
//
//	// 反向迭代器
//	string::reverse_iterator it3 = s1.rbegin();
//	while (it3 != s1.rend()) {
//		cout << *it3 << " ";
//		++it3;
//	}
//	cout << endl;
//
//	// 3. 范围for 本质还是迭代器
//	for (auto e : s1) cout << e << " ";
//	cout << endl;
//	// 也能修改
//	for (auto e : s1) cout << e++ << " ";
//}
//
//void test_capacity_functions() {
//	string s1 = "hello C++";
//	// 返回字符串有效个数
//	cout << s1.size() << endl;
//	// 返回字符串的容量
//	cout << s1.capacity() << endl;
//	// 清空字符串，但不释放空间
//	s1.clear();
//	cout << "After clear,capacity:" << s1.capacity() << endl;
//	// 检查字符串是否为空
//	cout << s1.empty() << endl;
//
//	// 预留存储空间
//	string s2 = "abcdefghijk";
//	s2.reserve(50);
//	cout << "After reserve: " << s2.capacity() << endl;
//
//	// 缩减容量以匹配实际大小
//	s2.shrink_to_fit();
//	cout << "After shrink_to_fit: " << s2.capacity() << endl;
//
//	// 改变字符串大小
//	s2.resize(20, '!');
//	cout << "After resize: " << s2 << endl;
//	cout << "After resize, size: " << s2.size() << endl;
//	cout << "After resize, capacity: " << s2.capacity() << endl;
//}
//
//void test_element_access_funcitons() {
//	// 访问字符串
//	string s1 = "hello,string";
//	// 1.operator[] 
//	// char& operator[] (size_t pos); 可以修改返回对象
//	// const char& operator[] (size_t pos) const; 不能修改返回对象
//	for (size_t i = 0; i < s1.size(); i++)
//	{
//		cout << s1[i] << " ";
//	}
//	cout << endl;
//	// 可以修改
//	for (size_t i = 0; i < s1.size(); i++)
//	{
//		cout << s1[i]++ << " ";
//	}
//	cout << endl;
//
//	// 返回当前字符
//	for (size_t i = 0; i < s1.size(); i++)
//	{
//		cout << s1.at(i) << " ";
//	}
//	cout << endl;
//
//	// 返回最后一个字符
//	cout << s1.back() << endl;
//	// 返回第一个字符
//	cout << s1.front() << endl;
//
//}
//
//void test_modifiers_functions() {
//	// 字符串结尾追加一个字符，一个字符串，一个C类型字符串
//	string s1 = "hello vect";
//	string s2 = "yyyyy";
//	cout << s1 << endl << s2 << endl;
//	s1 += '!';
//	cout << s1 << endl;
//	s1 += "haha";
//	cout << s1 << endl;
//	s2 += s1;
//	cout << s2 << endl;
//
//	string s3 = "abc";
//	s3.append(s1);
//	cout << s3 << endl;
//	s3.append(s1, 4, 2);// (源字符串，开始索引，追加长度)
//	cout << s3 << endl;
//	s3.append("lalala", 4);// (源字符串，追加长度)
//	cout << s3 << endl;
//	s3.append("qiqiqi");
//	cout << s3 << endl;
//	s3.append(3, '.'); // "..."
//	cout << s3 << endl;
//	cout << endl;
//
//	// 尾插一个字符
//	s3.push_back('x');
//	cout << s3 << endl;
//	cout << endl;
//
//	// 指定索引位置插入
//	string s4 = "to be question";
//	string s5 = "the ";
//	string s6 = "or not to be";
//
//	string::iterator it;
//	cout << s4 << endl;
//	s4.insert(6, s5);
//	cout << s4 << endl;
//	s4.insert(6, s6, 3, 4);
//	cout << s4 << endl;
//	s4.insert(10, "that is cool", 8);
//	cout << s4 << endl;
//	s4.insert(10, "to be ");
//	cout << s4 << endl;
//	s4.insert(s4.end(), 3, '!');
//	cout << s4 << endl;
//	cout << endl;
//
//	// 删除字符
//	s4.erase(2, 6); // （开始删除索引，删除长度）
//	cout << s4 << endl;
//	s4.erase(s4.begin() + 2);
//	cout << s4 << endl;
//	s4.erase(s4.begin() + 1, s4.end() - 2);
//	cout << s4 << endl;
//	cout << endl;
//
//	// 替换
//	string str = "this is a test string";
//	string str2 = "n example";
//	string str3 = "sample phrase";
//	string str4 = "useful";
//
//	// 用索引
//	str.replace(9, 5, str2);          // "this is an example string." 
//	str.replace(19, 6, str3, 7, 6);     // "this is an example phrase." 
//	str.replace(8, 10, "just a");     // "this is just a phrase."     
//	str.replace(8, 6, "a shorty", 7);  // "this is a short phrase."    
//	str.replace(22, 1, 3, '!');        // "this is a short phrase!!!"  
//	cout << str << endl;
//
//	// 用迭代器
//	str.replace(str.begin(), str.end() - 3, str3);                    // "sample phrase!!!"     
//	str.replace(str.begin(), str.begin() + 6, "replace");             // "replace phrase!!!"     
//	str.replace(str.begin() + 8, str.begin() + 14, "is coolness", 7);    // "replace is cool!!!"   
//	str.replace(str.begin() + 12, str.end() - 4, 4, 'o');                // "replace is cooool!!!"  
//	str.replace(str.begin() + 11, str.end(), str4.begin(), str4.end());// "replace is useful."    
//	cout << str << endl;
//
//}
//int main() {
//	// test_member_functions();
//	// test_iterator_functions();
//	// test_capacity_functions();
//	// test_element_access_funcitons();
//	// test_modifiers_functions();
//	return 0;
//}

//#include "myString.h"
//void test_tra() {
//	myString s0("abcdefg");
//	// 1. 迭代器
//	myString::iterator it1 = s0.begin();
//	while (it1 != s0.end()) {
//		std::cout << *it1 << " ";
//		++it1;
//	}
//	std::cout << std::endl;
//	// 2.operator[]
//	for (size_t i = 0; i < s0.size(); i++)
//	{
//		std::cout << s0[i] << " ";
//	}
//	std::cout << std::endl;
//	// 可以修改
//	for (size_t i = 0; i < s0.size(); i++)
//	{
//		std::cout << s0[i]++ << " ";
//	}
//	std::cout << std::endl;
//	// 3. 范围for
//	for (auto e : s0) std::cout << e << " ";
//	std::cout << std::endl;
//}
//void test_capacity() {
//	myString s0("hello world");
//	std::cout << "before clear:" << std::endl;
//	std::cout << "capacity: "<< s0.capacity() << std::endl;
//	std::cout << "size: "<< s0.size() << std::endl;
//	std::cout << "empty? : "<< s0.empty() << std::endl;
//	// 清空
//	s0.clear();
//	std::cout << "after clear:" << std::endl;
//	std::cout << "capacity: " << s0.capacity() << std::endl;
//	std::cout << "size: " << s0.size() << std::endl;
//	std::cout << "empty? : " << s0.empty() << std::endl;
//
//	myString s1 = "abcdefg";
//	const char* substr = "cd";
//	std::cout << s1.find(2,'e') << std::endl;
//	std::cout << s1.find(2,"cd") << std::endl;
//}
//
//void test_insert() {
//	myString s0("hello world");
//	s0.push_back('!');
//	s0.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..");
//	s0 += "haha";
//	s0 += '1';
//	std::cout << s0.c_str() << std::endl;
//
//	myString s1("hello world");
//	myString s2("! C++"); 
//	s1.append(s2);
//	s1 += s2;
//	std::cout << s1.c_str() << std::endl;
//
//	myString s3("hello world");
//	//myString s0("hello world");
//	//s0.push_back('!');
//	//s0.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..");
//	//s0 += "haha";
//	//s0 += '1';
//	//std::cout << s0.c_str() << std::endl;
//
//	//myString s1("hello world");
//	//myString s2("! C++"); 
//	//s1.append(s2);
//	//s1 += s2;
//	//std::cout << s1.c_str() << std::endl;
//
//	/*myString s3("hello world");
//>>>>>>> d5512f6c3d7e2bb27f3fa8972f68534446007025
//	s3.erase(1, 2);
//	std::cout << s3.c_str() << std::endl;
//	myString s4("hello world");
//	s4.erase(1,30);
//<<<<<<< HEAD
//	std::cout << s4.c_str() << std::endl;
//=======
//	std::cout << s4.c_str() << std::endl;*/
//
//	myString s5("xxxxxxx");
//	s5.insert(0, 'p');
//	std::cout << s5.c_str() << std::endl;
//	s5.insert(0, "qqqq");
//	myString s6("123");
//	s5.insert(0, s6);
//	std::cout << s5.c_str() << std::endl;
//
//}
//
//void test_compare() {
//	myString s0 = "abc";
//	myString s1 = "cdefg";
//	std::cout << (s0 > s1)<< std::endl;
//	std::cout << (s0 >= s1)<< std::endl;
//	std::cout << (s0 < s1)<< std::endl;
//	std::cout << (s0 <= s1)<< std::endl;
//	std::cout << (s0 == s1)<< std::endl;
//	std::cout << (s0 != s1)<< std::endl;
//}
//
//void test_stream() {
//	myString s0 = "123456";
//	cout << s0 << endl;
//	myString s1;
//	cin >> s1;
//	cout << s1;
//}
//int main() {
//	// test_tra();
//	// test_capacity();
//	// test_insert();
//	/*test_compare();*/
//	test_stream();
//	return 0;
//}

