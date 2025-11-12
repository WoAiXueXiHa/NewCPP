#pragma once
#include <iostream>

using namespace std;

namespace Vect {
	/*====================== 红黑树节点 ======================*/
	enum COLOR { RED, BLACK };
	template<class ValueType>
	struct RBTreeNode {
		RBTreeNode<ValueType>* _left;
		RBTreeNode<ValueType>* _right;
		RBTreeNode<ValueType>* _parent;

		COLOR _col;
		ValueType _data; // set是key类型 map是pair类型

		RBTreeNode(const ValueType& data, COLOR col)
			:_left(nullptr)
			,_right(nullptr)
			,_parent(nullptr)
			,_col(col)
			,_data(data)
		{ }
	};

	/*====================== 封装迭代器 ======================*/
	// ValueType:节点值类型  Ref：返回引用   Ptr：返回指针
	template<class ValueType, class Ref, class Ptr>
	struct RBTreeIterator {
		typedef RBTreeNode<ValueType> Node;
		typedef RBTreeIterator<ValueType, Ref, Ptr> Self;

		Node* _node;		// 当前节点所在指针
		Node* _root;		// 当前树的根

		RBTreeIterator(Node* node, Node* root)
			:_node(node)
			,_root(root)
		{ }

		// 中序的下一个 
		Self& operator++() {
			// 情况1：有右子树，下一个是“右子树的最左”
			if (_node->_right) {
				Node* leftMost = _node->_right;
				while (leftMost && leftMost->_left) {
					leftMost = leftMost->_left;
				}
				_node = leftMost;
			}
			// 情况2：无右子树，向上找第一个把当前节点放在“左子树”里的祖先
			else {
				Node* cur = _node;
				Node* parent = _node->_parent;
				while (parent && cur == parent->_right) {
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;		// 可能成为 nullptr（到达end）
			}
			return *this;
		}

		// 中序的上一个 和++相反 右 根 左
		Self& operator--() {
			// 特例：从 end()（即 _node==nullptr）回退到“整棵树的最右节点”
			if (_node == nullptr) {
				Node* rightMost = _root;
				while(rightMost && rightMost->_right) {
					rightMost = rightMost->_right;
				}
				_node = rightMost;
			}
			// 有左子树：前驱是“左子树的最右”
			else if (_node->_left) {
				Node* rightMost = _node->_left;
				while (rightMost && rightMost->_right) {
					rightMost = rightMost->_right;
				}
				_node = rightMost;
			}
			// 无左子树：向上找第一个把当前节点放在“右子树”里的祖先
			else {
				Node* cur = _node;
				Node* parent = cur->_parent;
				while (parent && cur == parent->_right) {
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return *this;
		}

		bool operator==(const Self& other) const { return _node == other._node; }
		bool operator!=(const Self& other) const { return _node != other._node; }

		Ptr operator->() { return &_node->_data; }
		Ref operator*() { return _node->_data; }
	};


	/*====================== 红黑树 ======================*/
	// Key:用于比较/查找的“键”类型
	// ValueType:节点里实际存储的数据类型
	// KeyOfV:从ValueType提取Key的函数对象（map/set可复用同一棵RBTree）
	template<class Key, class ValueType, class KeyOfV>
	class RBTree {
	public:
		typedef RBTreeNode<ValueType> Node;
		typedef RBTreeIterator<ValueType, ValueType&, ValueType*> Iterator;
		typedef RBTreeIterator<ValueType, const ValueType&, const ValueType*> ConstIterator;

		RBTree() = default;
		RBTree(const RBTree& other) { _root = Copy(other._root); }
		RBTree& operator=(RBTree other) { swap(_root, other._root); return *this; }
		~RBTree() { Destory(_root); }

		void InOrder() { _inOrder(_root); }

		// 中序第一个 最左子节点
		Iterator Begin(){
			Node* leftMost = _root;
			while (leftMost && leftMost->_left) {
				leftMost = leftMost->_left;
			}
			return Iterator(leftMost, _root);
		}
		// 中序最后一个的下一个 最右子节点的下一个 nullptr
		Iterator End() { return Iterator(nullptr, _root); }
		
		ConstIterator Begin() const {
			Node* leftMost = _root;
			while (leftMost && leftMost->_left) {
				leftMost = leftMost->_left;
			}
			return ConstIterator(leftMost, _root);
		}
		ConstIterator End() const { return ConstIterator(nullptr, _root); }

		// 按Key定位，返回迭代器，找不到返回End()
		Iterator Find(const Key& key) {
			Node* cur = _root;
			KeyOfV kov;
			while (cur) {
				if (key < kov(cur->_data)) cur = cur->_left;
				else if (key > kov(cur->_data)) cur = cur->_right;
				else return Iterator(cur, _root);
			}

			return End();
		}

		// 插入成功 返回新插入节点迭代器      插入失败 返回上一个节点迭代器
		pair<Iterator, bool> Insert(const ValueType& data) {
			if (_root == nullptr) {
				_root = new Node(data, BLACK);
				return make_pair(Iterator(_root, _root),true);
			}

			// 1. 找插入位置
			Node* cur = _root;
			Node* parent = nullptr;
			KeyOfV kov;
			while (cur) {
				if (kov(data) < kov(cur->_data)) {
					parent = cur;
					cur = cur->_left;
				}
				else if (kov(data) > kov(cur->_data)) {
					parent = cur;
					cur = cur->_right;
				}
				else return make_pair(Iterator(cur, _root),false);
			}

			// 2. 插入操作
			cur = new Node(data, RED);
			Node* newNode = cur;	// 提前保存一份 防止旋转之后迭代器失效

			cur->_parent = parent;
			if (kov(parent->_data) > kov(cur->_data))
				parent->_left = cur;
			else
				parent->_right = cur;

			// 3. 检查红黑树结构是否被破坏
			// 1> 父节点是黑色 结构未被破坏 不用调整

			// 2> 父节点为红色 连续两个红节点 结构被破坏
			while (parent && parent->_col == RED) {
				// 父节点为红色 就一定不是根 父节点的父亲一定存在且为黑
				Node* grandfather = parent->_parent;
				Node* uncle = (parent == grandfather->_left) ? grandfather->_right : grandfather->_left;

				// uncle在左
				if (grandfather->_right == parent) {
					// case1: uncle存在且为红
					if (uncle && uncle->_col == RED) {
						// 父叔变黑 爷变红并向上更新
						parent->_col = uncle->_col = BLACK;
						grandfather->_col = RED;

						cur = grandfather;
						parent = grandfather->_parent;
					}
					// case2: uncle不存在或为黑
					else {
						// 1) cur在parent的右 RR 左旋爷
						if (cur == parent->_right) {
							rotateLeft(grandfather);

							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						// 2) cur在parent的左 RL 先右旋父 再左旋爷
						else {
							rotateRight(parent);
							rotateLeft(grandfather);

							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						break;	// 一次旋转加变色就可以调整完成
					}
				}
				// unlce在右
				else {
					// case1: uncle存在且为红
					if (uncle && uncle->_col == RED) {
						// 父叔变黑 爷变红并向上更新
						parent->_col = uncle->_col = BLACK;
						grandfather->_col = RED;

						cur = grandfather;
						parent = grandfather->_parent;
					}
					// case2: uncle不存在或为黑
					else {
						// 1）cur在parent的左 LL 右旋爷
						if (cur == parent->_left) {
							rotateRight(grandfather);

							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						// 2）cur在parent的右 LR 先左旋父 后右旋爷
						else {
							rotateLeft(parent);
							rotateRight(grandfather);

							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						break;	// 一次旋转加变色就可以调整完成
					}
				}
			}
			_root->_col = BLACK;
			return make_pair(Iterator(newNode, _root),true);
		}
	private:
		Node* _root;

		// 左旋
		void rotateLeft(Node* node) {
			Node* child = node->_right;
			Node* childKid = child->_left;
			Node* nodeParent = node->_parent;

			// 1. 下沉node 上浮child
			node->_parent = child;
			child->_left = node;
			node->_right = childKid;
			if (childKid) childKid->_parent = node;

			// 2. 梳理新的爷父孙关系
			child->_parent = nodeParent;
			if (nodeParent != nullptr) {
				if (node == nodeParent->_left) nodeParent->_left = child;
				else nodeParent->_right = child;
			}
			else {
				_root = child;
			}
		}
		
		// 右旋
		void rotateRight(Node* node) {
			Node* child = node->_left;
			Node* childKid = child->_right;
			Node* nodeParent = node->_parent;

			node->_parent = child;
			child->_right = node;
			node->_left = childKid;
			if (childKid) childKid->_parent = node;

			child->_parent = nodeParent;
			if (nodeParent != nullptr) {
				if (node == nodeParent->_left) nodeParent->_left = child;
				else nodeParent->_right = child;
			}
			else {
				_root = child;
			}
		}

		// 中序遍历
		void _inOrder(Node* root) {
			if (root == nullptr) return;

			_inOrder(root->_left);
			cout << root->_data << " ";
			_inOrder(root->_right);
			cout << endl;
		}

		void Destory(Node* root) {
			if (root == nullptr) return;
			Destory(root->_left);
			Destory(root->_right);
			delete root;
		}

		Node* Copy(Node* root) {
			if (root == nullptr) return nullptr;
			
			Node* newRoot = new Node(root->_data, root->_col);
			newRoot->_left = Copy(root->_left);
			if (newRoot->_left)  newRoot->_left->_parent = newRoot;
			newRoot->_right = Copy(root->_right);
			if (newRoot->_right) newRoot->_right->_parent = newRoot;
		}
	};
}