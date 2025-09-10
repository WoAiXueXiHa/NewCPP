#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cassert>
using namespace std;
class myString {
private:
	char* _str = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
	static const size_t npos;
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

	// ��������
	size_t size() const;
	size_t capacity() const;
	void clear();
	bool empty() const;

	void reserve(size_t size);
	size_t find(size_t pos, const char ch) const;
	size_t find(size_t pos, const char* str) const;

	// �޸Ĳ���
	void push_back(const char ch);
	void append(const char* str);
	void append(const myString& str);
	void erase(size_t pos, size_t len);
	void insert(size_t pos, const char ch);
	void insert(size_t pos, const char* str);
	void insert(size_t pos, const myString& str);

	// ���������
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

std::ostream& operator<<(std::ostream& os, const myString& str);
std::istream& operator>>(std::istream& os, myString& str);