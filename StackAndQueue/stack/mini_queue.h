#include <iostream>
#include <cassert>
#include <list>
#include <string>

namespace Vect {
	// 链表类
	template <class T>
	struct list_node {
		list_node* _next;
		T _val;

		list_node(const T& val = T())
			:_next(nullptr)
			,_val(val)
		{ }
	};

	// 队列类
	template <class T>
	class mini_queue {
	private:
		list_node<T>* _head; // 队首
		list_node<T>* _tail; // 队尾
		size_t _size;

	public:
		// 构造
		mini_queue()
			:_head(nullptr)
			,_tail(nullptr)
			,_size(0)
		{ }
		
		// 拷贝构造（深拷贝）
		mini_queue(const mini_queue& other)
			:_head(nullptr)
			, _tail(nullptr)
			, _size(0)
		{
			// 遍历 other 链表，把每个元素都拷贝一份
			list_node<T>* cur = other._head;
			while (cur) {
				enqueue(cur->_val); // 借助已有的 enqueue 实现
				cur = cur->_next;
			}
		}

		// 析构
		~mini_queue() { clear(); }

		//  入队 尾插
		void enqueue(const T& val) {
			list_node<T>* new_node = new list_node<T>(val);
			// 空队列 新元素既是队首 也是队尾
			if (_head == nullptr) {
				_head = _tail = new_node;
			}
			else {
				_tail->_next = new_node;
				_tail = new_node;
			}
			++_size;
		}

		// 出队 头删
		void dequeue() {
			assert(!empty());

			// 保存当前队首节点（待删除）
			list_node<T>* tmp = _head;

			// 队列只有一个元素
			if (_head == _tail) {
				_head = _tail = nullptr;  // 删完后队列空，头尾都置空
			}
			else {
				// 多个元素：头指针后移到下一个节点
				_head = _head->_next;
			}

			delete tmp;  // 删除原来的队首节点
			--_size;     // 队列大小减1
		}

		// 获取队首队尾元素
		const T& front() const { assert(!empty()); return _head->_val; }
		const T& back() const { assert(!empty()); return _tail->_val; }

		// 判空
		const bool empty() const { return _size == 0; }

		// 队列元素个数
		const size_t size() const { return _size; }

		// 清空队列
		void clear() { while (!empty()) dequeue(); }

		// 打印队列
		void print_queue() {
			if (empty()) {
				std::cout << "此队列为空" << std::endl;
				return;
			}

			list_node<T>* cur = _head;
			while (cur) {
				std::cout << cur->_val << " ";
				cur = cur->_next;
			}
			std::cout << std::endl;
		}
	};

	void test_mini_queue() {
		mini_queue<std::string> q;

		std::cout << "===== 测试队列 =====" << std::endl;

		std::cout << "===== 1. 测试入队列 =====" << std::endl;

		q.enqueue("kunkun");
		q.enqueue("abc");
		q.enqueue("lili");
		q.enqueue("ahha");
		q.print_queue();

		std::cout << "===== 2. 获取队头及队尾元素 =====" << std::endl;
		std::cout << "队首： " << q.front() << std::endl;
		std::cout << "队尾： " << q.back() << std::endl;

		std::cout << "===== 3. 获取队列元素个数 =====" << std::endl;
		std::cout << "队列元素个数： " << q.size() << std::endl;


		std::cout << "===== 4. 测试出队列 =====" << std::endl;
		q.dequeue();
		q.dequeue();
		q.print_queue();


		std::cout << "===== 4. 测试清空队列 =====" << std::endl;
		q.clear();
		if (q.empty()) std::cout << "队列清空完成" << std::endl;
		else std::cout << "队列清空异常" << std::endl;

	}
}