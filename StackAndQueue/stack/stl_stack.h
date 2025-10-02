#include <iostream>
#include <cassert>
#include <vector>
#include <list>

namespace Vect {
	template <class T, class Container = std::vector<T>>
	class my_stack {
	private:
		Container _con;
	public:
		bool isEmpty() { return _con.empty(); }
		const size_t size() const { return _con.size(); }
	};
}