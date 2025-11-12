#pragma once
#include "RBTree.h"

namespace Vect {
    // 映射容器：键Key，值ValueType；底层用红黑树存储 pair<const Key, ValueType>
    template<class Key, class ValueType>
    class map {
    public:
        // 从节点值类型 pair<Key, ValueType> 中抽取“键”的函数对象

        struct MapKeyOfV {
            // 这里形参写的是 pair<Key, ValueType> RBTree里实际ValueType是 pair<const Key, ValueType>
            const Key& operator()(const pair<Key, ValueType>& kv) const{
                return kv.first;
            }
        };

        // 复用RBTree的迭代器类型（ValueType为 pair<const Key, ValueType>）
        typedef typename RBTree<Key, pair<const Key, ValueType>, MapKeyOfV>::Iterator iterator;
        typedef typename RBTree<Key, pair<const Key, ValueType>, MapKeyOfV>::ConstIterator const_iterator;

        iterator begin() { return _tree.Begin(); }
        iterator end() { return _tree.End(); }
        const_iterator begin() const { return _tree.Begin(); }
        const_iterator end() const { return _tree.End(); }

        pair<iterator, bool> insert(const pair<Key, ValueType>& kv) { return _tree.Insert(kv); }

        ValueType& operator[](const Key& key) {
            // 先插入默认值 再通过迭代器找到ValueType
            pair<iterator, bool> ret = insert(make_pair(key, ValueType()));
            return ret.first->second;
        }

        iterator find(const Key& key) {
            return _tree.Find(key);
        }
    private:
        RBTree<Key, pair<const Key, ValueType>, MapKeyOfV> _tree;
    };

    void test_map()
    {
        map<string, string> dict;
        dict.insert({ "sort", "排序" });
        dict.insert({ "left", "左边" });
        dict.insert({ "right", "右边" });

        map<string, string>::iterator it = dict.begin();
        while (it != dict.end())
        {
            cout << it->first << ":" << it->second << endl;
            ++it;
        }
        cout << endl;
    }
}
   