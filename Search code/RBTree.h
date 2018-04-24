#pragma once

enum Colour
{
	RED,
	BLACK,
};

template<class ValueType>
struct RBTreeNode
{
	RBTreeNode<ValueType>* _left;
	RBTreeNode<ValueType>* _right;
	RBTreeNode<ValueType>* _parent;
	Colour _col;

	//K _key;
	//V _value;
	ValueType _valueField;

	RBTreeNode(const ValueType& valueField)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_valueField(valueField)
		,_col(RED)
	{}
};

template<class T>
struct __RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T> Self;
		 
	Node* _node;

	__RBTreeIterator(Node* node)
		:_node(node)
	{}
	
	T& operator*()
	{
		return _node->_valueField;
	}

	T* operator->()
	{
		return &(operator*());
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	Self& operator++()
	{
		if (_node->_right)
		{
			Node* subLeft = _node->_right;
			while (subLeft->_left)
				subLeft = subLeft->_left;

			_node = subLeft;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;

			while (parent && parent->_right == cur)
			{
				cur = parent;
				parent = cur->_parent;
			}

			_node = parent;
		}

		return *this;
	}

	Self& operator--()
	{
		if (_node->_left)
		{
			Node* subRight = _node->_left;
			while (subRight->_right)
			{
				subRight = subRight->_right;
			}

			_node = subRight;
		}
		else
		{
			Node* cur =_node;
			Node* parent = _node->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}

			_node = parent;
		}

		return *this;
	}
};

template<class K, class T, class KeyOfValue>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef __RBTreeIterator<T> Iterator;

	RBTree()
		:_root(NULL)
	{}

	Iterator Begin()
	{
		Node* leftLeft = _root;
		while (leftLeft && leftLeft->_left)
		{
			leftLeft = leftLeft->_left;
		}

		return Iterator(leftLeft);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

	Iterator RBegin()
	{
		Node* subRight = _root;
		while (subRight->_right)
		{
			subRight = subRight->_right;
		}

		return subRight;
	}

	Iterator REnd()
	{
		return Iterator(NULL);
	}

	Iterator Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			KeyOfValue keyOfValue;
			if (keyOfValue(cur->_valueField) > key)
			{
				cur = cur->_left;
			}
			else if (keyOfValue(cur->_valueField) < key)
			{
				cur = cur->_right;
			}
			else
			{
				return Iterator(cur);
			}
		}

		return End();
	}

	pair<Iterator, bool> Insert(const T& kv)
	{
		if (_root == NULL)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return make_pair(Iterator(_root), true);
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (KeyOfValue()(cur->_valueField) < KeyOfValue()(kv))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (KeyOfValue()(cur->_valueField) > KeyOfValue()(kv))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(Iterator(cur), false);
			}
		}

		cur = new Node(kv);
		Node* newNode = cur;
		if (KeyOfValue()(parent->_valueField) < KeyOfValue()(kv))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 调平衡
		while(parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else // uncle不存在/存在且黑
				{
					// 双旋
					if(parent->_right == cur)
					{
						RotateL(parent);

						// fix bug--更正parent和cur的相对位置
						swap(parent, cur);
					}

					RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;

					break;
				}
			}
			else // parent == grandfather->_right
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						
						// fix bug--更正parent和cur的相对位置
						swap(parent, cur);
					}

					RotateL(grandfather);

					parent->_col = BLACK;
					grandfather->_col = RED;

					break;
				}
			}
		}

		_root->_col = BLACK;
		return make_pair(Iterator(newNode), true);
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parentParent == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subL;
			else
				parentParent->_right = subL;

			subL->_parent = parentParent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		Node* parentParent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parentParent == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subR;
			else
				parentParent->_right = subR;

			subR->_parent = parentParent;
		}
	}

	bool IsBalance()
	{
		if (_root && _root->_col == RED)
		{
			return false;
		}

		int k = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				++k;
			cur = cur->_left;
		}

		size_t blackNum = 0;
		return _IsBalance(_root, blackNum, k);
	}

	bool _IsBalance(Node* root, size_t blackNum, const size_t k)
	{
		if(root == NULL)
		{
			if (blackNum == k)
				return true;
			else
			{
				cout<<"黑色节点的数量不相等:"<<endl;
				return false;
			}
		}

		if (root->_col == BLACK)
			++blackNum;

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout<<"存在连续的红节点:"<<endl;
			return false;
		}

		return _IsBalance(root->_left, blackNum, k)
			&&_IsBalance(root->_right, blackNum, k);
	}

private:
	Node* _root;
};

void TestRBTree()
{
	//int a1[] = {5,3,4,1,7,8,2,6,0,9};
	/*RBTree<int, int> t1;
	RBTree<int, pair<int, int>> t2;
	t1.Insert(3);
	t1.Insert(2);
	t1.Insert(1);
	t1.Insert(4);

	RBTree<int, int>::Iterator it = t1.Begin();
	while (it != t1.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	RBTree<int, int>::Iterator rit = t1.RBegin();
	while (rit != t1.REnd())
	{
		cout<<*rit<<" ";
		--rit;
	}
	cout<<endl;*/
}