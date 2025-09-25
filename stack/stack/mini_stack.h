#include <iostream>
#include <cassert>

using namespace std;

namespace Vect {
	template <class T>
	class mini_stack {
	private:
		T* _arr; // 底层用动态数组实现
		int _top_index; // 索引从0开始 如果为-1 则为空栈
		size_t _capacity;

		// 扩容
		void resize() {
			size_t new_capacity = (_capacity == 0) ? 4 : 2 * _capacity;
			T* tmp = new T[new_capacity];

			// 深拷贝
			for (size_t i = 0; i < new_capacity; i++)
			{
				tmp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = tmp;
			_capacity = new_capacity;
		}
	public:
		// 构造
		mini_stack(const size_t initial_capacity = 4)
			:_arr(new T[initial_capacity])
			, _top_index(-1)
			,_capacity(initial_capacity)
		{ }
		// 拷贝构造
		mini_stack(const mini_stack& other)
			:_arr(new T[other._capacity])
			, _top_index(other._top_index)
			, _capacity(other._capacity)
		{
			for (size_t i = 0; i < other._top_index; i++)
			{
				_arr[i] = other._arr[i];
			}
		}
		// 析构
		~mini_stack() {
			delete[] _arr;
			_arr = nullptr;
			_top_index = _capacity = 0;
		}

		// 压栈
		void push(const T& val) {
			if (_top_index + 1 == _capacity) resize();
			_arr[++_top_index] = val;
		}
		// 出栈
		void pop() {
			assert(!empty());
			--_top_index;
		}

		bool empty() { return _top_index == -1; }

		size_t size() { return _top_index + 1; }
		size_t capacity(){ return _capacity; }

		T& top() { assert(!empty()); return _arr[_top_index]; }

		void clear() { _top_index = -1; }

		void print_stack() {
			if (empty()) {  // 处理空栈情况
				cout << "栈为空" << endl;
				return;
			}
			// 有效元素范围是 0 ~ _top_index（包含两者）
			for (size_t i = 0; i <= _top_index; ++i) {
				cout << _arr[i] << " ";
			}
			cout << endl;
		}
	};

	void test_mini_stack() {
		mini_stack<int> st;
		cout << "===== 测试mini_stack =====" << endl;
		cout << "===== 1. 测试栈是否为空 =====" << endl;

		cout << st.empty() << endl;

		cout << "===== 2. 测试入栈 =====" << endl;
		st.push(10);
		st.push(20);
		st.push(30);
		st.push(40);
		st.print_stack();

		cout << "===== 3. 测试出栈 =====" << endl;
		st.pop();
		st.pop();
		st.print_stack();

		cout << "===== 3. 测试容量 =====" << endl;
		cout << "size(): " << st.size() << "     " << "capacity(): " << st.capacity() << endl;

		cout << "===== 4. 测试clear =====" << endl;
		st.clear();
		cout << "size(): " << st.size() << "   已清空"<<endl;
	}
}