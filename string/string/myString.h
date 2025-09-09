#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cassert>

class myString {
private:
	char* _str = nullptr;
	size_t _size;
	size_t _capacity;

public:
	// 构造
	myString(const char* str = "");
	// 拷贝构造
	myString(const myString& str);
	// 析构
	~myString();

	// 返回C格式字符串
	char* c_str() const;

	// 迭代器
	typedef  char* iterator;
	typedef  char* const_iterator;
	// 正向
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	// 容量操作
	size_t size() const;
	size_t capacity() const;
	void clear();
	bool empty() const;

	void reserve(size_t size);
	void resize(size_t new_size);

	// 修改操作
	void push_back(const char ch);
	void append(const char* str);
	void append(const myString& str);
	void erase(size_t pos, size_t len);
	void insert(size_t pos, const char ch);
	void insert(size_t pos, const char* str);
	void insert(size_t pos, const myString& str);

	// 运算符重载
	const char& operator[](size_t pos) const;
	char& operator[](size_t pos);
	myString& operator+=(const char* str);
	myString& operator+=(const char ch);
	myString& operator+=(const myString& str);

	bool operator>(const myString& str) const;
	bool operator>=(const myString& str) const;
	bool operator<(const myString& str) const;
	bool operator<=(const myString& str) const;
	bool operator==(const myString& str) const;
	bool operator!=(const myString& str) const;
};