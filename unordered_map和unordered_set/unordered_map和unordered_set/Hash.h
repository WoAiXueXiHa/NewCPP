#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace hash_bucket {

    // 通用哈希函数对象模板：
    // 对任意 T，默认做一个简单的强制类型转换： (size_t)key
    // 适用于整型等可以安全转换到 size_t 的类型。
    template<class T>
    struct HashFunc {
        size_t operator()(const T& key) { return (size_t)key; }
    };

    // 针对 string 的特化版本：
    // 实现一个常见的字符串 hash：
    // hash = hash * 31 + 字符
    template<>
    struct HashFunc<string> {
        size_t operator()(const string& s) {
            size_t hash = 0;
            for (const auto& e : s) {
                hash *= 31;
                hash += e;
            }
            return hash;
        }
    };

    // =============================
    //  节点结构：HashNode<T>
    //  - 用于拉链法哈希桶中的链表节点
    //  - 模板参数 T 是“真实存储类型”
    //      * 对 unordered_map 来说：T = pair<const K, V>
    //      * 对 unordered_set 来说：T = const K
    // =============================
    template<class T>
    struct HashNode {
        HashNode<T>* _next; // 指向下一个节点，形成单链表
        T _data;            // 存放真实数据 T

        HashNode(const T& data)
            :_next(nullptr)
            , _data(data)
        {
        }
    };

    // -----------------------
    // 哈希表迭代器 HTIterator：前向迭代器
    //    K, T     和 HashTable 模板参数一致：
    //             K 是 key 类型，T 是哈希表中真实存的类型
    //    Ptr, Ref 控制当前是普通迭代器还是 const 迭代器：
    //             - 普通迭代器：Ptr = T*，Ref = T&
    //             - const 迭代器：Ptr = const T*，Ref = const T&
    //    KeyOfT   用于从 T 中抽取 key（T -> K），便于 ++ 时定位当前桶
    //    Hash     哈希函数对象，对 key 做 hash
    // -----------------------

    // 注意：HTIterator 需要用到 HashTable 的定义，
    // 所以在它前面会有 HashTable 的前置声明（见后面）。
    template<class K, class T, class KeyOfT, class Hash>
    class HashTable;

    template<class K, class T, class Ptr, class Ref, class KeyOfT, class Hash>
    struct HTIterator {
        typedef HashNode<T> Node;
        typedef HashTable<K, T, KeyOfT, Hash> HT;           // 方便起名
        typedef HTIterator<K, T, Ptr, Ref, KeyOfT, Hash> Self;

        Node* _node;        // 当前所指向的节点
        const HT* _pht;     // 指向整张哈希表，用于 ++ 时跨桶寻找下一个元素

        HTIterator(Node* node, const HT* pht)
            :_node(node)
            , _pht(pht)
        {
        }

        // 解引用：*it
        // 返回当前节点里存的 T 的引用：
        //   普通迭代器 -> T&
        //   const 迭代器 -> const T&
        Ref operator*() const { return _node->_data; }

        // 成员访问：it->xxx
        // 返回 T* 或 const T*
        Ptr operator->() const { return &_node->_data; }

        // 比较运算：只比较当前节点指针是否相同，
        // End() 被约定为 _node == nullptr
        bool operator!=(const Self& s) const { return _node != s._node; }
        bool operator==(const Self& s) const { return _node == s._node; }

        // 前置 ++ ：
        // 遍历顺序：
        //   1. 先在当前桶的链表中往后走
        //   2. 当前桶链表走完后，跨桶去找“后面的第一个非空桶”
        Self& operator++() {
            if (_node == nullptr) return *this; // 已经是 End()，++ 不做事

            if (_node->_next) {
                // 情况1：当前桶内链表还有下一个节点
                // 直接在链表中前进
                _node = _node->_next;
            }
            else {
                // 情况2：当前节点是桶内最后一个节点，需要“跨桶”寻找下一个有元素的桶
                KeyOfT kot;
                Hash hs;

                // 先算出当前节点所在桶号：
                // 通过 KeyOfT 从 T 中抽出 key，再通过 Hash 计算 hash 值
                size_t hashIdx = hs(kot(_node->_data)) % _pht->_tables.size();

                ++hashIdx;	// 从“下一个桶”开始向后找
                while (hashIdx < _pht->_tables.size()) {
                    if (_pht->_tables[hashIdx]) {
                        // 找到下一个非空桶的第一个节点
                        _node = _pht->_tables[hashIdx];
                        return *this;
                    }
                    ++hashIdx;
                }
                // 后面的桶都为空，说明到达整个哈希表的末尾
                // 用 _node == nullptr 表示 End()
                _node = nullptr;
            }
            return *this;
        }
    };

    /*
        通用哈希桶 HashTable 的模板参数：
        K       key 的类型
        T       真实存储的元素类型：
                - unordered_map: T = pair<const K, V>
                - unordered_set: T = const K
        KeyOfT  从 T 中抽出 key 的仿函数（T -> K）
        Hash    对 key 做哈希的仿函数，默认使用 HashFunc<K>
    */
    template<class K, class T, class KeyOfT, class Hash = HashFunc<K>>
    class HashTable {
        typedef HashNode<T> Node;   // 节点里存的是 T，而不是 K

        // 让迭代器可以访问 HashTable 的内部（尤其是 _tables）
        template<class K, class T, class Ptr, class Ref, class KeyOfT, class Hash>
        friend struct HTIterator;
    private:
        vector<Node*> _tables;  // 桶数组，每个元素是链表头指针
        size_t _nums = 0;       // 当前存储的元素个数
    public:

        // 基础迭代器类型：
        // Ptr -> T*, Ref -> T& （可修改 T）
        typedef HTIterator<K, T, T*, T&, KeyOfT, Hash> Iterator;
        // const 迭代器类型：
        // Ptr -> const T*, Ref -> const T& （只读）
        typedef HTIterator<K, T, const T*, const T&, KeyOfT, Hash> ConstIterator;


        HashTable() { _tables.resize(10); }

        // 析构函数：释放所有桶中链表的节点
        ~HashTable() {
            for (size_t i = 0; i < _tables.size(); i++)
            {
                Node* cur = _tables[i];
                while (cur) {
                    Node* next = cur->_next;
                    delete cur;
                    cur = next;
                }
                _tables[i] = nullptr;
            }
        }

        //------------------
        //  Begin() / End() —— 非 const 版本
        //------------------
        Iterator Begin() {
            if (_nums == 0) return End(); // 空表，直接返回 End()

            // 找到第一个非空桶，返回这个桶链表的头结点
            for (size_t i = 0; i < _tables.size(); i++)
            {
                if (_tables[i])
                    return Iterator(_tables[i], this);
            }
            // 理论上不会到这里（_nums > 0 一定有非空桶）
            return End();
        }
        Iterator End() {
            // 用 _node == nullptr 表示 End()
            return Iterator(nullptr, this);
        }

        //------------------
        //  Begin() / End() —— const 版本
        //------------------
        ConstIterator Begin() const {
            if (_nums == 0) return End(); // 这里调用的是 const End()（编译器选 const 重载）

            for (size_t i = 0; i < _tables.size(); i++)
            {
                if (_tables[i])
                    return ConstIterator(_tables[i], this);
            }
            return End();
        }
        ConstIterator End() const {
            return ConstIterator(nullptr, this);
        }

        //-------------------
        // 插入 Insert
        // 1. 用 KeyOfT 从 data 中抽取 key，先查重
        // 2. 如有必要，进行扩容（rehash）
        // 3. 把新节点头插到对应桶
        // 返回值：<Iterator, bool>
        //   - first：新插入的位置 / 已有元素的位置
        //   - second：true 表示插入成功，false 表示 key 已存在
        //-------------------

        pair<Iterator, bool> Insert(const T& data) {

            KeyOfT kot;

            // 1. 查重：从 data 中抽 key，然后查表
            //   如果 key 已存在，返回已有迭代器 + false
            Iterator it = Find(kot(data));
            if (it != End()) return make_pair(it, false);

            // 2. 扩容逻辑：
            //    开一个新的 vector<Node*> 表，把旧表中的节点搬运到新表，
            //    自己控制新表的映射位置（rehash）。
            //    不复用 Insert，是为了避免 delete n 个 + new n 个带来的低效。
            Hash hs;
            size_t hashIdx = hs(kot(data)) % _tables.size();

            // 这里的扩容条件写的是：元素个数 == 桶数
            // 实际项目中一般会用“负载因子”（_nums / _tables.size() > 某阈值）
            if (_nums == _tables.size()) {
                vector<Node*> newTables(2 * _tables.size(), nullptr);
                for (size_t i = 0; i < _tables.size(); i++)
                {
                    Node* cur = _tables[i];
                    while (cur) {
                        Node* next = cur->_next;
                        // 把旧表中的节点映射到新表中：
                        // 这里一定要用 newTables.size() 取模，而不是 _tables.size()
                        hashIdx = hs(kot(cur->_data)) % newTables.size();
                        // 头插到新表的对应桶
                        cur->_next = newTables[hashIdx];
                        newTables[hashIdx] = cur;

                        cur = next;
                    }
                    _tables[i] = nullptr;
                }
                _tables.swap(newTables);
            }

            // 3. 插入：头插到当前表中对应的桶
            hashIdx = hs(kot(data)) % _tables.size();
            Node* newNode = new Node(data);
            newNode->_next = _tables[hashIdx];
            _tables[hashIdx] = newNode;
            ++_nums;

            //   注意：这里有一个易错点：
            //   return make_pair((newNode,this),true);
            //   (newNode, this) 在 C++ 里是“逗号表达式”，结果其实是 this（HashTable*），不是迭代器。
            //   正确写法应该是先构造迭代器 Iterator it(newNode, this); 再 return make_pair(it, true);
            Iterator ret(newNode, this);
            return make_pair(ret, true);
        }

        // 在哈希表中查找 key 对应的元素，返回迭代器：
        //   - 找到：返回指向该元素的迭代器
        //   - 找不到：返回 End()
        Iterator Find(const K& key) {
            KeyOfT kot;
            Hash hs;
            size_t hashIdx = hs(key) % _tables.size();

            Node* cur = _tables[hashIdx];
            while (cur) {
                if (kot(cur->_data) == key) {
                    return Iterator(cur, this);
                }

                cur = cur->_next;
            }
            return End();
        }

        // 删除 key 对应的元素：
        //   - 找到：从链表中摘除，释放节点，_nums--，返回 true
        //   - 找不到：返回 false
        bool Erase(const K& key) {
            KeyOfT kot;
            Hash hs;
            size_t hashIdx = hs(key) % _tables.size();

            Node* cur = _tables[hashIdx];
            Node* prev = nullptr;
            while (cur) {
                if (kot(cur->_data) == key) {
                    if (prev == nullptr) {
                        // 删除的是桶头节点
                        _tables[hashIdx] = cur->_next;
                    }
                    else {
                        // 删除的是中间节点
                        prev->_next = cur->_next;
                    }
                    delete cur;
                    --_nums;
                    return true;
                }
                prev = cur;
                cur = cur->_next;
            }
            return false;
        }
    };
} 
