#pragma once

#include <iostream>
#include <deque>

namespace Vect {
	template <class T, class Container = std::deque<int>>
	class queue {
	public:
		void push(const T& val) { _con.push_back(val); }
		void pop() { _con.pop_front(); }
		bool empty() const { return _con.empty(); }
		const T& front() const { _con.front(); }
		T& front() { _con.front(); }
		const T& back() const { _con.back(); }
		T& back() { _con.back(); }
		const size_t size() const { return _con.size(); }
	private:
		Container _con;
	};
}
