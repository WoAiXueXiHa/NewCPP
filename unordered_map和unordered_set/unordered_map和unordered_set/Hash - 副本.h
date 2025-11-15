#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 开放定址 线性探测
/*
	1. 先实现简单的哈希表 满足整型寻找映射位置即可
	2. 然后再添加其他类型转到整型的方法
*/
namespace open_adress {

	enum STATE{EMPTY, DELETE, EXIST};

	template<class K>
	struct HashFunc {
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};
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

	template<class K, class ValueType>
	struct HashData {
		pair<K, ValueType> _kv;
		STATE _state = EMPTY;
	};

	template<class K, class ValueType, class Hash = HashFunc<K>>
	class HashTable {
	private:
		vector<HashData<K, ValueType>> _tables;
		size_t _nums = 0;
	public:
		HashTable() { _tables.resize(10); }

		// 插入
		bool Insert(const pair<K, ValueType>& kv) {
			// 1. 查重
			if (Find(kv.first)) return false;
			// 2. 扩容
			// 创建新的哈希表 复用Insert后面部分的逻辑 完成旧数据映射到新表
			if (_nums * 10 / _tables.size() >= 7) {
				HashTable<K, ValueType> newHT;
				newHT._tables.resize(2 * _tables.size());
				for (size_t i = 0; i < _tables.size(); i++)
				{
					if (_tables[i]._state == EXIST) {
						newHT.Insert(_tables[i]._kv);
					}
				}
				_tables.swap(newHT._tables);
			}

			// 3. 插入
			Hash hs;
			size_t hashIdx = hs(kv.first) % _tables.size();
			while (_tables[hashIdx]._state == EXIST) {
				++hashIdx;
				hashIdx %= _tables.size();
			}
			_tables[hashIdx]._kv = kv;
			_tables[hashIdx]._state = EXIST;
			++_nums;

			return true;
		}

		// 查找 越过EMPTY 且保证EXIST
		HashData<K,ValueType>* Find(const K& key) {
			Hash hs;
			size_t hashIdx = hs(key) % _tables.size();

			while (_tables[hashIdx]._state != EMPTY) {
				if (_tables[hashIdx]._state == EXIST
					&& _tables[hashIdx]._kv.first == key)
					return &_tables[hashIdx];
				++hashIdx;
				hashIdx %= _tables.size();
			}
			return nullptr;
		}

		// 删除 调用Find 
		bool Erase(const K& key) {
			HashData<K, ValueType>* ret = Find(key);
			if (ret == nullptr) return false;
			else {
				ret->_state = DELETE;
				return true;
			}
		}
	};

	void TestOpenAdress() {
		HashTable<int, int> hs;
		int arr[] = { 12,31,51,44,23,54,88,97 };
		for (const auto& e : arr) hs.Insert({ e,e });

		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
		{
			hs.Erase(arr[i]);
		}
	}

}

namespace hash_bucket {
	template<class K>
	struct HashFunc {
		size_t operator()(const K& key) { return (size_t)key; }
	};
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

	template<class K, class ValueType>
	struct HashNode {
		HashNode<K, ValueType>* _next;
		pair < K, ValueType> _kv;

		HashNode(const pair<K,ValueType>& kv)
			:_next(nullptr)
			,_kv(kv)
		{ }
	};

	template<class K, class ValueType, class Hash = HashFunc<K>>
	class HashTable {
		typedef HashNode<K, ValueType> Node;
	private:
		vector<Node*> _tables;
		size_t _nums = 0;
	public:
		HashTable() { _tables.resize(10); }
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

		// 插入 
		bool Insert(const pair<K, ValueType>& kv) {
			// 1. 查重
			Node* ret = Find(kv.first);
			if (ret) return false;

			// 2. 扩容
			// 扩容逻辑： 建一张新的vector表 把旧表的节点搬运到新表 自己控制新表映射位置
			// 为什么不复用Insert？
			// 会delete n个节点 new n个节点 低效
			Hash hs;
			size_t hashIdx = hs(kv.first) % _tables.size();
			if (_nums == _tables.size()) {
				vector<Node*> newTables(2 * _tables.size(), nullptr);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;
						// 旧表节点映射到新表
						hashIdx = hs(cur->_kv.first) % newTables.size();
						// 头插
						cur->_next = newTables[i];
						newTables[i] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}

			// 3. 头插
			hashIdx = hs(kv.first) % _tables.size();
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
			return nullptr;
		}

		bool Erase(const K& key) {
			Hash hs;
			size_t hashIdx = hs(key) % _tables.size();

			Node* cur = _tables[hashIdx];
			Node* prev = nullptr;
			while (cur) {
				if (cur->_kv.first == key) {
					if (prev == nullptr) {
						_tables[hashIdx] = cur->_next;
					}
					else {
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

	void TestHashBucket1() {
		HashTable<string, string> hs;
		hs.Insert({ "sort","排序" });
		hs.Insert({ "book","书" });
	}

	void TestHashBucket2() {
		HashTable<int, int> hs;
		int arr[] = { 12,31,51,44,23,54,88,97 ,106,445};
		for (const auto& e : arr) hs.Insert({ e,e });

		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
		{
			hs.Erase(arr[i]);
		}
	}

}