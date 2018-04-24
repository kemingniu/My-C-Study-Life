//#pragma once
//
//template<class K>
//struct BinarySearchTreeNode
//{
//	BinarySearchTreeNode<K>* _left;
//	BinarySearchTreeNode<K>* _right;
//
//	K _key;
//
//	BinarySearchTreeNode(const K& key)
//		:_key(key)
//		,_left(NULL)
//		,_right(NULL)
//	{}
//};
//
//template<class K>
//class BinarySearchTree
//{
//	typedef BinarySearchTreeNode<K> Node;
//public:
//	BinarySearchTree()
//		:_root(NULL)
//	{}
//
//	BinarySearchTree(const BinarySearchTree<K>& t)
//		:_root(_Copy(t._root))
//	{}
//
//	// t1 = t2
//	//BinarySearchTree<K>& operator=(const BinarySearchTree<K>& t)
//	//{
//	//	if (this != &t)
//	//	{
//	//		_Destory(this->_root);
//	//		_root = _Copy(t._root);
//	//	}
//
//	//	return *this;
//	//}
//
//	// t1 = t2
//	BinarySearchTree<K>& operator=(BinarySearchTree<K> t)
//	{
//		swap(_root, t._root);
//		return *this;
//	}
//
//	Node* _Copy(Node* root)
//	{
//		if (root == NULL)
//		{
//			return NULL;
//		}
//		
//		Node* newRoot = new Node(root->_key);
//		newRoot->_left = _Copy(root->_left);
//		newRoot->_right = _Copy(root->_right);
//
//		return newRoot;
//	}
//
//	~BinarySearchTree()
//	{
//		_Destory(_root);
//		_root = NULL;
//	}
//
//	void _Destory(Node* root)
//	{
//		if (root == NULL)
//			return;
//
//		_Destory(root->_left);
//		_Destory(root->_right);
//		delete root;
//		//root = NULL;
//	}
//
//	bool Insert(const K& key)
//	{
//		// 1.空
//		if (_root == NULL)
//		{
//			_root = new Node(key);
//			return true;
//		}
//
//		Node* parent = NULL;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				return false;
//			}
//		}
//
//		if (parent->_key < key)
//		{
//			parent->_right = new Node(key);
//		}
//		else
//		{
//			parent->_left = new Node(key);
//		}
//
//		return true;
//	}
//
//	bool InsertR(const K& key)
//	{
//		return _InsertR(_root, key);
//	}
//
//	bool _InsertR(Node*& root, const K& key)
//	{
//		if (root == NULL)
//		{
//			root = new Node(key);
//			return true;
//		}
//		
//		if (root->_key < key)
//			return _InsertR(root->_right, key);
//		else if (root->_key > key)
//			return _InsertR(root->_left, key);
//		else
//			return false;
//	}
//
//	bool RemoveR(const K& key)
//	{
//		return _RemoveR(_root, key);
//	}
//
//	bool _RemoveR(Node*& root, const K& key)
//	{
//		if (root == NULL)
//			return false;
//		
//		if (root->_key < key)
//			return _RemoveR(root->_right, key);
//		else if(root->_key > key)
//			return _RemoveR(root->_left, key);
//		else
//		{
//			// 1.
//			// 2.
//			Node* del = root;
//			if (root->_left == NULL)
//				root = root->_right;
//			else if (root->_right == NULL)
//				root = root->_left;
//			else
//			{
//				Node* parent = root;
//				Node* subLeft = root->_right;
//				while (subLeft->_left)
//				{
//					parent = subLeft;
//					subLeft = subLeft->_left;
//				}
//
//				del = subLeft;
//				root->_key = subLeft->_key;
//				if (parent->_left == subLeft)
//					parent->_left = subLeft->_right;
//				else
//					parent->_right = subLeft->_right;
//			}
//
//			delete del;
//			return true;
//		}
//	}
//
//	const Node* Find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				return cur;
//			}
//		}
//
//		return NULL;
//	}
//
//	Node* FindR(const K& key)
//	{
//		return _FindR(_root, key);
//	}
//
//	Node*_FindR(Node* root, const K& key)
//	{
//		if(root == NULL)
//			return;
//
//		if (root->_key < key)
//			return _FindR(root->_right, key);
//		else if (root->_key > key)
//			return _FindR(root->_left, key);
//		else
//			return root;
//	}
//
//	bool Remove(const K& key)
//	{
//		Node* parent = NULL;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				// todo
//				// 1. 左为空/右为空
//				// 2. 左右都不为空
//				Node* del = cur;
//				if(cur->_left == NULL)
//				{
//					if (parent == NULL)
//					{
//						_root = cur->_right;
//					}
//					else
//					{
//						if (cur == parent->_left)
//							parent->_left = cur->_right;
//						else
//							parent->_right = cur->_right;
//					}
//				}
//				else if (cur->_right == NULL)
//				{
//					if (parent == NULL)
//					{
//						parent = cur->_left;
//					}
//					else
//					{
//						if (cur == parent->_left)
//							parent->_left = cur->_left;
//						else
//							parent->_right = cur->_left;
//					}
//				}
//				else
//				{
//					// 替换法
//					Node* parent = cur;
//					Node* subLeft = cur->_right;
//					while (subLeft->_left)
//					{
//						parent = subLeft;
//						subLeft = subLeft->_left;
//					}
//
//					// 
//					del = subLeft;
//					cur->_key = subLeft->_key;
//					if (parent->_left == subLeft)
//						parent->_left = subLeft->_right;
//					else
//						parent->_right = subLeft->_right;
//				}
//
//				delete del;
//
//				return true;
//			}
//		}
//
//		return false;
//	}
//
//	size_t Size();
//
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout<<endl;
//	}
//
//private:
//
//	void _InOrder(Node* root)
//	{
//		if(root == NULL) return;
//
//		_InOrder(root->_left);
//		cout<<root->_key<<" ";
//		_InOrder(root->_right);
//	}
//
//protected:
//	Node* _root;
//};
//
//void TestBSTree()
//{
//	int a [] = {5,3,4,1,7,8,2,6,0,9};
//	BinarySearchTree<int> t;
//	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
//	{
//		t.Insert(a[i]);
//	}
//	t.InOrder();
//
//	BinarySearchTree<int> t1(t);
//
//
//	// 测试情况
//	// 1. 左为空/右为空
//	// 2. 左右都不为空
//	t.Remove(8);
//	t.Remove(2);
//	t.Remove(1);
//	t.Remove(5);
//	t.InOrder();
//
//	// 相不到情况
//	t.Remove(0);
//	t.Remove(1);
//	t.Remove(2);
//	t.Remove(3);
//	t.Remove(4);
//	t.Remove(5);
//	t.Remove(6);
//	t.Remove(7);
//	t.Remove(9);
//	t.Remove(10);
//	t.InOrder();
//
//	t1.InOrder();
//}
//
//
//void TestBSTreeR()
//{
//	int a [] = {5,3,4,1,7,8,2,6,0,9};
//	BinarySearchTree<int> t;
//	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
//	{
//		t.InsertR(a[i]);
//	}
//	t.InOrder();
//
//	BinarySearchTree<int> t1(t);
//
//
//	// 测试情况
//	// 1. 左为空/右为空
//	// 2. 左右都不为空
//	t.RemoveR(8);
//	t.RemoveR(2);
//	t.RemoveR(1);
//	t.RemoveR(5);
//	t.InOrder();
//
//	// 相不到情况
//	t.RemoveR(0);
//	t.RemoveR(1);
//	t.RemoveR(2);
//	t.RemoveR(3);
//	t.RemoveR(4);
//	t.RemoveR(5);
//	t.RemoveR(6);
//	t.RemoveR(7);
//	t.RemoveR(9);
//	t.RemoveR(10);
//	t.InOrder();
//
//	t1.InOrder();
//}
//
//#include <string>
//
//void TestBSTTree2()
//{
//	//BinarySearchTree<string> t;
//	//t.Insert("sort");
//	//t.Insert("string");
//	//t.Insert("key");
//	//t.Insert("hash");
//
//	int strs[] = {"sort", "string", "sport",
//		"sport", "sport", "sort", "sport", "sort", "key"};
//}
//
//// 查找、排序、去重
//// 1. 判断一个单词是否合法 -- key
//// 2. 统计一个文本中单词出现的次数  -- key/value
//// 3. 实现一个字典


#pragma once

template<class K, class V>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode<K, V>* _left;
	BinarySearchTreeNode<K, V>* _right;

	const K _key;
	V _value;

	BinarySearchTreeNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		// 1.空
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

		if (parent->_key < key)
		{
			parent->_right = new Node(key, value);
		}
		else
		{
			parent->_left = new Node(key, value);
		}

		return true;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
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
				// todo
				// 1. 左为空/右为空
				// 2. 左右都不为空
				Node* del = cur;
				if(cur->_left == NULL)
				{
					if (parent == NULL)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;
					}
				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)
					{
						parent = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;
					}
				}
				else
				{
					// 替换法
					Node* parent = cur;
					Node* subLeft = cur->_right;
					while (subLeft->_left)
					{
						parent = subLeft;
						subLeft = subLeft->_left;
					}

					// 
					del = subLeft;
					cur->_key = subLeft->_key;
					if (parent->_left == subLeft)
						parent->_left = subLeft->_right;
					else
						parent->_right = subLeft->_right;
				}

				delete del;

				return true;
			}
		}

		return false;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

private:

	void _InOrder(Node* root)
	{
		if(root == NULL) return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

#include <string>

void TestBSTTree2()
{
	char* strs[] = {"sort", "string", "sport",
		"sport", "sport", "sort", "sport", "sort", "key"};

	BinarySearchTree<string, string> dict;
	dict.Insert("关键字", "key");
	dict.Insert("排序", "sort");
	dict.Insert("插入", "insert");
	dict.Insert("左边", "left");
	dict.Insert("剩余", "left");

	string s;
	//cin>>s;
	//cout<<s<<"->"<<dict.Find(s)->_value<<endl;

	BinarySearchTree<string, int> countTree;
	for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); ++i)
	{
		BinarySearchTreeNode<string, int>* ret = countTree.Find(strs[i]);
		if (ret)
		{
			ret->_value++;
		}
		else
		{
			countTree.Insert(strs[i], 1);
		}
	}
}

// 查找、排序、去重
// 1. 判断一个单词是否合法 -- key
// 2. 统计一个文本中单词出现的次数  -- key/value
// 3. 实现一个字典