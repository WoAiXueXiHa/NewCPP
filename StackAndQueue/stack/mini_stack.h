#include <iostream>
#include <cassert>

using namespace std;

namespace Vect {
	template <class T>
	class mini_stack {
	private:
		T* _arr; // ��̬����洢����
		int _top_index; // ջ������
		size_t _capacity;

		// ����
		void resize() {
			size_t new_cap = _capacity == 0 ? 4 : 2 * _capacity;
			// ��һ���������Ŀռ�
			T* tmp = new T[new_cap];
			// ��_arr�����ݿ������¿ռ䣨ֻ�踴����ЧԪ�أ���[0, _top_index]��Χ��
			for (size_t i = 0; i < _top_index; i++)
			{
				tmp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = tmp;
			_capacity = new_cap;
		}

	public:
		// ����
		mini_stack(size_t initial_capacity = 4)
			:_arr(new T[initial_capacity])
			,_top_index(-1)
			,_capacity(initial_capacity)
		{}

		// �������� ���
		mini_stack(const mini_stack<T>& other)  
			: _arr(nullptr)
			, _top_index(-1)
			, _capacity(0)
		{
			// 1. ������ԭ������ͬ��С���ڴ�
			_capacity = other._capacity;
			if (_capacity > 0) {
				_arr = new T[_capacity];
				// 2. ����Ԫ�أ�ֻ�踴����ЧԪ�أ���[0, _top_index]��Χ��
				for (size_t i = 0; i <= other._top_index; ++i) {
					_arr[i] = other._arr[i];
				}
			}
			// 3. ����ջ������
			_top_index = other._top_index;
		}

		// ����
		~mini_stack() { clear(); }

		// ��ջ
		void push(const T& val) {
			// �ж��Ƿ���Ҫ����
			if (_top_index + 1 == _capacity) resize();
			// ѹջ
			_arr[++_top_index] = val;
		}

		// ��ջ
		void pop() { assert(!empty()); --_top_index; }

		// ��ȡջ��Ԫ��
		T& top() { assert(!empty());  return _arr[_top_index]; }

		// �п�
		bool empty() { return _top_index == -1; }

		// ��ЧԪ�ظ���
		size_t size() { return _top_index + 1; }

		// ����
		size_t capacity() const { return _capacity; }

		// ����Ԫ�ص����ı�����
		void clear() { _top_index = -1; }

		// ��ӡջ
		void print_stack() {
			if (_top_index == -1)
				cout << "��ջΪ��" << endl;
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