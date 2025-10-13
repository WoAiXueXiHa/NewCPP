#pragma once
#include <iostream>
#include <deque>

namespace Vect {
	// 第二个参数：适配器 传一个容器
	template <class T, class Container = std::deque<T>>
	class stack {
	public:
		stack() {}
		void push(const T& val) { _con.push_back(val); }
		void pop() { _con.pop_back(); }
		bool empty() const { return _con.empty(); }
		const size_t size() const { return _con.size(); }
		const T& top() const { return _con.back(); }
		T& top() { return _con.back(); }
	private:
		// 底层是容器 
		Container _con;
	};
}