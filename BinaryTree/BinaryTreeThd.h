#pragma once

enum PointerTag {THREAD, LINK};

template <class T>
struct BinaryTreeNodeThd
{
	T _data ;                         // 数据
	BinaryTreeNodeThd<T >* _left;   // 左孩子
	BinaryTreeNodeThd<T >* _right;  // 右孩子
	PointerTag   _leftTag ;          // 左孩子线索标志
	PointerTag   _rightTag ;         // 右孩子线索标志

	BinaryTreeNodeThd(const T& x)
		:_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
		,_data(x)
	{}
};

// 基类迭代器
template<class T>
struct __BinaryTreeIterator
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef __BinaryTreeIterator<T> Self;
	Node* _node;

	__BinaryTreeIterator(Node* node)
		:_node(node)
	{}
	
	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		return &(_node->_data);
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	virtual Self& operator++() = 0; // 纯虚函数
};


template<class T>
struct __BinaryTreeInIterator : public __BinaryTreeIterator<T>
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef __BinaryTreeInIterator<T> Self;

	__BinaryTreeInIterator(Node* node)
		:__BinaryTreeIterator(node)
	{}

	Self& operator++()
	{
		if (_node->_rightTag == THREAD)
		{
			_node = _node->_right;
		}
		else
		{
			Node* sub = _node->_right;
			while (sub && sub->_leftTag == LINK)
			{
				sub = sub->_left;
			}

			_node = sub;
		}

		return *this;
	}
};

template<class T>
struct __BinaryTreePrevIterator : public __BinaryTreeIterator<T>
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef __BinaryTreePrevIterator<T> Self;

	__BinaryTreePrevIterator(Node* node)
		:__BinaryTreeIterator(node)
	{}

	Self& operator++()
	{
		if (_node->_leftTag == LINK)
		{
			_node = _node->_left;
		}
		else // left THREAD
		{
			_node = _node->_right;
		}

		return *this;
	}
};


template <class T>
struct BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef __BinaryTreeInIterator<T> InIterator;
	typedef __BinaryTreePrevIterator<T> PrevIterator;

public:
	typedef __BinaryTreeIterator<T> Iterator;

	BinaryTreeThd(T* a, size_t n, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(a, n, index, invalid);
	}


	PrevIterator PrevBegin()
	{
		return _root;
	}

	PrevIterator PrevEnd()
	{
		return NULL;
	}

	InIterator InBegin()
	{
		Node* sub = _root;
		while (sub && sub->_leftTag == LINK)
		{
			sub = sub->_left;
		}

		return sub;
	}

	InIterator InEnd()
	{
		return NULL;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	// 线索化
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}

	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		_InOrderThreading(cur->_left, prev);

		//线索化
		if(cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;

		_InOrderThreading(cur->_right, prev);
	}

	void PrevThreading()
	{
		Node* prev = NULL;
		_PrevThreading(_root, prev);
	}

	void _PrevThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		
		prev = cur;

		if (cur->_leftTag == LINK)
			_PrevThreading(cur->_left, prev);

		if(cur->_rightTag == LINK)
			_PrevThreading(cur->_right, prev);
	}

protected:
	Node* _CreateTree(T* a, size_t n, size_t& index, const T& invalid)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, n, ++index, invalid);
			root->_right = _CreateTree(a, n, ++index, invalid);
		}

		return root;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

//void TestBinaryTreeThd()
//{
//	int a1[] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
//	BinaryTreeThd<int> t1(a1, sizeof(a1)/sizeof(a1[0]), '#');
//	t1.InOrder();
//	t1.InOrderThreading();
//
//	BinaryTreeThd<int>::InIterator it1 = t1.InBegin();
//	while(it1 != t1.InEnd())
//	{
//		cout<<*it1<<" ";
//		++it1;
//	}
//	cout<<endl;
//
//	BinaryTreeThd<int> t2(a1, sizeof(a1)/sizeof(a1[0]), '#');
//	t2.PrevThreading();
//
//	BinaryTreeThd<int>::PrevIterator it2 = t2.PrevBegin();
//	while(it2 != t2.PrevEnd())
//	{
//		cout<<*it2<<" ";
//		++it2;
//	}
//	cout<<endl;
//}


void TestBinaryTreeThd()
{
	int a1[] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	BinaryTreeThd<int> t1(a1, sizeof(a1)/sizeof(a1[0]), '#');
	t1.InOrder();
	t1.InOrderThreading();

	BinaryTreeThd<int>::Iterator& it1 = t1.InBegin();
	while(it1 != t1.InEnd())
	{
		cout<<*it1<<" ";
		++it1; // 多态
	}
	cout<<endl;

	BinaryTreeThd<int> t2(a1, sizeof(a1)/sizeof(a1[0]), '#');
	t2.PrevThreading();

	BinaryTreeThd<int>::Iterator& it2 = t2.PrevBegin();
	while(it2 != t2.PrevEnd())
	{
		cout<<*it2<<" ";
		++it2;
	}
	cout<<endl;
}

//Node* ToSortList(Node* root)
//{
//	Node* prev = NULL;
//	_ToSortList(root, prev);
//
//	Node* head = root;
//	while (head && head->_left)
//	{
//		head = head->_left;
//	}
//
//	return head;
//}
//
//void _ToSortList(Node* cur, Node*& prev)
//{
//	if(cur == NULL)
//		return;
//
//	_ToSortList(cur->_left, prev);
//
//	cur->_left = prev;
//	if(prev)
//		prev->_right = cur;
//
//	_ToSortList(cur->_right, prev);
//}
