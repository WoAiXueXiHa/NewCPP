#pragma once
#include <iostream>
#include <vector>

namespace Vect {
	// 第二个参数：适配器 传一个容器
	template <class T, class Container = std::vector<T>>
	class stack {
	public:
		void push(const T& val) { _con.push_back(val); }
		void pop() { _con.pop_back(); }
		bool empty() const { return _con.empty(); }
		const size_t size() const { return _con.size(); }
		const T top() const { return _con.front(); }
	private:
		// 底层是容器 
		Container _con;
	};
}