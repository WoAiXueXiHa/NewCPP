#include <iostream>
#include <algorithm>

template <class T>
class mini_vector {
public:
	typedef T* iterator;
	void push_back() {

	}
private:
	T* _arr;
	iterator _start;
	iterator _finish;
	iterator _end_of_storage;
};