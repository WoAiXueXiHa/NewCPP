#include "mini_string.h"
const size_t mini_string::npos = -1;
// ======= ����&���� ========
// Ĭ�Ϲ��죺���� 1 �ֽڣ���� '\0'
mini_string::mini_string()
    : _data(new char[1])
    , _size(0)
    , _capacity(1)
{
    _data[0] = '\0';
}

// �� C �ַ�������
mini_string::mini_string(const char* s) {
    _size = strlen(s);
    _capacity = _size + 1;
    _data = new char[_capacity];
    // ����s��_data
    memcpy(_data, s, _capacity);
}

// �������죺���
mini_string::mini_string(const mini_string& str) {
    _size = str._size;
    _capacity = str._capacity;
    _data = new char[_capacity];
    memcpy(_data, str._data, _capacity);
}

// ����������ͳһ�ͷ�
mini_string::~mini_string() {
    delete[] _data;
    _data = nullptr;
    _size = _capacity = 0;
}

// ======= Ԫ�ط��� ========
// ����ָ��λ�õ��ַ�
char& mini_string::at(size_t i) {
    if (i >= _size) throw std::out_of_range("index out of range");
    return _data[i];
}

// ======= ��ֵ���� ========
mini_string& mini_string::operator=(const mini_string& str) {
    // ��ֹ�Ը�ֵ
    if (this != &str) {
        delete[] _data;
        _size = str._size;
        _capacity = str._capacity;
        _data = new char[_capacity];

        memcpy(_data, str._data, _capacity);
    }
    return *this;
}

// ======= �������� ========
void mini_string::reserve(size_t new_cap) {
    // ֻ�д��ݵ����������������
    if (new_cap > _capacity) {
        // ��һ���������Ŀռ� �ͷžɿռ� ָ���¿ռ�
        char* tmp = new char[new_cap];
        memcpy(tmp, _data, _size + 1);
        delete[] _data;
        _data = tmp;
        _capacity = new_cap;
    }
}
// ��С����
void mini_string::shrink_to_fit() {
    // ���1��Ϊ�˶��'\0'
    if (_capacity > _size + 1 ) {
        // ��һ���������Ŀռ� �ͷžɿռ� ָ���¿ռ�
        char* tmp = new char[_size + 1];
        memcpy(tmp, _data, _size + 1);
        delete[] _data;
        _data = tmp;
        _capacity = _size + 1;
    }
}

// ======= �޸Ĳ��� ========

void  mini_string::erase(size_t pos, size_t len) {
    // �߽���
    assert(pos <= _size);
    // ���pos��ĩβ�����ò���
    if (pos == _size) return;
    // ���len�㹻�� �ж���ɾ����
    if (len > _size - pos) {
        _data[pos] = '\0';
        _size = pos;
    }
    else {
    // ����ʵʵŲ��
        size_t i = pos + len;        
        while (i < _size) {
            _data[i - len] = _data[i];
            ++i;
        }
        _size -= len;
    }
    _data[_size] = '\0';// һ����Ҫ�����ַ�����β
}
void  mini_string::insert(size_t pos, const char ch) {
    // �߽���
    assert(pos <= _size);
    // ������
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
    ++_size;            // �ȸ��³���
    _data[_size] = '\0';// ��β��λ��Ϊ�µ�_size
}

void  mini_string::insert(size_t pos, const char* str) {
    // �߽���
    assert(pos <= _size);
    size_t len = strlen(str);
    if (_size + len + 1 > _capacity) reserve(_size + len + 1);
    
    // �� [pos, _size) ������ַ�����ƶ� len λ
    size_t i = _size;
    while (i > pos) {
        _data[i + len - 1] = _data[i -1];
        --i;
    }
    // ��Ŀ���ַ���������posλ�ÿ�ʼ����
    memcpy(_data + pos, str, len);
    _data[_size + len] = '\0';
    _size += len;
}

void  mini_string::push_back(const char ch) {
    // ������
    if (_size + 1 >= _capacity) {
        size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
        reserve(new_cap);
    }

    _data[_size] = ch;  // �������ַ�
    ++_size;            // �ȸ��³���
    _data[_size] = '\0';// ��ʱ_size��+1
}

mini_string& mini_string::append(const char* str) {
    size_t len = strlen(str);
    if (_size + len + 1 > _capacity) reserve(_size + len + 1);

    memcpy(_data + _size, str, len);
    _size += len;
    _data[_size] = '\0';

    return *this; // ���ص�ǰ��������ã��޿���
}

mini_string& mini_string::append(const mini_string& str) {
    size_t len = str.size();
    if (_size + len + 1 > _capacity) reserve(_size + len + 1);

    memcpy(_data + _size, str.c_str(), len);
    _size += len;
    _data[_size] = '\0';

    return *this; // ���ص�ǰ��������ã����ǿ���
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
// ======= ���Ҳ��� ========
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
    // Խ���ж�
    assert(pos < _size);

    // ����ʵ�ʳ��ȣ����ܳ���ʣ���ַ���
    if (pos + len > _size) {
        len = _size - pos;
    }

    // �����еĹ��캯������ɿ���
    mini_string result;
    result.reserve(len + 1);   // ��ǰ�����ڴ棬����������
    for (size_t i = 0; i < len; ++i) {
        result.push_back(_data[pos + i]);
    }

    return result;
}

// ======= ������ =========
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

    // ����ǰ���ո�
    while (is.get(ch) && (ch == ' ' || ch == '\n')) {
        // ʲô������
    }

    if (!is) return is;

    // ��ȡ���ʣ�ֱ���ո����
    do {
        str.push_back(ch);
    } while (is.get(ch) && ch != ' ' && ch != '\n');

    return is;
}
