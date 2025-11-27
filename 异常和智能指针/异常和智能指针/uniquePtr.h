#pragma once

namespace uniquePtr {
	template <class T>
	class unique_ptr {
	private:
		T* _ptr;
	public:
		unique_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{
			cout << "unique_ptr¹¹Ôì: " << _ptr << endl;
		}

		~unique_ptr() {
			if (_ptr) {
				cout << "unique_ptrÎö¹¹: " << _ptr << endl;
			}
		}
		// ¼òµ¥´Ö±© ½ûÖ¹¿½±´
		unique_ptr(const unique_ptr<T>& other) = delete;
		unique_ptr& operator=(const unique_ptr<T>& other) = delete;

		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }
	};

	struct Date {
		int year;
		int month;
		int day;

		Date() = default;
	};
}