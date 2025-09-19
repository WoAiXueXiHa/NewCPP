#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;
namespace Vect {
	template <class T>
	class my_vector {
	public:
		typedef T* iterator;
		typedef T* const_iterator;

		// ������
		iterator begin() { return _start; }
		iterator end() { return _finish; }

		// ����get����
		size_t capacity() { return _end_of_storage - _start; }
		size_t size() { return _finish - _start; }

		// ���캯��
		my_vector()
			:_start(nullptr)
			, _finish(nullptr)
			,_end_of_storage(nullptr){ }

		// �������� ���ص�ǰ���ֵ
		T& operator[](size_t index){
			if(index < size()) return _start[index];
		}

		// Ԥ���ռ�
		void reserve(size_t input_num) {
			// ��ǰ����ɿռ��С �ͷ�֮�� _start���µ� ��_finish�Ǿɵ�
			size_t old_size = size();
			// �����ֵ���������Ŵ������ݻ���
			if (input_num > capacity()) {
				// ����һ���µĿռ� ���ɿռ����ݿ������¿ռ�
				T* tmp = new T[input_num];
				// ��֤_start��Ϊ�� �ſ��Խ��ɿռ����ݿ������¿ռ�
				if (_start) {
					// memcpy�о����� ǳ���� ����string list��������
					//memcpy(tmp, _start, sizeof(T) * size());

					// ���
					for (size_t i = 0; i < old_size ; i++)
					{
						tmp[i] = _start[i]; // ��ֵһ��һ��������ȥ
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + input_num;
			}
		}

		void push_back(const T& input_val) {
			//// �ж��Ƿ���Ҫ����
			//if (_finish == _end_of_storage) {
			//	size_t new_cap = capacity() == 0 ? 4 : 2 * capacity();
			//	reserve(new_cap);
			//}

			//*_finish = input_val;
			//_finish++;

			// ����insert
			insert(_finish, input_val);
		}

		// ��pos֮�����Ԫ��
		iterator insert(iterator pos, const T& input_val) {
			// ���pos�ĺ�����
			assert(pos <= _finish && pos >= _start);
			// �ж��Ƿ���Ҫ����
			if (_finish == _end_of_storage) {
				//  ��reserve���߼��� �Ὣ_startԭ���Ŀռ�ɾ�� ��posָ�����_start�ľɿռ�
				// �����ͷžɿռ�֮�� pos��Ұָ�� ������������ʧЧ
				// ��Ҫ��¼pos��_start�����λ��
				size_t len = pos - _start;
				size_t new_cap = capacity() == 0 ? 4 : 2 * capacity();
				reserve(new_cap);
				// ����posλ��
				pos = _start + len;
			}

			// �Ӻ���ǰŲ������
			iterator end = _finish;
			while (end != pos) {
				*(end + 1) = *end;
				end--;
			}
			*pos = input_val;
			_finish++;

			return pos;
		}

		// ɾ��posλ��Ԫ��
		iterator erase(iterator pos) {
			// ���pos�ĺ�����
			assert(pos <= _finish && pos >= _start);

			// ��pos֮���Ԫ��������ǰŲ��һλ
			iterator end = pos + 1;

			while (end != _finish) {
				*(end - 1) = *end;
				end++;
			}

			_finish--;

			return pos;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};



	void test_tra() {
		my_vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);

		// ��������
		cout << "==== index ====" << endl;
		for (size_t i = 0; i < v1.size(); i++)
		{
			cout << v1[i] << " ";
		}

		cout << endl << "==== iterator ====" << endl;
		my_vector<int>:: iterator it = v1.begin();
		while (it != v1.end()) {
			cout << *it << " ";
			it++;
		}

		cout << endl << "==== endge for ====" << endl;
		for (auto e : v1) cout << e << " ";
	}

	void test_erase() {
		my_vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(6);

		for (auto e : v1) cout << e << " ";
		my_vector<int>::iterator target = find(v1.begin(), v1.end(), 3);
		v1.erase(target);
		cout << endl;
		for (auto e : v1) cout << e << " ";

		
	
	
	}
}

