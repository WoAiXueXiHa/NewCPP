#include "myString.h"
const size_t myString::npos = -1;

myString::myString(const char* str)
	:_size(strlen(str))
{
	// 多一个空间存'\0'
	_str = new char[_size + 1];
	_capacity = _size;
	// 拷贝到_str
	strcpy(_str, str);
}
myString::myString(const myString& str) {
	char* tmp = new char[str.capacity() + 1];
	_str = tmp;
	_capacity = str.capacity();
	_size = str.size();

	delete[] tmp;
	tmp = nullptr;
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
	_str[0] = '\0';
	_size = 0;
}
bool myString::empty() const {
	return _size == 0;
}

size_t myString::find(size_t pos, const char ch) const {
	// 检查起始位置是否有效
	if (pos >= _size) {
		return npos;
	}

	// 从pos位置开始查找字符ch
	for (size_t i = pos; i < _size; i++) {
		if (_str[i] == ch) {
			return i;  // 找到返回索引
		}
	}
	return npos;  // 未找到返回npos
}

size_t myString::find(size_t pos, const char* str) const {
	// 检查参数有效性
	if (pos >= _size || str == nullptr || *str == '\0') {
		return npos;
	}

	// 使用strstr查找子字符串
	char* p = strstr(_str + pos, str);
	if (p != nullptr) {
		return p - _str;  // 找到返回起始索引
	}
	return npos;  // 未找到返回npos
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
	size_t len = strlen(str);
	if (len + _size > _capacity) reserve(len + _size);

	// 插入
	// 原来字符串结尾开始插入
	strcpy(_str + _size, str);
	_size += len;
}
void myString::append(const myString& str) {
	size_t len = str.size();
	if (len + _size > _capacity) reserve(len + _size);
	// 插入
	// 原来字符串结尾开始插入
	strcpy(_str + _size, str.c_str());
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
myString& myString::operator+=(const myString& str) {
	append(str);
	return *this;
}


void myString::erase(size_t pos, size_t len) {
	// 暴力检查
	assert(pos <= _size);

	// 如果删除长度足够大，直接截断
	if (len >= _size - pos) {
		_str[pos] = '\0';
		_size = pos;
	}
	// 否则需要挪动数据
	else {
		// 保存原始pos值，用新变量i进行迭代
		size_t i = pos;
		// 循环条件：当还没复制到原字符串结尾时继续
		while (i + len < _size) {
			_str[i] = _str[i + len];
			++i;
		}
		// 添加字符串结束符
		_str[_size - len] = '\0';
		// 更新字符串长度
		_size -= len;
	}
}
// 在pos位置之后插入字符
void  myString::insert(size_t pos, const char ch) {
	// 暴力检查
	assert(pos <= _size);
	
	// 扩容
	size_t new_capacity = _capacity == 0 ? 4 : 2 * _capacity;
	reserve(new_capacity);

	size_t end = _size + 1;
	while (end > pos) {
		_str[end + 1] = _str[end];
		--end;
	}
	_str[pos] = ch;
	++_size;
}

void  myString::insert(size_t pos, const char* str) {
	// 暴力检查
	assert(pos <= _size);
	// 扩容
	size_t len = strlen(str);
	if (len + _size > _capacity) reserve(len + _size);

	size_t end = _size + len;
	while (end > pos) {
		_str[end] = _str[end - len];
		--end;
	}
	memcpy(_str + pos, str, len);
	_size += len;

}
void  myString::insert(size_t pos, const myString& str) {
	// 暴力检查
	assert(pos <= _size);
	// 扩容
	size_t len = str.size();
	if (len + _size > _capacity) reserve(len + _size);

	size_t end = _size + len;
	while (end > pos) {
		_str[end] = _str[end - len];
		--end;
	}
	memcpy(_str + pos, str.c_str(), len);
	_size += len;
}

bool myString::operator>(const myString& str) const {
<<<<<<< HEAD
	return !(*this <= str.c_str());
}
bool myString::operator>=(const myString& str) const {
	return !(*this < str.c_str());
=======
	return !(*this <= str);
}
bool myString::operator>=(const myString& str) const {
	return !(*this < str);
>>>>>>> d5512f6c3d7e2bb27f3fa8972f68534446007025
}
bool myString::operator<(const myString& str) const {
	return strcmp(_str,str.c_str()) < 0;
}
bool myString::operator<=(const myString& str) const {
<<<<<<< HEAD
	return *this < str.c_str() || *this == str.c_str();
=======
	return *this < str || *this == str;
>>>>>>> d5512f6c3d7e2bb27f3fa8972f68534446007025
}
bool myString::operator==(const myString& str) const {
	return strcmp(_str, str.c_str()) == 0;
}
bool myString::operator!=(const myString& str) const {
<<<<<<< HEAD
	return !(*this == str.c_str());
}


ostream& operator<<(std::ostream& os, const myString& str) {
	for (size_t i = 0; i < str.size(); i++)
	{
		os << str[i];
	}
	return os;
}
istream& operator>>(istream& is, myString& str) {
	str.clear();
	char ch = is.get();
	while (ch != ' ' && ch != '\n') {
		str += ch;
		ch = is.get();
	}

	return is;
=======
	return !(*this == str);
>>>>>>> d5512f6c3d7e2bb27f3fa8972f68534446007025
}