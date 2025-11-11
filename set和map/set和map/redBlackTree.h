#pragma once
#include <iostream>

using namespace std;

namespace Vect{
	enum COLOR { RED, BLACK };

	template<class ValueType>
	struct RBTreeNode {
		RBTreeNode<ValueType>* _left;
		RBTreeNode<ValueType>* _right;
		RBTreeNode<ValueType>* _parent;
		ValueType _data;
		COLOR _col;

		// 构造 
		RBTreeNode(const ValueType& data,COLOR col)
			:_left(nullptr)
			,_right(nullptr)
			,_parent(nullptr)
			,_data(data)
			,_col(col)
		{ }
	};

	template<class ValueType,class Ref, class Ptr>
	struct RBTIterator {
		typedef RBTreeNode<ValueType> Node;
		typedef RBTIterator<ValueType, Ref, Ptr> Self;

		Node* _node;
		Node* _root;

		RBTIterator(Node* node,Node* root):_node(node),_root(root) { }

		Self& operator++() {
			// 只关注局部子树就好 
			if (_node->_right) {
				// 右子树不为空
				/*   13    <---- it  下一个是15 此时右子树不为空 说明左子树已经走完了 则寻找右子树最左节点
						17
				     15    25
				
				*/
				Node* leftMost = _node->_right;
				while (leftMost->_left) { leftMost = leftMost->_left; }

				_node = leftMost;
			}
			else {
				// 右子树为空 两种情况： 是左孩子 是右孩子
				/*
					   13			it在15且右为空 说明当前子树访问完了
						 17			需要沿着到根节点地路径查找 找父亲是左孩子的祖先节点
			   it---->15    25		找到17
				
					   13			
					9				需要沿着到根节点地路径查找 找父亲是左孩子的祖先节点
				 1    11<---it		9已经走完了 找到13 找祖先
									
									所以： 在左 找父亲    在右 找父亲是左孩子的祖先节点
				*/
				Node* cur = _node;
				Node* parent = _node->_parent;

				while (parent && cur == parent->_right) {
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}

		// 和++反着来 右 根 左
		Self& operator--() {
			// 迭代器从end()开始 需要特殊处理 end()是最后节点的下一个位置
			// 走到中序最后一个节点 整棵树的最右节点
			if (_node == nullptr) {
				Node* rightMost = _root;
				while (rightMost && rightMost->_right) {
					rightMost = rightMost->_right;
				}
				_node = rightMost;
			}
			else if (_node->_left) {
				// 左子树不为空 是中序左子树的最后一个
				/*   13    
						17	<---- it  下一个是15 此时左子树不为空 说明右子树已经走完了 找左子树的最右节点
						15    25
				*/
				Node* rightMost = _node->_left;
				while (rightMost) {
					rightMost = rightMost->_right;
				}
				_node = rightMost;
			}
			else {
				// 左子树为空 两种情况： 是左孩子 是右孩子
				// 在右 找父亲    在左 找父亲是左孩子的祖先节点
				/*
						13		下一个是13 	
							17			
				it---->15    25		

						13
					9			下一个是9	
					1    11<---it		
				*/
				Node* cur = _node;
				Node* parent = _node->_parent;
				while (parent && cur == parent->_left) {
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}

		Ref operator*() { return _node->_data; }
		Ptr operator->() { return &_node->_data; }

		bool operator!=(const Self s) { return _node != s._node; }

		bool operator==(const Self s) { return _node == s._node; }

	};
	
	// Key给find erase用
	// ValueType给Node insert用
	template<class Key,class ValueType, class KeyOfV>
	class RBTree {
	public:
		typedef RBTreeNode<ValueType> Node;
		typedef RBTIterator<ValueType, ValueType&, ValueType*> Iterator;
		typedef RBTIterator<ValueType, const ValueType&, const ValueType*> ConstIterator;
		
		// 构造
		RBTree() :_root(nullptr) { }

		// 拷贝构造
		RBTree(const RBTree& other) { _root = Copy(other._root); }

		// 赋值重载
		RBTree& operator=(const RBTree& other) { swap(_root, other._root); return *this; }

		// 迭代器
		// 中序 最左子节点
		Iterator Begin(){
			Node* leftMost = _root;
			while (leftMost && leftMost->_left) {
				leftMost = leftMost->_left;
			}
			return Iterator(leftMost);
		}
		ConstIterator Begin() const {
			Node* leftMost = _root;
			while (leftMost && leftMost->_left) {
				leftMost = leftMost->_left;
			}
			return ConstIterator(leftMost);
		}

		// 最后一个节点的下一个
		Iterator End() { return Iterator(nullptr); }
		ConstIterator End() const { return ConstIterator(nullptr); }

		// 插入
		// 插入成功 返回插入节点迭代器			插入失败 返回已有节点迭代器
		pair<Iterator,bool> Insert(const ValueType& data) {
			// 空树 直接插入 
			if (nullptr == _root) {
				_root = new Node(data,BLACK);
				return make_pair(Iterator(_root,_root),true);
			}

			// 非空树 先查找
			KeyOfV kov;
			Node* cur = _root;
			Node* parent = nullptr;

			while (cur) {
				if (kov(data) < kov(cur->_data)) {
					parent = cur;
					cur = cur->_left;
				}
				else if (kov(data) > kov(cur->_data)) {
					parent = cur;
					cur = cur->_right;
				}
				else return make_pair(Iterator(cur,_root),false);		// 相同节点不插入
			}

			// 找到插入的位置 cur所在位置
			cur = new Node(data,RED);
			Node* newNode = cur;		// 插入成果要返回迭代器 防止调整的时候迭代器失效 提前保存一份
			cur->_parent = parent;
			if (kov(cur->_data) < kov(parent->_data)) parent->_left = cur;
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
			return make_pair(Iterator(newNode, _root), true);
		}

		void inOrder() {
			_inOrder(_root);
			cout << endl;
		}

		// 查找 按Key查找
		Iterator Find(const Key& key) {
			Node* cur = _root;
			while (cur)
			{
				if (cur->_kv.first < key)
				{
					cur = cur->_right;
				}
				else if (cur->_kv.first > key)
				{
					cur = cur->_left;
				}
				else
				{
					return Iterator(cur, _root);
				}
			}

			return End();
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

		void Destroy(Node* root)
		{
			if (root == nullptr)
				return;

			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}

		Node* Copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;

			Node* newRoot = new Node(root->_kv);
			newRoot->_left = Copy(root->_left);
			newRoot->_right = Copy(root->_right);

			return newRoot;
		}
	};
}