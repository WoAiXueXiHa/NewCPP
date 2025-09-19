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

		// 迭代器
		iterator begin() { return _start; }
		iterator end() { return _finish; }

		// 容量get函数
		size_t capacity() { return _end_of_storage - _start; }
		size_t size() { return _finish - _start; }

		// 构造函数
		my_vector()
			:_start(nullptr)
			, _finish(nullptr)
			,_end_of_storage(nullptr){ }

		// 索引重载 返回当前这个值
		T& operator[](size_t index){
			if(index < size()) return _start[index];
		}

		// 预留空间
		void reserve(size_t input_num) {
			// 提前保存旧空间大小 释放之后 _start是新的 但_finish是旧的
			size_t old_size = size();
			// 输入的值大于容量才触发扩容机制
			if (input_num > capacity()) {
				// 开辟一块新的空间 将旧空间数据拷贝到新空间
				T* tmp = new T[input_num];
				// 保证_start不为空 才可以将旧空间数据拷贝到新空间
				if (_start) {
					// memcpy有局限性 浅拷贝 遇到string list类会出问题
					//memcpy(tmp, _start, sizeof(T) * size());

					// 深拷贝
					for (size_t i = 0; i < old_size ; i++)
					{
						tmp[i] = _start[i]; // 将值一个一个拷贝过去
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + input_num;
			}
		}

		void push_back(const T& input_val) {
			//// 判断是否需要扩容
			//if (_finish == _end_of_storage) {
			//	size_t new_cap = capacity() == 0 ? 4 : 2 * capacity();
			//	reserve(new_cap);
			//}

			//*_finish = input_val;
			//_finish++;

			// 复用insert
			insert(_finish, input_val);
		}

		// 在pos之后插入元素
		iterator insert(iterator pos, const T& input_val) {
			// 检查pos的合理性
			assert(pos <= _finish && pos >= _start);
			// 判断是否需要扩容
			if (_finish == _end_of_storage) {
				//  在reserve的逻辑里 会将_start原来的空间删除 而pos指向的是_start的旧空间
				// 所以释放旧空间之后 pos是野指针 会引发迭代器失效
				// 需要记录pos和_start的相对位置
				size_t len = pos - _start;
				size_t new_cap = capacity() == 0 ? 4 : 2 * capacity();
				reserve(new_cap);
				// 更新pos位置
				pos = _start + len;
			}

			// 从后往前挪动数据
			iterator end = _finish;
			while (end != pos) {
				*(end + 1) = *end;
				end--;
			}
			*pos = input_val;
			_finish++;

			return pos;
		}

		// 删除pos位置元素
		iterator erase(iterator pos) {
			// 检查pos的合理性
			assert(pos <= _finish && pos >= _start);

			// 将pos之后的元素依次往前挪动一位
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

		// 索引访问
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

