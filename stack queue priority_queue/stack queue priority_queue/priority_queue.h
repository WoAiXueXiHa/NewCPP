#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <string>         
#include <cmath>          

namespace Vect {
    // ά��һ�������
    // Compare(a,b) == true ��ʾa�����ȼ�����b

    // ���վ���ֵ������� |a| < |b|
    template <class T>
    struct absLess {
        bool operator()(const T& a, const T& b) const { return std::abs(a) < std::abs(b); }
    };
    // ���ַ������ȴ������ a.size() < b.size()
    struct strLess {
        bool operator()(const std::string& a, const std::string& b) {
            return a.size() < b.size();
        }
    };

    // ���սṹ��Ƚ� �����ߵ����� ������ͬ�İ��������ֵ�������
    struct StudentInfo {
        int score;
        std::string name;
    };
    struct structLess {
        // ���� true ��ʾ ������� ���ȼ� �� �� �Ҳ�����
        bool operator()(const StudentInfo& stuA, const StudentInfo& stuB) const {
            if (stuA.score != stuB.score) return stuA.score < stuB.score; // �����ߵ�����
            return stuA.name > stuB.name; // ������ͬ��name С�����ȣ�ASCII С��ǰ��
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
