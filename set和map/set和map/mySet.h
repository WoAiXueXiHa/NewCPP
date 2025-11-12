#pragma once
#include "RBTree.h"

namespace Vect {
	template<class Key, class ValueType>
	class set {
	public:
		struct SetKeyOfV {
			const Key& operator()(const Key& key) const {
				return key;
			}
		};

		typedef typename RBTree<Key, const Key, SetKeyOfV>::Iterator iterator;
		typedef typename RBTree<Key, const Key, SetKeyOfV>::ConstIterator const_iterator;

		iterator begin() { return _tree.Begin(); }
		const_iterator begin() const { return _tree.Begin(); }
		iterator end() { return _tree.End(); }
		const_iterator end() const { return _tree.End(); }

		pair<iterator, bool> insert(const Key& key) { return _tree.Insert(key);}
		iterator find(const Key& key) { return _tree.Find(); }

	private:
		RBTree<Key, const Key, SetKeyOfV> _tree;
	};

	void test_set() {
		set<int,int> s;
		s.insert(1);
		s.insert(0);
		s.insert(10);
		s.insert(20);
		s.insert(7);
		s.insert(65);

		set<int, int>::iterator it = s.begin();
		while (it != s.end()) {
			cout << *it << " ";
			++it;
		}

	}
}