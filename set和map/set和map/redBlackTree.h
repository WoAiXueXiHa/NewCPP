#pragma once
#include <iostream>

using namespace std;

namespace Vect{
	enum COLOR { RED, BLACK };

	template<class T>
	struct RBTreeNode {
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		RBTreeNode<T>* _parent;
		T _data;
		COLOR _col;

		// 构造 
		RBTreeNode(const T& data, COLOR col)
			:_left(nullptr)
			,_right(nullptr)
			,_parent(nullptr)
			,_data(data)
			,_col(col)
		{ }
	};
	
	// K给find erase用
	// V给Node insert用
	template<class Key,class T, class KeyOfT>
	class RBTree {
	public:
		typedef RBTreeNode<T> Node;
		// 构造
		RBTree() :_root(nullptr) { }

		// 查询
		bool find(const K& data) {
			if (nullptr == _root) return false;

			Node* cur = _root;
			// 二分逻辑
			while (cur) {
				if (data < cur->_data) cur = cur->_left;
				else if (data > cur->_data) cur = cur->_right;
				else return true;	// 命中 
			}
			return false;
		}

		// 插入
		bool insert(const T& data) {
			// 空树 直接插入 
			if (nullptr == _root) {
				_root = new Node(data,BLACK);
				return true;
			}

			// 非空树 先查找
			Node* cur = _root;
			Node* parent = nullptr;

			while (cur) {
				if (data < cur->_data) {
					parent = cur;
					cur = cur->_left;
				}
				else if (data > cur->_data) {
					parent = cur;
					cur = cur->_right;
				}
				else return false;		// 相同节点不插入
			}

			// 找到插入的位置 cur所在位置
			cur = new Node(data,RED);
			cur->_parent = parent;
			if (cur->_data < parent->_data) parent->_left = cur;
			else parent->_right = cur;

			// 完成插入 检查红黑树结构是否被破坏
			// 1. 父亲是黑色节点 结构未被破坏 无需调整

			// 2. 父亲是红色节点 出现连续两个红色节点 调整
			while (parent && parent->_col == RED) {
				// 父亲存在且为红色 那么爷爷节点必定存在 并且为黑色 不然之前结构就不是红黑树
				Node* grandfather = parent->_parent;
				Node* uncle = nullptr;
				if (grandfather) {
					uncle = (parent == grandfather->_left) ? grandfather->_right : grandfather->_left;
				}
				// 叔叔节点在右
				if (parent == grandfather->_left) {
					
					// 1. 叔叔节点存在且为红色 调色
					if (uncle && uncle->_col == RED) {
						grandfather->_col = RED;
						parent->_col = uncle->_col = BLACK;

						// 继续向上更新
						cur = grandfather;
						parent = grandfather->_parent;
					}
					// 2. 叔叔节点不存在或为黑色 旋转+调色
					else {
						// 2.1. LL 右旋
						if (cur == parent->_left) {
							/*
									g黑						    p黑
								  p红  u黑    左边高 右旋g     c黑   g红
							    c红									  u黑	
							
							*/
							rotateRight(grandfather);

							grandfather->_col = RED;
							cur->_col = BLACK;
							parent->_col = BLACK;
						}
						// 2.2. LR 先左旋后右旋
						else {
							/*
								g黑					 g黑						c黑
							 p红   u黑  先左旋p    c红   u黑    后右旋g     p黑  g红
								c红			   p红								 u黑
							*/
							rotateLeft(parent);
							rotateRight(grandfather);

							grandfather->_col = RED;
							cur->_col = BLACK;
							parent->_col = BLACK;
						}
						break;
					}
				}
				// 叔叔节点在左
				else {
					// 1. 叔叔节点存在且为红色 调色
					if (uncle && uncle->_col == RED) {
						grandfather->_col = RED;
						parent->_col = uncle->_col = BLACK;

						// 继续向上更新
						cur = grandfather;
						parent = grandfather->_parent;
					}
					// 2. 叔叔节点不存在或为黑色 旋转+调色
					else {
						// 2.1. RR 左旋
						if (cur == parent->_right) {
							/*
								g黑							 p黑
							 u黑   p红      右边高 左旋g   g红   c黑
									 c红					u黑	
							*/
							rotateLeft(grandfather);

							grandfather->_col = RED;
							parent->_col = BLACK;
							cur->_col = BLACK;
						}
						// 2.2. RL 先右旋后左旋
						else {
							/*
								g黑					g黑						c黑
							 u黑   p红  先右旋p   u黑   c红     后左旋g    g红   p黑
							    c红						 p红			  u黑

							*/
							rotateRight(parent);
							rotateLeft(grandfather);

							grandfather->_col = RED;
							parent->_col = BLACK;
							cur->_col = BLACK;
						}
						break;
					}
				}
			}
			_root->_col = BLACK;
			return true;
		}

		void inOrder() {
			_inOrder(_root);
			cout << endl;
		}

	private:
		Node* _root;

		void _inOrder(Node* root) {
			if (root == nullptr) return;

			_inOrder(root->_left);
			cout << root->_data << " ";
			_inOrder(root->_right);
		}

		// 右旋 
		void rotateRight(Node* node) {
			Node* nodeParent = node->_parent;
			Node* child = node->_left;
			Node* childKid = child->_right;

			/* n > c c < k
					p                         p
				  n                         c 
			    c          右旋node           n
			      k                         k 
			*/

			// 1. 下沉node 上浮child
			node->_parent = child;
			child->_right = node;
			node->_left = childKid;
			if (childKid) childKid->_parent = node;

			// 2. 处理新关系
			child->_parent = nodeParent;
			if (nullptr != nodeParent) {
				if (node == nodeParent->_left) nodeParent->_left = child;
				else nodeParent->_right = child;
			}
			else {
				_root = child;
			}
		}

		// 左旋
		void rotateLeft(Node* node) {
			Node* nodeParent = node->_parent;
			Node* child = node->_right;
			Node* childKid = child->_left;

			/* n < c c > k
				 p								p
				   n							  c
					 c     左旋node              n
                   k							   k
			*/

			// 1. 下沉node 上浮child
			node->_parent = child;
			child->_left = node;
			node->_right = childKid;
			if (childKid) childKid->_parent = node;

			// 2. 处理新关系
			child->_parent = nodeParent;
			if (nullptr != nodeParent) {
				if (node == nodeParent->_left) nodeParent->_left = child;
				else nodeParent->_right = child;
			}
			else {
				_root = child;
			}
		}
	};
}