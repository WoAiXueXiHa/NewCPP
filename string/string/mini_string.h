#include <iostream>
#include <cassert>
using namespace std;

// 基本定义 
class mini_string {
private:
	char* _data; // 字符数据
	size_t _size;// 实际字符数
	size_t _capacity; // 容量 不含'\0'
public:
	static const size_t npos;
	// ======= 构造&析构 ========
	mini_string(); // 默认构造
	mini_string(const char* str); // 用C格式字符串构造
	mini_string(const mini_string& str); // 拷贝构造
	~mini_string(); // 析构

	// ======= 赋值操作 ========
	mini_string& operator=(const mini_string& str);

	// ======= 元素访问 ========
	char& operator[](size_t i) { return _data[i]; } // 可以修改
	const char& operator[](size_t i) const { return _data[i]; } // 不能修改
	char& at(size_t i);
	char& front() { return _data[0]; } // 字符串首位索引
	char& back() { return _data[_size - 1]; } // 字符串末尾索引
	const char* c_str() const { return _data; } // 返回C格式字符串

	// ======= 容量操作 ========
	size_t size() const { return _size; }
	size_t capacity() const { return _capacity; }
	void clear() { _size = 0,_data[0] = '\0'; }
	bool empty() const { return _size == 0; }

	void reserve(size_t new_cap);
	void shrink_to_fit();

	// ======= 查找操作 ========
	size_t find(const char target_char) const; // 查找字符串中有无目标字符
	size_t find(const char* target_str) const; // 查找字符串中有无目标字符串
	mini_string substr(size_t pos, size_t len) const; // 截取子串

	// ======= 修改操作 ========
	void push_back(const char ch); // 尾插
	mini_string& append(const char* str); // 结尾追加一个C格式字符串
	mini_string& append(const mini_string& str); // 结尾追加一个mini_string类字符串
	void erase(size_t pos, size_t len); //从pos位置开始删除len个长度字符
	void insert(size_t pos, const char ch);// 在pos位置之后插入一个字符
	void insert(size_t pos, const char* str);// 在pos位置之后插入一个字符串
	mini_string& operator+=(const mini_string& str);  // 针对mini_string对象
	mini_string& operator+=(const char* str);         // 针对C风格字符串
	mini_string& operator+=(const char ch);                 // 针对单个字符

	// ======= 迭代器 ========
	typedef char* iterator;
	typedef char* const_iterator;

	iterator begin() { return _data; }
	iterator end() { return _data + _size; }
	/*const_iterator begin(){ return _data; }
	const_iterator  end() { return _data + _size; }*/

	// ======= 运算符重载 =========
	bool operator==(const mini_string& str) const { return strcmp(_data, str._data) == 0; }
	bool operator!=(const mini_string& str) const { return !(*this == str._data); }
	bool operator>(const mini_string& str) const { return !(*this <= str._data); }
	bool operator>=(const mini_string& str) const { return !(*this < str._data); }
	bool operator<(const mini_string& str) const { return strcmp(_data, str._data) < 0; }
	bool operator<=(const mini_string& str) const { return *this < str._data || *this == str._data; }
};

// ======= 流操作 =========
istream& operator>>(istream& is,  mini_string& str);
ostream& operator<<(ostream& os, const mini_string& str);
