#include <iostream>
#include <cassert>
using namespace std;

// �������� 
class mini_string {
private:
	char* _data; // �ַ�����
	size_t _size;// ʵ���ַ���
	size_t _capacity; // ���� ����'\0'
public:
	static const size_t npos;
	// ======= ����&���� ========
	mini_string(); // Ĭ�Ϲ���
	mini_string(const char* str); // ��C��ʽ�ַ�������
	mini_string(const mini_string& str); // ��������
	~mini_string(); // ����

	// ======= ��ֵ���� ========
	mini_string& operator=(const mini_string& str);

	// ======= Ԫ�ط��� ========
	char& operator[](size_t i) { return _data[i]; } // �����޸�
	const char& operator[](size_t i) const { return _data[i]; } // �����޸�
	char& at(size_t i);
	char& front() { return _data[0]; } // �ַ�����λ����
	char& back() { return _data[_size - 1]; } // �ַ���ĩβ����
	const char* c_str() const { return _data; } // ����C��ʽ�ַ���

	// ======= �������� ========
	size_t size() const { return _size; }
	size_t capacity() const { return _capacity; }
	void clear() { _size = 0,_data[0] = '\0'; }
	bool empty() const { return _size == 0; }

	void reserve(size_t new_cap);
	void shrink_to_fit();

	// ======= ���Ҳ��� ========
	size_t find(const char target_char) const; // �����ַ���������Ŀ���ַ�
	size_t find(const char* target_str) const; // �����ַ���������Ŀ���ַ���
	mini_string substr(size_t pos, size_t len) const; // ��ȡ�Ӵ�

	// ======= �޸Ĳ��� ========
	void push_back(const char ch); // β��
	mini_string& append(const char* str); // ��β׷��һ��C��ʽ�ַ���
	mini_string& append(const mini_string& str); // ��β׷��һ��mini_string���ַ���
	void erase(size_t pos, size_t len); //��posλ�ÿ�ʼɾ��len�������ַ�
	void insert(size_t pos, const char ch);// ��posλ��֮�����һ���ַ�
	void insert(size_t pos, const char* str);// ��posλ��֮�����һ���ַ���
	mini_string& operator+=(const mini_string& str);  // ���mini_string����
	mini_string& operator+=(const char* str);         // ���C����ַ���
	mini_string& operator+=(const char ch);                 // ��Ե����ַ�

	// ======= ������ ========
	typedef char* iterator;
	typedef char* const_iterator;

	iterator begin() { return _data; }
	iterator end() { return _data + _size; }
	/*const_iterator begin(){ return _data; }
	const_iterator  end() { return _data + _size; }*/

	// ======= ��������� =========
	bool operator==(const mini_string& str) const { return strcmp(_data, str._data) == 0; }
	bool operator!=(const mini_string& str) const { return !(*this == str._data); }
	bool operator>(const mini_string& str) const { return !(*this <= str._data); }
	bool operator>=(const mini_string& str) const { return !(*this < str._data); }
	bool operator<(const mini_string& str) const { return strcmp(_data, str._data) < 0; }
	bool operator<=(const mini_string& str) const { return *this < str._data || *this == str._data; }
};

// ======= ������ =========
istream& operator>>(istream& is,  mini_string& str);
ostream& operator<<(ostream& os, const mini_string& str);
