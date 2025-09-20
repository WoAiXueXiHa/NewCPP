#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

namespace Vect {
	template <class T>
	class my_vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		// ������
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		iterator begin() const { return _start; }
		iterator end() const { return _finish; }
		const_iterator cbegin()const { return _start; }
		const_iterator cend() const { return _finish; }


		// ������غ���
		size_t capacity() const {
			if (!_start || !_end_of_storage) return 0;
			return _end_of_storage - _start; 
		}
		size_t size() const { 
			if (!_start || !_end_of_storage) return 0;
			return _finish - _start; 
		}
		bool empty() const { return _start == _finish; }

		// ���캯��
		// Ĭ�Ϲ���
		my_vector()
			:_start(nullptr)
			, _finish(nullptr)
			,_end_of_storage(nullptr)
		{ }

		// ����n��Ԫ��
		my_vector(size_t n, const T& val = T()) 
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr) 
		{
			reserve(n);
			// ����������β��
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// �����������ʼ��
		// ��ģ��ĳ�Ա����Ҳ��д�ɺ���ģ�� ֧�������������ĵ�������ʼ��
		template <class InputIterator>
		my_vector(InputIterator first, InputIterator last) 
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			// ����Ԫ�ظ���
			size_t n = 0;
			InputIterator tmp = first;
			while (tmp != last) {
				++tmp;
				++n;
			}

			// β��n��Ԫ��
			reserve(n);
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		// ��������
		my_vector(const my_vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			// �������Դvector��Ԫ��
			reserve(v.capacity());
			for (const auto& tmp : v) push_back(tmp);
		}

		void swap(my_vector<T>& v) {
			// ������������ָ��
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		// ��ֵ���������
		my_vector<T>& operator=(my_vector<T> v) {
			swap(v);
			return *this;
		}

		// ����
		~my_vector() {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
	
		}

		// Ԫ�ط���
		T& operator[](size_t index){
			if(index < size()) return _start[index];
		}

		const T& operator[](size_t index) const {
			assert(index < size());
			return _start[index];
		}

		T& front() {
			assert(!empty());
			return *_start;
		}

		const T& front() const {
			assert(!empty());
			return *_start;
		}

		T& back() {
			assert(!empty());
			return *(_finish - 1);
		}

		const T& back() const {
			assert(!empty());
			return *(_finish - 1);
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
				*end = *(end - 1);
				end--;
			}
			*pos = input_val;
			_finish++;

			return pos;
		}

		// ɾ��posλ��Ԫ��
		iterator erase(iterator pos) {
			// ���pos�ĺ�����
			assert(pos < _finish && pos >= _start);

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


	// ��ӡvector��Ϣ�ĸ�������
	template<class T>
	void print_my_vector(const Vect::my_vector<T>& v, const std::string& name) {
		std::cout << name << " - ��С: " << v.size()
			<< ", ����: " << v.capacity()
			<< ", Ԫ��: ";
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
	}

	// ��װ���в����߼��ĺ���
	void test() {
		std::cout << "===== ��ʼ����my_vector���нӿ� =====" << std::endl;

		//  ����Ĭ�Ϲ��캯��
		Vect::my_vector<int> v1;
		print_my_vector(v1, "v1(Ĭ�Ϲ���)");

		//  ����push_back��size��capacity
		for (int i = 1; i <= 5; ++i) {
			v1.push_back(i);
		}
		print_my_vector(v1, "v1(push_back 1-5��)");

		// ����reserve
		v1.reserve(10);
		print_my_vector(v1, "v1(reserve(10)��)");

		//  ���Դ��������캯�����޸���������ԭVect::vector��ΪVect::my_vector��
		Vect::my_vector<int> v2((size_t)3, 10);
		print_my_vector(v2, "v2(����3��10)");

		//  ���Ե�������Χ����
		Vect::my_vector<int> v3(v1.begin() + 2, v1.begin() + 6);
		print_my_vector(v3, "v3(��������Χv1[2]-v1[5])");

		//  ���Կ�������
		Vect::my_vector<int> v4(v1);
		print_my_vector(v4, "v4(����v1)");

		//  ���Ը�ֵ�����
		Vect::my_vector<int> v5;
		v5 = v2;
		print_my_vector(v5, "v5(��ֵv2)");

		// ����operator[]���޸�Ԫ��
		v5[0] = 99;
		v5[1] = 88;
		print_my_vector(v5, "v5(�޸ĵ�0λΪ99����1λΪ88��)");

		//  ����front��back
		std::cout << "v5 front: " << v5.front() << ", back: " << v5.back() << std::endl;

		//  ����insert���޸���ӡ��������ԭprint_vector��Ϊprint_my_vector��
		auto it = v5.insert(v5.begin() + 1, 55);
		print_my_vector(v5, "v5(�ڵ�1λ����55��)");

		//  ����erase���޸���ӡ��������
		it = v5.erase(v5.begin() + 3);
		print_my_vector(v5, "v5(ɾ����3λԪ�غ�)");

		// ����empty
		Vect::my_vector<int> v6;
		std::cout << "v6�Ƿ�Ϊ��: " << (v6.empty() ? "��" : "��") << std::endl;
		v6.push_back(1);
		std::cout << "v6���1���Ƿ�Ϊ��: " << (v6.empty() ? "��" : "��") << std::endl;
		print_my_vector(v6, "v6(���1��)");

		std::cout << "===== ���нӿڲ������ =====" << std::endl;
	}
}


