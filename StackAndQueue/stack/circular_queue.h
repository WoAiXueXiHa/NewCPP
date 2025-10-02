#pragma once
#include <iostream>
#include <cassert>
#include <string>

namespace Vect {
	template <class T>
	class circular_queue {
	private:
		T* _arr; // 底层动态数组控制
		size_t _front; // 队首索引
		size_t _rear; // 队尾索引，指向队列最后一个元素的下一个位置
		size_t _capacity; // 数组总容量 实际只能存储_capacity - 1个元素

	
		// 扩容
		void resize() {
			size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
			T* tmp = new T[new_cap];
			
			// 计算原队列元素个数 防止负数的情况
			size_t count = (_rear - _front + _capacity) % _capacity;
			size_t cur = _front;
			for (size_t i = 0; i < count; i++)
			{
				tmp[i] = _arr[cur];
				cur = (cur + 1) % _capacity;
			}

			delete[] _arr;
			_arr = tmp;
			_capacity = new_cap;
			_front = 0;
			_rear = count; // 新队列队尾指向最后一个元素的下一个位置（无预留空位，后续入队会自动留）
		}

	public:
		// 构造 
		circular_queue(size_t capacity = 4)
			:_front(0)
			, _rear(0)
			, _capacity(capacity)
		{
			_arr = new T[_capacity];
		}

		// 拷贝构造
		circular_queue(const circular_queue& other)
			:_front(other._front)
			, _rear(other._rear)
			, _capacity(other._capacity)
		{
			_arr = new T[_capacity];
			for (size_t i = 0; i < _capacity; i++)
			{
				_arr[i] = other._arr[i];
			}
		}
		// 析构 
		~circular_queue() {
			delete[] _arr;
			_arr = nullptr;
			_front = _rear = 0;
			_capacity = 0;
		}

		// 入队 尾插
		void enqueue(const T& val) {
			// 判断是否满了
			if ((_rear + 1) % _capacity == _front)
				resize();

			_arr[_rear] = val;
			_rear = (_rear + 1) % _capacity;
		}

		// 出队 头删
		void dequeue() {
			// 确保队列不为空
			assert(!empty());
			// 调整_front的指向即可
			_front = (_front + 1) % _capacity;
		}

		// 获取队首元素
		const T& front() const { assert(!empty()); return _arr[_front]; }

		// 获取队尾元素
		const T& back() const {
			assert(!empty());
			// 解决rear=0的负数问题
			size_t tail_idx = (_rear - 1 + _capacity) % _capacity;
			return _arr[tail_idx];
		}

		// 判断队列是否为空
		const bool empty() const { return _front == _rear; }

		// 判断队列是否满了
		const bool full() const { return (_rear + 1) % _capacity == _front; }

		// 计算有效元素个数
		const size_t size() const { return (_rear - 1 + _capacity) % _capacity; }

		// 计算队列容量
		const size_t capacity() const { return _capacity; }

		// 清空队列
		void clear() { _front = 0; _rear = 0; }

		// 打印队列
		void print_circular_queue() {
			if (empty()) {
				std::cout << "队列为空" << "\n";
				return;
			}
			// 先算元素个数再打印
			size_t count = size();
			size_t cur = _front;

			for (size_t i = 0; i < count; i++)
			{
				std::cout << _arr[cur] << " ";
				cur = (cur + 1) % _capacity;
			}
			std::cout << "\n";
		}

	};

	void test_circular_queue() {
		std::cout << "===== 测试无_size的循环队列 =====" << std::endl;
		circular_queue<std::string> cq(3); // 初始容量3，最多存2个元素（预留1个空位）

		// 测试1：入队到满
		std::cout << "\n1. 入队到满（容量3，最多存2个）" << std::endl;
		cq.enqueue("kunkun");
		cq.enqueue("lili");
		cq.print_circular_queue(); // 元素：kunkun lili（容量3，元素数2）
		std::cout << "队列是否已满：" << (cq.full() ? "是" : "否") << std::endl; // 是

		// 测试2：再入队触发扩容（扩容后容量6，最多存5个）
		std::cout << "\n2. 再入队触发扩容（容量→6）" << std::endl;
		cq.enqueue("ahha");
		cq.print_circular_queue(); // 元素：kunkun lili ahha（容量6，元素数3）
		std::cout << "队列是否已满：" << (cq.full() ? "是" : "否") << std::endl; // 否

		// 测试3：出队+判空
		std::cout << "\n3. 出队2个+判空" << std::endl;
		cq.dequeue();
		cq.dequeue();
		cq.print_circular_queue(); // 元素：ahha（容量6，元素数1）
		cq.dequeue();
		std::cout << "队列是否为空：" << (cq.empty() ? "是" : "否") << std::endl; // 是

		// 测试4：拷贝构造
		std::cout << "\n4. 拷贝构造测试" << std::endl;
		cq.enqueue("xixi");
		circular_queue<std::string> cq2(cq);
		cq2.enqueue("haha");
		std::cout << "原队列cq："; cq.print_circular_queue();  // cq：xixi
		std::cout << "拷贝队列cq2："; cq2.print_circular_queue(); // cq2：xixi haha
	}
}
