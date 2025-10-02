#include <iostream>
#include <cassert>

using namespace std;

namespace Vect {
	template <class T>
	class mini_stack {
	private:
		T* _arr; // 动态数组存储数据
		int _top_index; // 栈顶索引
		size_t _capacity;

		// 扩容
		void resize() {
			size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
			// 开一个新容量的空间
			T* tmp = new T[new_cap];
			// 将_arr的内容拷贝到新空间（只需复制有效元素，即[0, _top_index]范围）
			for (size_t i = 0; i < _top_index; i++)
			{
				tmp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = tmp;
			_capacity = new_cap;
		}

	public:
		// 构造
		mini_stack(size_t initial_capacity = 4)
			:_arr(new T[initial_capacity])
			,_top_index(-1)
			,_capacity(initial_capacity)
		{}

		// 拷贝构造 深拷贝
		mini_stack(const mini_stack<T>& other)  
			: _arr(nullptr)
			, _top_index(-1)
			, _capacity(0)
		{
			// 1. 分配与原对象相同大小的内存
			_capacity = other._capacity;
			if (_capacity > 0) {
				_arr = new T[_capacity];
				// 2. 复制元素（只需复制有效元素，即[0, _top_index]范围）
				for (size_t i = 0; i <= other._top_index; ++i) {
					_arr[i] = other._arr[i];
				}
			}
			// 3. 复制栈顶索引
			_top_index = other._top_index;
		}

		// 析构
		~mini_stack() { clear(); }

		// 入栈
		void push(const T& val) {
			// 判断是否需要扩容
			if (_top_index + 1 == _capacity) resize();
			// 压栈
			_arr[++_top_index] = val;
		}

		// 出栈
		void pop() { assert(!empty()); --_top_index; }

		// 获取栈顶元素
		T& top() { assert(!empty());  return _arr[_top_index]; }

		// 判空
		bool empty() { return _top_index == -1; }

		// 有效元素个数
		size_t size() { return _top_index + 1; }

		// 容量
		size_t capacity() const { return _capacity; }

		// 清理元素但不改变容量
		void clear() { _top_index = -1; }

		// 打印栈
		void print_stack() {
			if (_top_index == -1)
				cout << "此栈为空" << endl;
			else
				for (size_t i = 0; i <= _top_index; i++)
				{
					cout << _arr[_top_index] << " ";
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