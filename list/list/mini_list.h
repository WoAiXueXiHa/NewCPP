#include <iostream>
#include <cassert>
#include <cstdbool>
#include <initializer_list>
using namespace std;

namespace Vect {
	// �ڵ��� �������Ƶ�����ʽڵ� ���Խ��ڵ����Ա����
	template <class T>
	struct list_node {

		list_node<T>* _prev; // ��¼ǰ���ڵ�ĵ�ַ
		list_node<T>* _next; // ��¼��̽ڵ�ĵ�ַ

		T _data; // �ýڵ�洢������

		// Ĭ�Ϲ���
		list_node(const T& input_val = T())
			:_prev(nullptr)
			,_next(nullptr)
			,_data(input_val)
		{ }
	};

	// --------- ������ģ�� (����ʵ�� iterator / const_iterator) ---------
	// ģ�����:
	// T   : �ڵ��д�ŵ���������
	// Ref : operator* �ķ������� (T& �� const T&)
	// Ptr : operator-> �ķ������� (T* �� const T*)
	//
	// ������һ��ģ����ʵ���˿�д��������ֻ��������������Ϊ�������ظ����룩��

	template <class T, class ref, class ptr>
	struct list_iterator {
		typedef list_node<T> Node;
		typedef list_iterator<T, ref, ptr> self; // ������������ ����д

		Node* _node; // ָ��ǰ�ڵ㣨�� end() �����ָ���ڱ� _head��

		// ����
		list_iterator(Node* node = nullptr)
			:_node(node)
		{ }

		// ��������� ���ⲿ�κ�����ʹ��iterator�ķ�ʽͳһ

		// ǰ��++ �ƶ�����һ���ڵ� ������������ �������޸� ������ֵ ��ֻ���޸ĸ��� �������ڽ���ֵ��û��
		self& operator++() {
			_node = _node->_next;
			return *this;
		}

		// ǰ��-- �ƶ���ǰһ���ڵ�
		self& operator--() {
			_node = _node->_prev;
			return *this;
		}

		// ����++ ���ؾ�ֵ �Լ������ƶ�һλ
		self operator++(int) {
			self tmp = *this;
			_node = _node->_next;
			return tmp;
		}

		// ����-- ���ؾ�ֵ �Լ���ǰ�ƶ�һλ
		self operator--(int) {
			self tmp = *this;
			_node = _node->_prev;
			return tmp;
		}

		// * ������ ���� ref�������� T& �� const T&��
		ref operator*()  {
			// ��Ҫ���ڱ�λ������
			assert(_node);
			return _node->_data;
		}

		// -> ָ����ʳ�Ա ����ptr��T* �� const T*��
		ptr operator->() {
			assert(_node);
			return &_node->_data; // ȡ��ַ
		}

		// != ==����
		bool operator==(const self& other) const {
			return _node == other._node;
		}

		bool operator!=(const self& other) const {
			return _node != other._node;
		}
	};
	
	// ������ ���ڱ�λ������������
	template <class T>
	class mini_list {
	public:
		typedef list_node<T> Node;
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); } // �ڱ�λ����β

		const_iterator begin() const { return const_iterator(_head->_next); }
		const_iterator end() const { return const_iterator(_head); }


		// ���������
		void empty_list() {
			// newһ���ڱ�λ
			_head = new Node(); // ���洢��Чֵ Ĭ��T()
			_head->_next = _head;
			_head->_prev = _head;
		}
		mini_list() { empty_list(); }

		mini_list(initializer_list<T> il) {
			empty_list();
			for (const auto& e : il) push_back(e);
		}
		// ����n��ֵ��ͬ�Ľڵ�
		mini_list(size_t n, const T& val) {
			empty_list();
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// ��������
		mini_list(const mini_list<T>& other) {
			empty_list();
			for (const auto& e : other) push_back(e);
		}

		// ��ֵ���������
		mini_list<T>& operator=(mini_list<T> other) {
			// ����ָ��
			std::swap(_head, other._head);
			return *this;
		}
		// �������ͷ����нڵ����ڱ�
		~mini_list() {
			if (_head) {
				clear();
				delete _head;
				_head = nullptr;
			}
		}

		// posǰ�����½ڵ�
		iterator insert(iterator pos, const T& input_val) {
			Node* cur = pos._node;
			Node* new_node = new Node(input_val);
			Node* prev = cur->_prev;

			// ���� prev <-> newnode <-> cur
			new_node->_prev = prev;
			new_node->_next = cur;
			prev->_next = new_node;
			cur->_prev = new_node;

			return iterator(new_node);
		}

		// �ڵ� pos ��λ��ǰ���� val��pos �� 0 ��ʼ��
		iterator insert(size_t pos, const T& val) {
			auto it = begin();
			for (size_t i = 0; i < pos && it != end(); ++i) {
				++it;
			}
			return insert(it, val); // ����ԭ���� iterator �汾
		}

		// ɾ��posλ�ýڵ� ����ָ��ɾ�ڵ��̵ĵ�����
		iterator erase(iterator pos) {
			// ����ɾ���ڱ�λ
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = cur->_next;
			next->_prev = cur->_prev;

			delete cur;

			return iterator(next);
		}

		// ɾ��pos�����Ľڵ㣨pos �� 0 ��ʼ��
		iterator erase(size_t pos) {
			auto it = begin();
			for (size_t i = 0; i < pos && it != end(); ++i) {
				++it;
			}
			return erase(it); 
		}
		// β��
		void push_back(const T& input_val) { insert(end(), input_val); }
		// ͷ��
		void push_front(const T& input_val) {
			insert(begin(), input_val); 
		}
		// βɾ
		void pop_back() { 
			assert(_head->_next != _head);  
			// ɾ�����һ����Ч�ڵ� -> --end() ָ�����һ���ڵ�
			erase(--end());
		}
		// ͷɾ
		void pop_front() { 
			assert(_head->_next != _head);  
			erase(begin()); 
		}

		// �������
		void clear(){
			auto it = begin();
			while (it != end()) {
				it = erase(it); // ������һ����Ч������
			}
		}
		// �п�
		bool empty() { return _head->_next == _head; }

		// ��ӡ���������ٶ� T �������
		void debug_print(const char* sep = " ") const {
			for (auto it = begin(); it != end(); ++it) {
				std::cout << *it << sep;
			}
			std::cout << "\n";
		}
	private:
		Node* _head;
	};

	void test_insert_and_erase() {
		mini_list<int> list;
		cout << "==== ���� mini_list ����ɾ������ ====" << endl;
		list.push_back(1);
		list.push_back(11);
		list.push_back(1111);
		list.push_back(11111);
		list.debug_print();

		cout << "ͷ���" << endl;
		list.push_front(2);
		list.push_front(22);
		list.push_front(222);
		list.push_front(2222);
		list.debug_print();

		cout << "������Ϊ3��λ�ò���100��" << endl;
		list.insert(3, 100);
		list.debug_print();

		cout << "βɾ��" << endl;
		list.pop_back();
		list.debug_print();

		cout << "ͷɾ��" << endl;
		list.pop_front();
		list.debug_print();

		cout << "ɾ������Ϊ2�Ľڵ�" << endl;
		list.erase(2);
		list.debug_print();
	}

	void test_constructor() {
		cout << "==== ���� mini_list ���� ====" << endl;

		mini_list<int> lst1;
		cout << "lst1 �Ƿ�Ϊ��? " << (lst1.empty() ? "��" : "��") << endl;

		mini_list<int> lst2(5, 42);  // 5��42
		cout << "lst2 ��ʼ: ";
		for (auto& e : lst2) cout << e << " ";
		cout << endl;

		mini_list<int> lst3{ 1, 2, 3, 4, 5 };
		cout << "lst3 ��ʼ: ";
		for (auto& e : lst3) cout << e << " ";
		cout << endl;
	}
}

