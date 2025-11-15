#pragma once
#include "Hash.h"

namespace Vect {

    // =============================
    //   - 底层使用 hash_bucket::HashTable
    //   - 存储类型为 pair<const K, V>
    // =============================
    template<class K, class V, class Hash = hash_bucket::HashFunc<K>>
    class unordered_map {
        // 从 pair<const K, V> 中抽取 key 的仿函数：
        //   - 这是给 HashTable 用的 KeyOfT
        //   - 使得 HashTable 不需要知道 T 的结构，完全依赖这个仿函数抽 key
        struct MapKeyOfT {
            const K& operator()(const pair<const K, V>& kv) const {
                return kv.first;    // key 在 first 里
            }
        };

        // 底层哈希表类型：
        //   K: key 类型
        //   T: pair<const K, V> —— 让 key 变成 const，禁止通过迭代器修改 key
        //   KeyOfT: MapKeyOfT —— 从 T 中抽出 key
        //   Hash: hash 函数对象，默认 hash_bucket::HashFunc<K>
        typedef hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash> HT;

    public:
        // 公开迭代器类型，直接复用底层 HashTable 的迭代器
        typedef typename HT::Iterator iterator;
        typedef typename HT::ConstIterator const_iterator;

        unordered_map() = default;

        iterator begin() { return _ht.Begin(); }
        iterator end() { return _ht.End(); }

        const_iterator begin() const { return _ht.Begin(); }
        const_iterator end() const { return _ht.End(); }

        // 插入一个 pair<K,V>：
        //   - 底层 T 是 pair<const K,V>，可以通过 {K,V} 隐式构造
        //   - 返回值是 <iterator,bool>，语义和 STL 一样：
        //       * 第二个为 true：插入成功
        //       * 第二个为 false：key 已存在，first 指向已有元素
        pair<iterator, bool> insert(const pair<K, V>& kv) { return _ht.Insert(kv); }

        // 查找 key 对应元素（非 const 版本）
        iterator find(const K& key) { return _ht.Find(key); }

        // 删除 key 对应的元素，返回是否删除成功
        bool erase(const K& key) { return _ht.Erase(key); }

        // operator[]：
        //   语义仿照 STL：
        //     - 若 key 不存在：插入 {key, V()}，返回新插入元素的 value 引用
        //     - 若 key 已存在：返回已有元素的 value 引用
        V& operator[](const K& key) {
            // 先尝试插入 {key, V()}，底层 Insert 会负责查重：
            //   - 不存在：插入新节点并返回 {新位置, true}
            //   - 已存在：返回 {旧位置, false}
            auto ret = _ht.Insert(make_pair(key, V()));

            // 不管是新插入的还是原来存在的，ret.first 都指向该 key 的 pair<const K,V>
            // first->second 就是 value 的引用
            return ret.first->second;
        }
    public:
    private:
        HT _ht;  // 底层哈希表
    };

    void TestUnorderedMapBasic()
    {
        cout << "===== TestUnorderedMapBasic =====" << endl;

        unordered_map<string, int> m;

        // 1. insert 基本测试
        m.insert({ "apple", 1 });
        m.insert({ "banana", 2 });
        m.insert({ "cat", 3 });

        cout << "[1] after insert:" << endl;
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            cout << "  " << it->first << " -> " << it->second << endl;
        }
        cout << endl;

        // 2. operator[] 测试：访问不存在的 key，会插入默认值
        cout << "[2] operator[] test:" << endl;
        cout << "  m[\"dog\"] (before assign) = " << m["dog"] << endl; // 应该插入 { "dog", 0 }
        m["dog"] = 100; // 修改 value
        m["apple"] += 10; // 修改已有 key 的 value

        cout << "  after m[\"dog\"] = 100 and m[\"apple\"] += 10:" << endl;
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            cout << "  " << it->first << " -> " << it->second << endl;
        }
        cout << endl;

        // 3. find 测试
        cout << "[3] find test:" << endl;
        auto it = m.find("banana");
        if (it != m.end())
        {
            cout << "  find(\"banana\") = " << it->second << endl;
        }
        else
        {
            cout << "  banana not found" << endl;
        }

        auto it2 = m.find("xxxx");
        if (it2 == m.end())
        {
            cout << "  find(\"xxxx\") = end (not found)" << endl;
        }
        cout << endl;

        // 4. erase 测试
        cout << "[4] erase(\"cat\")" << endl;
        m.erase("cat");
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            cout << "  " << it->first << " -> " << it->second << endl;
        }

        cout << "===== TestUnorderedMapBasic End =====" << endl << endl;
    }
}
