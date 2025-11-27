#pragma once

namespace sharedPtr {
	template <class T>
	class shared_ptr {
	private:
		T* _ptr;
		int* _refConut;
	public:
		shared_ptr(const T* ptr = nullptr)
			:_ptr(ptr)
			, _refConut(new int(0))
		{
			cout << "shared_ptr构造: " << _ptr << " 数量: " << _refConut << endl;
		}

		shared_ptr(const shared_ptr<T>& other) {

		}
	};
}