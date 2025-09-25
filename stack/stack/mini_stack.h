#include <iostream>
#include <cassert>

using namespace std;

namespace Vect {
	template <class T>
	class mini_stack {
	private:
		T* _arr; // �ײ��ö�̬����ʵ��
		int _top_index; // ������0��ʼ ���Ϊ-1 ��Ϊ��ջ
		size_t _capacity;

		// ����
		void resize() {
			size_t new_capacity = (_capacity == 0) ? 4 : 2 * _capacity;
			T* tmp = new T[new_capacity];

			// ���
			for (size_t i = 0; i < new_capacity; i++)
			{
				tmp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = tmp;
			_capacity = new_capacity;
		}
	public:
		// ����
		mini_stack(const size_t initial_capacity = 4)
			:_arr(new T[initial_capacity])
			, _top_index(-1)
			,_capacity(initial_capacity)
		{ }
		// ��������
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
		// ����
		~mini_stack() {
			delete[] _arr;
			_arr = nullptr;
			_top_index = _capacity = 0;
		}

		// ѹջ
		void push(const T& val) {
			if (_top_index + 1 == _capacity) resize();
			_arr[++_top_index] = val;
		}
		// ��ջ
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
			if (empty()) {  // �����ջ���
				cout << "ջΪ��" << endl;
				return;
			}
			// ��ЧԪ�ط�Χ�� 0 ~ _top_index���������ߣ�
			for (size_t i = 0; i <= _top_index; ++i) {
				cout << _arr[i] << " ";
			}
			cout << endl;
		}
	};

	void test_mini_stack() {
		mini_stack<int> st;
		cout << "===== ����mini_stack =====" << endl;
		cout << "===== 1. ����ջ�Ƿ�Ϊ�� =====" << endl;

		cout << st.empty() << endl;

		cout << "===== 2. ������ջ =====" << endl;
		st.push(10);
		st.push(20);
		st.push(30);
		st.push(40);
		st.print_stack();

		cout << "===== 3. ���Գ�ջ =====" << endl;
		st.pop();
		st.pop();
		st.print_stack();

		cout << "===== 3. �������� =====" << endl;
		cout << "size(): " << st.size() << "     " << "capacity(): " << st.capacity() << endl;

		cout << "===== 4. ����clear =====" << endl;
		st.clear();
		cout << "size(): " << st.size() << "   �����"<<endl;
	}
}