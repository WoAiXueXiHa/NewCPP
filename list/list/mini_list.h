#include <iostream>
#include <cassert>
#include <cstdbool>
#include <initializer_list>
using namespace std;

namespace Vect {
	// 节点类 链表类会频繁访问节点 所以将节点类成员公开
	template <class T>
	struct list_node {

		list_node<T>* _prev; // 记录前驱节点的地址
		list_node<T>* _next; // 记录后继节点的地址

		T _data; // 该节点存储的数据

		// 默认构造
		list_node(const T& input_val = T())
			:_prev(nullptr)
			,_next(nullptr)
			,_data(input_val)
		{ }
	};

	// --------- 迭代器模版 (用于实现 iterator / const_iterator) ---------
	// 模版参数:
	// T   : 节点中存放的数据类型
	// Ref : operator* 的返回类型 (T& 或 const T&)
	// Ptr : operator-> 的返回类型 (T* 或 const T*)
	//
	// 这样用一个模版类实现了可写迭代器和只读迭代器两种行为（避免重复代码）。

	template <class T, class ref, class ptr>
	struct list_iterator {
		typedef list_node<T> Node;
		typedef list_iterator<T, ref, ptr> self; // 将类型名缩短 好书写

		Node* _node; // 指向当前节点（在 end() 情况下指向哨兵 _head）

		// 构造
		list_iterator(Node* node = nullptr)
			:_node(node)
		{ }

		// 重载运算符 让外部任何容器使用iterator的方式统一

		// 前置++ 移动到下一个节点 返回自身引用 还可以修改 若返回值 则只能修改副本 生命周期结束值就没了
		self& operator++() {
			_node = _node->_next;
			return *this;
		}

		// 前置-- 移动到前一个节点
		self& operator--() {
			_node = _node->_prev;
			return *this;
		}

		// 后置++ 返回旧值 自己往后移动一位
		self operator++(int) {
			self tmp = *this;
			_node = _node->_next;
			return tmp;
		}

		// 后置-- 返回旧值 自己往前移动一位
		self operator--(int) {
			self tmp = *this;
			_node = _node->_prev;
			return tmp;
		}

		// * 解引用 返回 ref（可以是 T& 或 const T&）
		ref operator*()  {
			// 不要对哨兵位解引用
			assert(_node);
			return _node->_data;
		}

		// -> 指针访问成员 返回ptr（T* 或 const T*）
		ptr operator->() {
			assert(_node);
			return &_node->_data; // 取地址
		}

		// != ==重载
		bool operator==(const self& other) const {
			return _node == other._node;
		}

		bool operator!=(const self& other) const {
			return _node != other._node;
		}
	};
	
	// 链表类 用哨兵位控制整个链表
	template <class T>
	class mini_list {
	public:
		typedef list_node<T> Node;
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); } // 哨兵位当作尾

		const_iterator begin() const { return const_iterator(_head->_next); }
		const_iterator end() const { return const_iterator(_head); }


		// 构造空链表
		void empty_list() {
			// new一个哨兵位
			_head = new Node(); // 不存储有效值 默认T()
			_head->_next = _head;
			_head->_prev = _head;
		}
		mini_list() { empty_list(); }

		mini_list(initializer_list<T> il) {
			empty_list();
			for (const auto& e : il) push_back(e);
		}
		// 构造n个值相同的节点
		mini_list(size_t n, const T& val) {
			empty_list();
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// 拷贝构造
		mini_list(const mini_list<T>& other) {
			empty_list();
			for (const auto& e : other) push_back(e);
		}

		// 赋值运算符重载
		mini_list<T>& operator=(mini_list<T> other) {
			// 交换指针
			std::swap(_head, other._head);
			return *this;
		}
		// 析构：释放所有节点与哨兵
		~mini_list() {
			if (_head) {
				clear();
				delete _head;
				_head = nullptr;
			}
		}

		// pos前插入新节点
		iterator insert(iterator pos, const T& input_val) {
			Node* cur = pos._node;
			Node* new_node = new Node(input_val);
			Node* prev = cur->_prev;

			// 连接 prev <-> newnode <-> cur
			new_node->_prev = prev;
			new_node->_next = cur;
			prev->_next = new_node;
			cur->_prev = new_node;

			return iterator(new_node);
		}

		// 在第 pos 个位置前插入 val（pos 从 0 开始）
		iterator insert(size_t pos, const T& val) {
			auto it = begin();
			for (size_t i = 0; i < pos && it != end(); ++i) {
				++it;
			}
			return insert(it, val); // 调用原来的 iterator 版本
		}

		// 删除pos位置节点 返回指向被删节点后继的迭代器
		iterator erase(iterator pos) {
			// 不能删除哨兵位
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = cur->_next;
			next->_prev = cur->_prev;

			delete cur;

			return iterator(next);
		}

		// 删除pos索引的节点（pos 从 0 开始）
		iterator erase(size_t pos) {
			auto it = begin();
			for (size_t i = 0; i < pos && it != end(); ++i) {
				++it;
			}
			return erase(it); 
		}
		// 尾插
		void push_back(const T& input_val) { insert(end(), input_val); }
		// 头插
		void push_front(const T& input_val) {
			insert(begin(), input_val); 
		}
		// 尾删
		void pop_back() { 
			assert(_head->_next != _head);  
			// 删除最后一个有效节点 -> --end() 指向最后一个节点
			erase(--end());
		}
		// 头删
		void pop_front() { 
			assert(_head->_next != _head);  
			erase(begin()); 
		}

		// 清空链表
		void clear(){
			auto it = begin();
			while (it != end()) {
				it = erase(it); // 返回下一个有效迭代器
			}
		}
		// 判空
		bool empty() { return _head->_next == _head; }

		// 打印整个链表（假定 T 可输出）
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
		cout << "==== 测试 mini_list 插入删除操作 ====" << endl;
		list.push_back(1);
		list.push_back(11);
		list.push_back(1111);
		list.push_back(11111);
		list.debug_print();

		cout << "头插后：" << endl;
		list.push_front(2);
		list.push_front(22);
		list.push_front(222);
		list.push_front(2222);
		list.debug_print();

		cout << "在索引为3的位置插入100：" << endl;
		list.insert(3, 100);
		list.debug_print();

		cout << "尾删后：" << endl;
		list.pop_back();
		list.debug_print();

		cout << "头删后：" << endl;
		list.pop_front();
		list.debug_print();

		cout << "删除索引为2的节点" << endl;
		list.erase(2);
		list.debug_print();
	}

	void test_constructor() {
		cout << "==== 测试 mini_list 构造 ====" << endl;

		mini_list<int> lst1;
		cout << "lst1 是否为空? " << (lst1.empty() ? "是" : "否") << endl;

		mini_list<int> lst2(5, 42);  // 5个42
		cout << "lst2 初始: ";
		for (auto& e : lst2) cout << e << " ";
		cout << endl;

		mini_list<int> lst3{ 1, 2, 3, 4, 5 };
		cout << "lst3 初始: ";
		for (auto& e : lst3) cout << e << " ";
		cout << endl;
	}
}

