#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <utility>

namespace Vect {
    // ά��һ�������
    // Compare(a,b) == true ��ʾa�����ȼ�����b

    template <class T>
    struct myLess {
        // ���� true ��ʾ a С�� b
        // ��;��
        //   1) std::sort(vec.begin(), vec.end(), myLess<int>{})  �� ����
        //   2) std::priority_queue<int, std::vector<int>, myLess<int>>
        //        ʹ��a<bΪ�����ȼ� �� �γɴ󶥶�
        bool operator()(const T& a, const T& b) const { return a < b; }
    };

    template <class T>
    struct myGreater {
        // ���� true ��ʾ a ���� b
        // ��;��
        //   1) std::sort(vec.begin(), vec.end(), myGreater<int>{}) �� ����
        //   2) std::priority_queue<int, std::vector<int>, myGreater<int>>
        //        ʹ��a>bΪ�����ȼ� �� �γ�С����
        bool operator()(const T& a, const T& b) const { return a > b; }
    };


    template <class T, class Container = std::vector<T>, class Compare = myLess<T>>
    class priority_queue {
    public:
        // Ĭ�Ϲ��� 
        priority_queue() = default;
        // ���������乹��
        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last) {
            while (first != last) {
                _con.push_back(*first);
                ++first;
            }
            // ����
            int n = (int)_con.size();
            for (int i = (n - 2) / 2; i >= 0; --i) {
                // ���µ���
                adjustDown(i);
            }
        }

        // ���ϵ��� 
        void adjustUp(int child) {
            Compare comFunc;
            // �Ҹ��ڵ�
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

        // ���µ���
        void adjustDown(int parent) {
            Compare comFunc;
            // �������������������и����
            int child = 2 * parent + 1;
            while (child < (int)_con.size()) {
                // �������
                //  if (child + 1 < _con.size() && _con[child] < _con[child + 1])
                if (child + 1 < (int)_con.size() && comFunc(_con[child], _con[child + 1])) {
                    ++child;
                }
                // �ȽϺ��Ӻ͸���
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

        // �����Ѷ��ѵ�Ԫ�� ɾ���ѵ�Ԫ�� ���µ���
        void pop() {
            std::swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            if (!_con.empty()) adjustDown(0);
        }
        // β�� ���ϵ���
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
