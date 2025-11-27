#pragma once
// auto_ptr 管理权限转移 禁止使用！！！！

namespace autoPtr {
	template <class T>
	class auto_ptr {
	private:
		T* _ptr;
	public:
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{
			cout << "auto_ptr构造 : " << _ptr << endl;
		}

		// *this <- other other管理权给*this
		auto_ptr(const auto_ptr<T>& other)
			:_ptr(other._ptr)
		{
			other._ptr = nullptr;
		}

		auto_ptr& operator=(auto_ptr<T>& other) {
			if (this != &other) {
				// 先释放自己的资源
				if (_ptr) {
					delete _ptr;
				}
				// 拿来别人的资源
				_ptr = other._ptr;
				other._ptr = nullptr;
			}
			return *this;
		}

		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }

		~auto_ptr() {
			if (_ptr) {
				cout << "~auto_ptr() : " << _ptr << endl;
				delete _ptr;
			}
		}
	};

	struct Date {
		int year;
		int month;
		int day;

		Date() = default;
	};
}
