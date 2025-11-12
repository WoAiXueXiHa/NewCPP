#pragma once
#include "RBTree.h"



namespace Vect {
	template<class Key, class ValueType>
	class map {
		struct MapKeyOfV {
			const Key& operator()(const pair<Key, ValueType>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<Key, pair<const Key, ValueType>, MapKeyOfV>::Iterator iterator;
		typedef typename RBTree<Key, pair<const Key, ValueType>, MapKeyOfV>::ConstIterator const_iterator;

		iterator begin() { return _tree.Begin(); }
		iterator end() { return _tree.End(); }
		const_iterator begin() const { return _tree.Begin(); }
		const_iterator end() const { return _tree.End(); }
		pair<iterator, bool> insert(const pair<Key, ValueType>& kv) { return _tree.Insert(kv); }
		iterator find(const Key& key) { return _tree.Find(key); }
		ValueType& operator[](const Key& key) {
			pair<iterator, bool> ret = insert(make_pair < key, ValueType());
			return ret.first->second;
		}
	private:
		RBTree<Key, pair<const Key, ValueType>, MapKeyOfV> _tree;
	};
}