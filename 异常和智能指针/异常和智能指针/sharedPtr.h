#pragma once
#include<functional>

namespace sharedPtr {
    template <class T>
    class shared_ptr {
    private:
        T* _ptr;                  // 指向资源的指针
        int* _refConut;           // 引用计数指针，记录有多少个 shared_ptr 管理同一个资源
        // 自定义删除器，可以删除任意类型的对象（默认使用 delete）
        std::function<void(T* ptr)> _del = [](T* ptr) { delete ptr; };

    public:
        shared_ptr(const T* ptr = nullptr)
            : _ptr(ptr), _refConut(new int(1))  // 初始化引用计数为 1，表示资源有一个管理者
        {
            std::cout << "shared_ptr构造: " << _ptr << " 数量: " << _refConut << std::endl;
        }

        // 构造函数：传入自定义删除器
        template <class D>
        shared_ptr(const T* ptr = nullptr, D del)
            : _ptr(ptr), _del(del), _refConut(new int(1))  // 自定义删除器
        {
            std::cout << "shared_ptr(const T* ptr = nullptr, D del)" << std::endl;
        }

        // 拷贝构造函数：增加引用计数
        shared_ptr(const shared_ptr<T>& other)
            : _ptr(other._ptr), _refConut(other._refConut)
        {
            ++(*_refConut);  // 引用计数加 1
        }

        // 释放资源：当引用计数减少为 0 时，释放资源
        void release() {
            if (--(*_refConut) == 0) {  
                _del(_ptr);  
                delete _refConut;  
                _ptr = nullptr;  
                _refConut = nullptr;  
            }
        }

        // 赋值运算符重载：释放旧资源，增加引用计数
        shared_ptr<T>& operator=(const shared_ptr<T>& other) {
            if (this != &other) {  // 防止自赋值
                release();  
                _ptr = other._ptr;  
                _refConut = other._refConut;  
                ++(*_refConut);  
            }
            return *this;
        }

        // 析构函数：调用 release 释放资源
        ~shared_ptr() { release(); }

        // 解引用运算符：返回指向的对象
        T* operator->() { return _ptr; }
        T& operator*() { return *_ptr; }

        // 获取原始指针
        T* get() { return _ptr; }

        // 获取当前引用计数
        int useCount() { return *_refConut; }
    };

    template <class T>
    class weak_ptr {
    private:
        T* _ptr = nullptr;
    public:
        weak_ptr() = default;
        weak_ptr(const shared_ptr<T>& sp)
            :_ptr(sp._ptr)  // 将 shared_ptr 的资源指针 _ptr 复制到 weak_ptr 的 _ptr 成员中
        {
            // 这里的构造函数将一个 shared_ptr 转换为 weak_ptr。
            // weak_ptr 不增加引用计数，它仅仅观察 shared_ptr 管理的资源。
            // 这样设计使得 weak_ptr 可以在不干扰资源生命周期的情况下，观察资源是否存在。
        }

        weak_ptr<T>& operator=(const shared_ptr<T>& other) {
            _ptr = other.get();  // 获取 shared_ptr 的资源指针并赋给 weak_ptr 的 _ptr 成员

            return *this;  // 返回当前的 weak_ptr 对象，以支持链式赋值操作
        }

        ~weak_ptr() {}
    };

    template <class T>
    struct ListNode {
        ListNode<T>* _prev = nullptr;
        ListNode<T>* _next = nullptr;

        ListNode() = default;
    };

    void test() {
        // 创建两个 ListNode<int> 节点，分别由 shared_ptr 管理
        shared_ptr<ListNode<int>> n1(new ListNode<int>);
        shared_ptr<ListNode<int>> n2(new ListNode<int>);

        // 形成双向链表关系
        //n1->_next = n2;   // n1 指向 n2
        //n2->_prev = n1;   // n2 指向 n1

        // 循环引用：n1 和 n2 互相持有对方的 shared_ptr
        // 当 test() 函数结束时，n1 和 n2 的引用计数永远不会为 0，资源不会被释放
    }
}
