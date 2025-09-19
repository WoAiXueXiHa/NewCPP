#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

namespace Vect{
	template <class T>
	class mini_vector {
	public:
		typedef T* iterator;
		mini_vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}
		size_t capacity() { return _end_of_storage - _start; }
		size_t size() { return _finish - _start; }
		iterator begin() { return _start; }
		iterator end() { return _finish; }

		T& operator[](size_t i) {
			assert(i < size());

			return _start[i];
		}

		void reserve(size_t n) {
			if (n > capacity()) {
				// ����ɵĴ�С ��ֹ�ɵ�finish-�µ�strat ���δ֪����
				size_t old_size = size();
				T* tmp = new T[n];
				if (_start) {
					memcpy(tmp, _start, sizeof(T) * size());
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + n;
			}
		}
		// β��
		void push_back(const T& input_val) {
			// ����Ƿ���Ҫ����
			if (_finish == _end_of_storage) {
				size_t new_capacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(new_capacity);
			}
			*_finish = input_val;
			++_finish;
		}
		// βɾ
		void pop_back() {
			assert(size() > 0);
			// β��������ǰ�Ƽ��ɶ���β��Ԫ��
			--_finish;
		}

		iterator insert(iterator pos, const T& input_val) {
			assert(pos <= _finish && pos >= _start);
			// ����Ƿ���Ҫ����
			if (_finish == _end_of_storage) {
				// ��¼pos�����_start��ƫ��������ֹ������ʧЧ
				size_t offset = pos - _start;
				size_t new_capacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(new_capacity);
				// ��ƫ���������µ�posλ��
				pos = _start + offset;
			}
			iterator end = _finish;
			while (pos != end) {
				*(end + 1) = *end;
				--end;
			}
			*pos = input_val;
			++_finish;

			return pos;
		}

		void erase(iterator pos) {

		}

	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};

	void test_tra() {
		mini_vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);

		cout << "========��������:========\n";
		for (size_t i = 0; i < v1.size(); i++)
		{
			cout << v1[i] << " ";
		}
		cout << "\n========������:========\n";
		mini_vector<int>::iterator it = v1.begin();
		while (it != v1.end()) {
			cout << *it << " ";
			++it;
		}
		cout << "\n========��Χfor:========\n";
		for (auto e : v1) cout << e << " ";
	}

	void test_insert() {
		mini_vector<double> v1;

		v1.push_back(0.1);
		v1.push_back(0.2);
		v1.push_back(0.3);
		v1.push_back(0.4);

		for (auto e : v1) cout << e << " ";

		cout << endl;

		v1.insert(v1.begin(), 1.99);
		for (auto e : v1) cout << e << " ";
	}

}

