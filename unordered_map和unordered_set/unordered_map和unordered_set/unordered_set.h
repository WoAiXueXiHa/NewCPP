#pragma once
#include "Hash.h"

#pragma once
#include "Hash.h"

namespace Vect {

    // =============================
    // 自己封装的 unordered_set：
    //   - 底层使用 hash_bucket::HashTable
    //   - 只存 key（没有 value）
    // =============================
    template<class K, class Hash = hash_bucket::HashFunc<K>>
    class unordered_set {
        // 从 T 中抽 key 的仿函数：
        // 对于 set，T 本身就是 K（或者 const K），所以直接返回。
        struct SetKeyOfT {
            const K& operator()(const K& key) const {
                return key;
            }
        };

        // T 使用 const K：
        //   - 这样通过迭代器访问到的元素类型是 const K&
        //   - 禁止修改 key（防止“改 key 没 rehash”导致哈希表结构错乱）
        typedef hash_bucket::HashTable<K, const K, SetKeyOfT, Hash> HT;

    public:
        // 迭代器类型，直接复用底层 HashTable 的迭代器
        typedef typename HT::Iterator iterator;
        typedef typename HT::ConstIterator const_iterator;

        unordered_set() = default;

        iterator begin() { return _ht.Begin(); }
        iterator end() { return _ht.End(); }
        const_iterator begin() const { return _ht.Begin(); }
        const_iterator end() const { return _ht.End(); }

        pair<iterator, bool> insert(const K& key) { return _ht.Insert(key); }

        iterator find(const K& key) { return _ht.Find(key); }

        // 删除 key
        bool erase(const K& key) { return _ht.Erase(key); }
    private:
        HT _ht; // 底层哈希表
    };

    void TestUnorderedSetBasic()
    {
        cout << "===== TestUnorderedSetBasic =====" << endl;

        unordered_set<int> s;

        // 1. insert 基本测试
        s.insert(10);
        s.insert(20);
        s.insert(30);
        s.insert(20); // 重复插入，看实现是否直接忽略

        cout << "[1] after insert:" << endl;
        for (auto it = s.begin(); it != s.end(); ++it)
        {
            cout << "  " << *it << endl;
        }
        cout << endl;

        // 2. find 测试
        cout << "[2] find test:" << endl;
        auto it = s.find(20);
        if (it != s.end())
        {
            cout << "  find(20) success: " << *it << endl;
        }
        else
        {
            cout << "  20 not found" << endl;
        }

        auto it2 = s.find(99);
        if (it2 == s.end())
        {
            cout << "  find(99) = end (not found)" << endl;
        }
        cout << endl;

        // 3. erase 测试
        cout << "[3] erase(10)" << endl;
        s.erase(10);
        for (auto it = s.begin(); it != s.end(); ++it)
        {
            cout << "  " << *it << endl;
        }

        cout << "===== TestUnorderedSetBasic End =====" << endl << endl;
    }
}
