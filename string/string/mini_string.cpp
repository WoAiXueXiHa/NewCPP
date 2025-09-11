#include "mini_string.h"
const size_t mini_string::npos = -1;
// ======= 构造&析构 ========
// 默认构造：分配 1 字节，存放 '\0'
mini_string::mini_string()
    : _data(new char[1])
    , _size(0)
    , _capacity(1)
{
    _data[0] = '\0';
}

// 用 C 字符串构造
mini_string::mini_string(const char* s) {
    _size = strlen(s);
    _capacity = _size + 1;
    _data = new char[_capacity];
    // 拷贝s到_data
    memcpy(_data, s, _capacity);
}

// 拷贝构造：深拷贝
mini_string::mini_string(const mini_string& str) {
    _size = str._size;
    _capacity = str._capacity;
    _data = new char[_capacity];
    memcpy(_data, str._data, _capacity);
}

// 析构函数：统一释放
mini_string::~mini_string() {
    delete[] _data;
    _data = nullptr;
    _size = _capacity = 0;
}

// ======= 元素访问 ========
// 访问指定位置的字符
char& mini_string::at(size_t i) {
    if (i >= _size) throw std::out_of_range("index out of range");
    return _data[i];
}

// ======= 赋值操作 ========
mini_string& mini_string::operator=(const mini_string& str) {
    // 防止自赋值
    if (this != &str) {
        delete[] _data;
        _size = str._size;
        _capacity = str._capacity;
        _data = new char[_capacity];

        memcpy(_data, str._data, _capacity);
    }
    return *this;
}

// ======= 容量操作 ========
void mini_string::reserve(size_t new_cap) {
    // 只有传递的新容量够大才扩容
    if (new_cap > _capacity) {
        // 开一个新容量的空间 释放旧空间 指向新空间
        char* tmp = new char[new_cap];
        memcpy(tmp, _data, _size + 1);
        delete[] _data;
        _data = tmp;
        _capacity = new_cap;
    }
}
// 缩小容量
void mini_string::shrink_to_fit() {
    // 这个1是为了多存'\0'
    if (_capacity > _size + 1 ) {
        // 开一个新容量的空间 释放旧空间 指向新空间
        char* tmp = new char[_size + 1];
        memcpy(tmp, _data, _size + 1);
        delete[] _data;
        _data = tmp;
        _capacity = _size + 1;
    }
}

// ======= 修改操作 ========

void  mini_string::erase(size_t pos, size_t len) {
    // 边界检查
    assert(pos <= _size);
    // 如果pos在末尾，不用操作
    if (pos == _size) return;
    // 如果len足够长 有多少删多少
    if (len > _size - pos) {
        _data[pos] = '\0';
        _size = pos;
    }
    else {
    // 老老实实挪动
        size_t i = pos + len;        
        while (i < _size) {
            _data[i - len] = _data[i];
            ++i;
        }
        _size -= len;
    }
    _data[_size] = '\0';// 一定不要忘了字符串结尾
}
void  mini_string::insert(size_t pos, const char ch) {
    // 边界检查
    assert(pos <= _size);
    // 先扩容
    if (_size + 1 >= _capacity) {
        size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
        reserve(new_cap);
    }

    size_t i = _size; 
    while (i > pos) {
        _data[i] = _data[i - 1];
        --i;
    }
    _data[pos] = ch;
    ++_size;            // 先更新长度
    _data[_size] = '\0';// 结尾符位置为新的_size
}

void  mini_string::insert(size_t pos, const char* str) {
    // 边界检查
    assert(pos <= _size);
    size_t len = strlen(str);
    if (_size + len + 1 > _capacity) reserve(_size + len + 1);
    
    // 将 [pos, _size) 区间的字符向后移动 len 位
    size_t i = _size;
    while (i > pos) {
        _data[i + len - 1] = _data[i -1];
        --i;
    }
    // 把目标字符串拷贝从pos位置开始拷贝
    memcpy(_data + pos, str, len);
    _data[_size + len] = '\0';
    _size += len;
}

void  mini_string::push_back(const char ch) {
    // 先扩容
    if (_size + 1 >= _capacity) {
        size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
        reserve(new_cap);
    }

    _data[_size] = ch;  // 插入新字符
    ++_size;            // 先更新长度
    _data[_size] = '\0';// 此时_size已+1
}

mini_string& mini_string::append(const char* str) {
    size_t len = strlen(str);
    if (_size + len + 1 > _capacity) reserve(_size + len + 1);

    memcpy(_data + _size, str, len);
    _size += len;
    _data[_size] = '\0';

    return *this; // 返回当前对象的引用，无拷贝
}

mini_string& mini_string::append(const mini_string& str) {
    size_t len = str.size();
    if (_size + len + 1 > _capacity) reserve(_size + len + 1);

    memcpy(_data + _size, str.c_str(), len);
    _size += len;
    _data[_size] = '\0';

    return *this; // 返回当前对象的引用，而非拷贝
}

mini_string& mini_string::operator+=(const char ch) {
    push_back(ch);
    return *this;
}
mini_string& mini_string::operator+=(const char* str) {
    append(str);
    return *this;
}
mini_string& mini_string::operator+=(const mini_string& str) {
    append(str);
    return *this;
}
// ======= 查找操作 ========
size_t mini_string::find(const char target_char) const {
    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] == target_char) return i;
    }
    return npos;
}
size_t mini_string::find(const char* target_str) const {
    size_t len = strlen(target_str);
    if (len == 0) return 0;
    for (size_t i = 0; i + len <= _size; ++i) {
        if (strncmp(_data + i, target_str, len) == 0) return i;
    }
    return npos;
}

mini_string mini_string::substr(size_t pos, size_t len) const {
    // 越界判断
    assert(pos < _size);

    // 计算实际长度：不能超过剩余字符数
    if (pos + len > _size) {
        len = _size - pos;
    }

    // 用已有的构造函数来完成拷贝
    mini_string result;
    result.reserve(len + 1);   // 提前分配内存，避免多次扩容
    for (size_t i = 0; i < len; ++i) {
        result.push_back(_data[pos + i]);
    }

    return result;
}

// ======= 流操作 =========
ostream& operator<<(std::ostream& os, const mini_string& str) {
    for (size_t i = 0; i < str.size(); i++)
    {
        os << str[i];
    }
    return os;
}
istream& operator>>(istream& is, mini_string& str) {
    str.clear();
    char ch;

    // 跳过前导空格
    while (is.get(ch) && (ch == ' ' || ch == '\n')) {
        // 什么都不做
    }

    if (!is) return is;

    // 读取单词，直到空格或换行
    do {
        str.push_back(ch);
    } while (is.get(ch) && ch != ' ' && ch != '\n');

    return is;
}
