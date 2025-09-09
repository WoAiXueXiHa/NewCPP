#include "myString.h"

myString::myString(const char* str)
	:_size(strlen(str))
{
	// 多一个空间存'\0'
	_str = new char[_size + 1];
	_capacity = _size;
	// 拷贝到_str
	strcpy(_str, str);
}

myString::~myString() {
	delete[] _str;
	_str = nullptr;
	_capacity = _size = 0;
}

char* myString::c_str() const{
	return _str;
}
// 容量操作
size_t myString::size() const {
	return _size;
}
size_t myString::capacity() const {
	return _capacity;
}
void myString::clear() {
	delete[] _str;
	_str = nullptr;
	_size = 0;
}
bool myString::empty() const {
	return _size == 0;
}

// 正向
// 可修改
myString::iterator myString::begin() {
	return _str;
}
myString::iterator myString::end() {
	return _str + _size;
}

// 不可修改
myString::const_iterator myString::begin() const {
	return _str;
}
myString::const_iterator myString::end() const {
	return _str + _size;
}

const char& myString::operator[](size_t pos) const {
	assert(pos < _size);
	return _str[pos];
}
char& myString::operator[](size_t pos) {
	assert(pos < _size);
	return _str[pos];
}

void  myString::reserve(size_t new_capacity) {
	if (new_capacity > _capacity) {
		char* tmp = new char[new_capacity + 1];
		strcpy(tmp, _str);
		delete[] _str;

		_str = tmp;
		_capacity = new_capacity;
	}
}
void  myString::resize(size_t new_size) {

}

// 修改操作
void  myString::push_back(const char ch) {
	// 扩容
	size_t new_capacity = _capacity == 0 ? 4 : 2 * _capacity;
	reserve(new_capacity);

	// 插入
	_str[_size] = ch;
	_str[_size + 1] = '\0';
	++_size;
}
void  myString::append(const char* str) {
	// 扩容
	size_t len = strlen(_str);
	if (len + _size > _capacity) reserve(len + _size);

	// 插入
	// 原来字符串结尾开始插入
	strcpy(_str + _size, str);
	_size += len;
}
myString& myString::operator+=(const char* str) {
	append(str);
	return *this;
}

myString& myString::operator+=(const char ch) {
	push_back(ch);
	return *this;
}

void  myString::erase() {

}
void  myString::insert(size_t pos, const char ch) {

}
void  myString::insert(size_t pos, const char* str) {

}
void  myString::insert(size_t pos, const myString& str) {

}