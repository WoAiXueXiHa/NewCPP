#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <utility>

namespace Vect {
    // 维护一个二叉堆
    // Compare(a,b) == true 表示a的优先级低于b

    template <class T>
    struct myLess {
        // 返回 true 表示 a 小于 b
        // 用途：
        //   1) std::sort(vec.begin(), vec.end(), myLess<int>{})  → 升序
        //   2) std::priority_queue<int, std::vector<int>, myLess<int>>
        //        使用a<b为低优先级 → 形成大顶堆
        bool operator()(const T& a, const T& b) const { return a < b; }
    };

    template <class T>
    struct myGreater {
        // 返回 true 表示 a 大于 b
        // 用途：
        //   1) std::sort(vec.begin(), vec.end(), myGreater<int>{}) → 降序
        //   2) std::priority_queue<int, std::vector<int>, myGreater<int>>
        //        使用a>b为低优先级 → 形成小顶堆
        bool operator()(const T& a, const T& b) const { return a > b; }
    };


    template <class T, class Container = std::vector<T>, class Compare = myLess<T>>
    class priority_queue {
    public:
        // 默认构造 
        priority_queue() = default;
        // 迭代器区间构造
        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last) {
            while (first != last) {
                _con.push_back(*first);
                ++first;
            }
            // 建堆
            int n = (int)_con.size();
            for (int i = (n - 2) / 2; i >= 0; --i) {
                // 向下调整
                adjustDown(i);
            }
        }

        // 向上调整 
        void adjustUp(int child) {
            Compare comFunc;
            // 找父节点
            int parent = (child - 1) / 2;
            while (child > 0) {
                // if(_con[parent] < _con[child])
                if (comFunc(_con[parent], _con[child])) {
                    std::swap(_con[parent], _con[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else {
                    break;
                }
            }
        }

        // 向下调整
        void adjustDown(int parent) {
            Compare comFunc;
            // 假设左孩子是两个孩子中更大的
            int child = 2 * parent + 1;
            while (child < (int)_con.size()) {
                // 假设错误
                //  if (child + 1 < _con.size() && _con[child] < _con[child + 1])
                if (child + 1 < (int)_con.size() && comFunc(_con[child], _con[child + 1])) {
                    ++child;
                }
                // 比较孩子和父亲
                // if (_con[parent] > _con[child])
                if (comFunc(_con[parent], _con[child])) {
                    std::swap(_con[child], _con[parent]);
                    parent = child;
                    child = 2 * parent + 1;
                }
                else {
                    break;
                }
            }
        }

        // 交换堆顶堆底元素 删除堆底元素 向下调整
        void pop() {
            std::swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            if (!_con.empty()) adjustDown(0);
        }
        // 尾插 向上调整
        void push(const T& val) {
            _con.push_back(val);
            adjustUp((int)_con.size() - 1);
        }

        const T& top() const { return _con[0]; }
        T& top() { return _con[0]; }
        size_t size() const { return _con.size(); }
        bool empty() const { return _con.empty(); }

    private:
        Container _con;
    };

}
