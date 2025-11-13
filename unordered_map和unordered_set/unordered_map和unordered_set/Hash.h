#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace open_adress {
	/*
		最开始搭载基础框架 
		但是不是所有数据都是size_t类型 只有size_t能 %
		所以 多一个模板参数 将其余类型强转成size_t 特化string
	*/

	// 通用 Hash 函数模板：对一般 K 类型，直接将 key 转成 size_t。
	// 注意：如果 K 为自定义类型，需要自行提供 Hash 的特化/仿函数；
	/*
		如果 K 为有符号整数，负值强转为 size_t 会变成很大的无符号数，
		但再取模映射到桶时仍然可用（只是数值看起来很大）。
	*/
	template<class K>
	struct HashFunc {
		size_t operator() (const K& key){
			return (size_t)key;
		}
	};
	// 特化string 常见的 31 进制滚动哈希
	template<>
	struct HashFunc<string> {
		size_t operator()(const string& key) {
			size_t hash = 0;
			for (const auto& e : key) {
				hash *= 31; // 31进制滚动
				hash += e;  // ASCII累加
			}
			return hash;
		}
	};
	// 状态
	enum STATE{ EMPTY, DELETE, EXIST};
	// 哈希数据
	template<class K, class V>
	struct HashData {
		STATE _state = EMPTY;
		pair<K, V> _kv;
	};

	// 哈希表
	// Hash 缺省为上面的 HashFunc<K>
	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable {
	private:
		vector<HashData<K, V>> _tables;
		size_t _nums;
	public:
		HashTable() { _tables.resize(10); }

		// key存在返回false
		bool Insert(const pair<K, V>& kv) {

			// 负载因子 避免小表过多冲突 超过0.7扩容
			if (_nums * 10 / _tables.size() >= 7) {
				// 开一个两倍大的新表 把旧表的数据重新映射到新表 
				HashTable<K, V,Hash> newHT;
				newHT._tables.resize(_tables.size() * 2);

				for (size_t i = 0; i < _tables.size(); i++)
				{
					// 只映射EXIST的值
					if (_tables[i]._state == EXIST) {
						newHT.Insert(_tables[i]._kv);
					}
				}
				// 交换两表  
				_tables.swap(newHT._tables);

			}
			// 直接找映射位置
			Hash hs; // 把数据类型转成size_t
			size_t hashIdx = hs(kv.first) % _tables.size();
			// 跳过存在的位置 找空位置插入
			while (_tables[hashIdx]._state == EXIST) {
				++hashIdx;
				hashIdx %= _tables.size(); // 防止越界
			}
			// 插入
			_tables[hashIdx]._kv = kv;
			_tables[hashIdx]._state = EXIST;
			++_nums;

			return true;
		}

		// 查找 按key查找 
		HashData<K, V>* Find(const K& key) {
			// 一上来直接从映射位置开始找
			Hash hs; // 把数据类型转成size_t
			size_t hashIdx = hs(key) % _tables.size();
			// 循环只要不是空就找
			while (_tables[hashIdx]._state != EMPTY) {
				// 遇到相同的值就返回地址
				if (_tables[hashIdx]._state == EXIST && _tables[hashIdx]._kv.first == key) {
					return &_tables[hashIdx];
				}
				++hashIdx;
				hashIdx %= _tables.size();
			}

			return nullptr;
		}

		// 删除
		bool Erase(const K& key) {
			HashData<K, V>* ret = Find(key);
			if (ret == nullptr) return false;
			else {
				ret->_state = DELETE;
				//--_nums;		不用减 负载因子只增不减
				return true;
			}
		}
	};

	void testHash() {
		vector<int> arr = { 31,25,99,157,26,344,257 };
		HashTable<int, int> h;
		for (const auto& e : arr) h.Insert({ e,e });
	}
}

// 哈希桶 链表挂冲突的值
namespace hash_bucket {
	template <class K>
	struct HashFunc {
		size_t operator()(const K& key) { return (size_t)key; }
	};

	template<>
	struct HashFunc<string> {
		size_t operator()(const string& key) {
			size_t hash = 0;
			for (const auto& e : key) {
				hash *= 31;
				hash += e;
			}
			return hash;
		}
	};

	template<class K,class V>
	struct HashNode {
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K,V>& kv)
			:_kv(kv)
			,_next(nullptr)
		{ }
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable {
		typedef HashNode<K, V> Node;
	private:
		vector<Node*> _tables;
		size_t _nums = 0;
	public:
		HashTable() { _tables.resize(10,nullptr); }

		// 插入 
		bool Insert(const pair<K, V>& kv) {

			// 扩容 这时负载因子可达到一再扩容
			if (_nums == _tables.size()) {
				// 重新分配更大的桶
				vector<Node*> newTable(2 * _tables.size(), nullptr);
				// 这里不能复用Insert的逻辑了 
				// 如果复用 会删除_nums个节点 再new_nums个节点 效率低
				// 好的解决方法是将旧桶的节点 重新映射到新桶挂着
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;
						// 旧节点在新桶中的新的映射位置
						size_t newHashIdx = cur->_kv.first % newTable.size();
						// 头插到对应新桶
						cur->_next = newTable[newHashIdx];
						newTable[newHashIdx] = cur;

						cur = next;
					}
					_tables[i] = nullptr; // 清空旧桶指针
				}
				_tables.swap(newTable);	// 交换新旧桶
			}
			
			// 先找映射位置
			Hash hs;
			size_t hashIdx = hs(kv.first) % _tables.size();
			// 头插到对应桶的位置
			Node* newNode = new Node(kv);
			newNode->_next = _tables[hashIdx];
			_tables[hashIdx] = newNode;
			++_nums;
			
			return true;
		}

		Node* Find(const K& key) {
			Hash hs;
			size_t hashIdx = hs(key) % _tables.size();
			Node* cur = _tables[hashIdx];
			while (cur) {
				if (cur->_kv.first == key) {
					return cur;
				}
				cur = cur->_next;
			}
			return false;
		}

		// 删除
		bool Erase(const K& key) {
			Hash hs;
			size_t hashIdx = hs(key) % _tables.size();

			Node* prev = nullptr;
			Node* cur = _tables[hashIdx];
			while (cur) {
				if (cur->_kv.first == key) {
					if (prev == nullptr) {	// 头删
						_tables[hashIdx] = cur->_next;
					}
					else {
						prev->_next = cur->_next;	// 中间/尾删
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