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

		// 迭代器
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		iterator begin() const { return _start; }
		iterator end() const { return _finish; }
		const_iterator cbegin()const { return _start; }
		const_iterator cend() const { return _finish; }


		// 容量相关函数
		size_t capacity() const {
			if (!_start || !_end_of_storage) return 0;
			return _end_of_storage - _start; 
		}
		size_t size() const { 
			if (!_start || !_end_of_storage) return 0;
			return _finish - _start; 
		}
		bool empty() const { return _start == _finish; }

		// 构造函数
		// 默认构造
		my_vector()
			:_start(nullptr)
			, _finish(nullptr)
			,_end_of_storage(nullptr)
		{ }

		// 构造n个元素
		my_vector(size_t n, const T& val = T()) 
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr) 
		{
			reserve(n);
			// 将所有数据尾插
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// 迭代器区间初始化
		// 类模板的成员函数也能写成函数模板 支持了任意容器的迭代器初始化
		template <class InputIterator>
		my_vector(InputIterator first, InputIterator last) 
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			// 计算元素个数
			size_t n = 0;
			InputIterator tmp = first;
			while (tmp != last) {
				++tmp;
				++n;
			}

			// 尾插n个元素
			reserve(n);
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		// 拷贝构造
		my_vector(const my_vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			// 逐个拷贝源vector的元素
			reserve(v.capacity());
			for (const auto& tmp : v) push_back(tmp);
		}

		void swap(my_vector<T>& v) {
			// 交换三个核心指针
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		// 赋值运算符重载
		my_vector<T>& operator=(my_vector<T> v) {
			swap(v);
			return *this;
		}

		// 析构
		~my_vector() {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
	
		}

		// 元素访问
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
				*end = *(end - 1);
				end--;
			}
			*pos = input_val;
			_finish++;

			return pos;
		}

		// 删除pos位置元素
		iterator erase(iterator pos) {
			// 检查pos的合理性
			assert(pos < _finish && pos >= _start);

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


	// 打印vector信息的辅助函数
	template<class T>
	void print_my_vector(const Vect::my_vector<T>& v, const std::string& name) {
		std::cout << name << " - 大小: " << v.size()
			<< ", 容量: " << v.capacity()
			<< ", 元素: ";
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
	}

	// 封装所有测试逻辑的函数
	void test() {
		std::cout << "===== 开始测试my_vector所有接口 =====" << std::endl;

		//  测试默认构造函数
		Vect::my_vector<int> v1;
		print_my_vector(v1, "v1(默认构造)");

		//  测试push_back、size、capacity
		for (int i = 1; i <= 5; ++i) {
			v1.push_back(i);
		}
		print_my_vector(v1, "v1(push_back 1-5后)");

		// 测试reserve
		v1.reserve(10);
		print_my_vector(v1, "v1(reserve(10)后)");

		//  测试带参数构造函数（修复类名错误：原Vect::vector改为Vect::my_vector）
		Vect::my_vector<int> v2((size_t)3, 10);
		print_my_vector(v2, "v2(构造3个10)");

		//  测试迭代器范围构造
		Vect::my_vector<int> v3(v1.begin() + 2, v1.begin() + 6);
		print_my_vector(v3, "v3(迭代器范围v1[2]-v1[5])");

		//  测试拷贝构造
		Vect::my_vector<int> v4(v1);
		print_my_vector(v4, "v4(拷贝v1)");

		//  测试赋值运算符
		Vect::my_vector<int> v5;
		v5 = v2;
		print_my_vector(v5, "v5(赋值v2)");

		// 测试operator[]和修改元素
		v5[0] = 99;
		v5[1] = 88;
		print_my_vector(v5, "v5(修改第0位为99、第1位为88后)");

		//  测试front和back
		std::cout << "v5 front: " << v5.front() << ", back: " << v5.back() << std::endl;

		//  测试insert（修复打印函数名：原print_vector改为print_my_vector）
		auto it = v5.insert(v5.begin() + 1, 55);
		print_my_vector(v5, "v5(在第1位插入55后)");

		//  测试erase（修复打印函数名）
		it = v5.erase(v5.begin() + 3);
		print_my_vector(v5, "v5(删除第3位元素后)");

		// 测试empty
		Vect::my_vector<int> v6;
		std::cout << "v6是否为空: " << (v6.empty() ? "是" : "否") << std::endl;
		v6.push_back(1);
		std::cout << "v6添加1后是否为空: " << (v6.empty() ? "是" : "否") << std::endl;
		print_my_vector(v6, "v6(添加1后)");

		std::cout << "===== 所有接口测试完成 =====" << std::endl;
	}
}


