#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <string>         
#include <cmath>          

namespace Vect {
    // 维护一个二叉堆
    // Compare(a,b) == true 表示a的优先级低于b

    // 按照绝对值大的优先 |a| < |b|
    template <class T>
    struct absLess {
        bool operator()(const T& a, const T& b) const { return std::abs(a) < std::abs(b); }
    };
    // 按字符串长度大的优先 a.size() < b.size()
    struct strLess {
        bool operator()(const std::string& a, const std::string& b) {
            return a.size() < b.size();
        }
    };

    // 按照结构体比较 分数高的优先 分数相同的按照名字字典序优先
    struct StudentInfo {
        int score;
        std::string name;
    };
    struct structLess {
        // 返回 true 表示 左操作数 优先级 低 于 右操作数
        bool operator()(const StudentInfo& stuA, const StudentInfo& stuB) const {
            if (stuA.score != stuB.score) return stuA.score < stuB.score; // 分数高的优先
            return stuA.name > stuB.name; // 分数相同，name 小的优先（ASCII 小在前）
        }
    };

    template <class T>
    struct myLess {
        bool operator()(const T& a, const T& b) const { return a < b; }
    };

    template <class T>
    struct myGreater {
        bool operator()(const T& a, const T& b) const { return a > b; }
    };

    template <class T, class Container = std::vector<T>, class Compare = myLess<T>>
    class priority_queue {
    public:
        const T& operator[](size_t i) const { return _con[i]; }
        priority_queue() = default;

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last) {
            while (first != last) {
                _con.push_back(*first);
                ++first;
            }
            int n = (int)_con.size();
            for (int i = (n - 2) / 2; i >= 0; --i) {
                adjustDown(i);
            }
        }

        void adjustUp(int child) {
            Compare comFunc;
            int parent = (child - 1) / 2;
            while (child > 0) {
                if (comFunc(_con[parent], _con[child])) {
                    std::swap(_con[parent], _con[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else break;
            }
        }

        void adjustDown(int parent) {
            Compare comFunc;
            int child = 2 * parent + 1;
            while (child < (int)_con.size()) {
                if (child + 1 < (int)_con.size() && comFunc(_con[child], _con[child + 1])) {
                    ++child;
                }
                if (comFunc(_con[parent], _con[child])) {
                    std::swap(_con[child], _con[parent]);
                    parent = child;
                    child = 2 * parent + 1;
                }
                else break;
            }
        }

        void pop() {
            std::swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            if (!_con.empty()) adjustDown(0);
        }
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
