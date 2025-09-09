#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cassert>

class myString {
private:
	char* _str = nullptr;
	size_t _size;
	size_t _capacity;

public:
	// ����
	myString(const char* str = "");
	// ��������
	myString(const myString& str);
	// ����
	~myString();

	// ����C��ʽ�ַ���
	char* c_str() const;

	// ������
	typedef  char* iterator;
	typedef  char* const_iterator;
	// ����
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	// ����
	iterator rbegin();
	iterator rend();
	const_iterator rbegin() const;
	const_iterator rend() const;

	// ��������
	size_t size() const;
	size_t capacity() const;
	void clear();
	bool empty() const;

	void reserve(size_t size);
	void resize(size_t new_size);

	// �޸Ĳ���
	void push_back(const char ch);
	void append(const char* str);
	void append(const myString& str);
	void erase();
	void insert(size_t pos, const char ch);
	void insert(size_t pos, const char* str);
	void insert(size_t pos, const myString& str);

	// ���������
	const char& operator[](size_t pos) const;
	char& operator[](size_t pos);
	myString& operator+=(const char* str);
	myString& operator+=(const char ch);

	bool operator>(const myString& str) const;
	bool operator>=(const myString& str) const;
	bool operator<(const myString& str) const;
	bool operator<=(const myString& str) const;
	bool operator==(const myString& str) const;
	bool operator!=(const myString& str) const;
};