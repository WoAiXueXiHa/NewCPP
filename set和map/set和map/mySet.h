#pragma once
#include "redBlackTree.h"

namespace Vect {
	template<class Key>

	class set {
		struct SetKeyOfV {
			const Key& operator(const Key& key) {
				return key;
			}
		};

	public:
		typedef typename RBTree<Key, const Key, SetKeyOfV>::Iterator iterator;
		typedef typename RBTree<Key, const Key, SetKeyOfV>::ConstIterator const_iterator;
		iterator begin() { return _tree.Begin(); }
		iterator end() { return _tree.End(); }
		const_iterator begin() const { return _tree.Begin(); }
		const_iterator end() const { return _tree.End(); }
		pair<iterator, bool> insert(const Key& key) { return _tree.Insert(key); }
		iterator find(const Key& key) { return _tree.Find(key); }
	private:
		RBTree<Key, Key, SetKeyOfV> _tree;

	};
}
