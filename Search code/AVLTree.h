#pragma once

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	
	K _key;
	V _value;

	int _bf; // 平衡因子

	AVLTreeNode(const K& key, const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// todo
		// 更新平衡因子
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0) // 高度不变
			{
				break;
			}
			else if (parent->_bf == 1 
				|| parent->_bf == -1) // 高度变了
			{
				cur = parent;
				parent = cur->_parent;
			}
			else if (parent->_bf == 2
				|| parent->_bf == -2)
			{
				// 旋转
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else
					{
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else
					{
						RotateLR(parent);
					}
				}

				break;
			}
			else
			{
				assert(false);
			}
		}

		return true;
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

		subL->_bf = parent->_bf = 0;
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

		subR->_bf =	parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else if (bf == 0)
		{
			subLR->_bf = subL->_bf = parent->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if(bf == 0)
		{
			subR->_bf = subRL->_bf = parent->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);

		cout<<root->_key<<":"<<root->_value<<"  ";
		_InOrder(root->_right);
	}

	bool IsBalance()
	{
		//return _IsBalance(_root);
		int height = 0;
		return _IsBalance(_root, height);
	}

	int _Height(Node* root)
	{
		if (root == NULL)
			return 0;

		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left+1:right+1;
	}

	bool _IsBalance(Node* root)
	{
		if(root == NULL)
			return true;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right); 

		return abs(rightHeight-leftHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}


	bool _IsBalance(Node* root, int& height)
	{
		if(root == NULL)
		{
			height = 0;
			return true;
		}

		int leftHeight = 0;
		if(_IsBalance(root->_left, leftHeight) == false)
			return false;

		int rightHeight = 0;
		if(_IsBalance(root->_right, rightHeight) == false)
			return false;
		
		if (root->_bf != (rightHeight-leftHeight))
		{
			cout<<"平衡因子异常"<<root->_key<<endl;
			return false;
		}

		height = leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;

		return abs(leftHeight-rightHeight) < 2;
	}

private:
	Node* _root;
};

void TestAVLTree()
{
	int a1[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int, int> t1;
	for (size_t i = 0; i < sizeof(a1)/sizeof(int); ++i)
	{
		t1.Insert(a1[i], i);
		cout<<"IsBalance?"<<t1.IsBalance()<<"->Insert:"<<a1[i]<<endl;
	}

	t1.InOrder();
}