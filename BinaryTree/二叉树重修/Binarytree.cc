#include<iostream>
#include<stack>
#include<queue>
#include<assert.h>
using namespace std;


template<typename T>
 struct TreeNode
{
	T _data;
	TreeNode<T>* _left;     
	TreeNode<T>* _right;
    
	TreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<typename T>
class BinaryTree{
private:
	typedef TreeNode<T> Node;
	Node* _root;
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(T* a,size_t n,const T& invalid)
	{
		assert(a);
		size_t index = 0;
		_root = CreateTree(a,n,index,invalid);
	}
	Node* CreateTree(T* array,size_t len,size_t &index,const T& invalid)
	{
		Node* root = NULL;  //前序遍历构造二叉树
		if(index < len && array[index] != invalid)
		{
			root  = new Node(array[index]);
			root->_left = CreateTree(array,len,++index,invalid);
			root->_right = CreateTree(array,len,++index,invalid);
		}
		return root;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}

	void _PrevOrder(Node* root)
	{
		if(root == NULL)
			return;
		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}


	void PrevOrderR()//非递归前序遍历二叉树
	{
		stack<Node*> s;   //划归为一个一个子问题，先求左路节点，再求左路节点的右子树。
		Node* cur = _root;
		while(cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cout<<s.top()->_data<<" ";
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}


	void InOrderR()
	{
		//先左子树，在根节点，在右子树，
		stack<Node*> s;
		Node* cur = _root;

		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout<<top->_data<<" ";
			cur = top->_right;
		}
		cout<<endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void _PostOrder(Node* root)
	{
		if(root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}

	void PostOrderR()
	{//后序遍历：先左子树，在右子树，后父节点。
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;//纪录当前访问的上一个节点

		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			if(top->_right == NULL || top->_right == prev)
			{
				cout<<top->_data<<" ";
				s.pop();
				prev = top;
				
			}
			else
			{
				cur = top->_right;
			}
		}
		cout<<endl;
	}
	size_t Size()
	{
		size_t n = 0;
		 _Size(_root,n);
		 return n;
	}
	size_t _Size(Node* root)
	{
		if(root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	void _Size(Node* root,size_t& n)
	{
		if(root == NULL)
			return;
		n++;

		 _Size(root->_left,n);
		 _Size(root->_right,n);

	}

	size_t LeafSize()
	{
		size_t  count = 0;
		//_LeadfSize(_root,count);
		//return count;
		return _LeadfSize(_root);

	}
	void _LeadfSize(Node* root,size_t& count) //低配版 
	{                                         //递归的条件，有结束的条件，越来越接近限制条件。
		if(root == NULL)
			return;
		if(root->_left == NULL && root->_right == NULL)
			count++;
		_LeadfSize(root->_left,count);
		_LeadfSize(root->_right,count);
	}

	size_t _LeadfSize(Node* root)
	{
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
			return 1;
		return _LeadfSize(root->_left) + _LeadfSize(root->_right);

	}

	size_t Hight()
	{
		return _Hight(_root);
	}
	size_t _Hight(Node* root)
	{
		if(root == NULL)
			return 0;
		size_t left = _Hight(root->_left);
		size_t right = _Hight(root->_right);

		return left > right ? left+1 : right+1;
	}

	size_t GetLevelK(int k)
	{
		
		return _GetLevelK(_root,k);
	}
	size_t _GetLevelK(Node* root,int k)
	{
		if(root == NULL)
			return 0;
		if(k==1)
			return 1;
		return _GetLevelK(root->_left,k-1) + _GetLevelK(root->_right,k-1);
	}

	void LevelOrder()
	{
		queue<Node*> q;
		if(_root != NULL)
		{
			q.push(_root);
		}
		while(!q.empty())
		{
			Node* front = q.front();
			cout<<front->_data<<" ";
			q.pop();

			if(front->_left)
			{
				q.push(front->_left);
			}
			if(front->_right)
			{
				q.push(front->_right);
			}
		}
		cout<<endl;
	}

	//void LevelOrderR()
	//{
	//	vector<vector<int> > res;
	//	level(res,_root,1);
	//	for(vector<vector<int>>::iterator it = res.begin();it != res.end();++it)
	//		for(vector<int>::iterator it2 = it->begin()/*(*it).begin()*/;it2 != it->end();++it2)
	//			cout<<*it2<<" ";

	//	/*
	//	if the compiler support the C++11;you can do this:
	//	vector<vector<int>> a;
	//	for(auto &u1 : a)
	//		for(auto &u2 : u1)
	//		cout<<u2<<endl;
	//	*/
	//}
	//void level(vector<vector<int>>&res,Node* root,int num)
	//{
	//	if(root == NULL)
	//		return ;
	//	if(num > res.size())
	//		res.push_back(vector<int>());
	//	
	//	res[num-1].push_back(root->_data);
	//	level(res,root->_left,num+1);
	//	level(res,root->_right,num+1);


	//}

	void LevelOrderR()
	{
		for(size_t  i = 1;i <= Hight();i++)
		_LevelOrderR(_root,i);
	}
	void _LevelOrderR(Node* root,size_t level)
	{
		if(root == NULL || level < 1)
			return;
		if(level == 1)
		{
			cout<<root->_data<<" ";
			return;
		}

		_LevelOrderR(root->_left,level-1);
		_LevelOrderR(root->_right,level-1);
	}
	bool IsCompleteTree() //完全二叉树
	{
		queue<Node*> q;
		if(_root)
			q.push(_root);
		bool flag = true;

		while(!q.empty())
		{
			Node* front = q.front();
			q.pop();

			if(front->_left)
			{
				q.push(front->_left);
				if(flag == false)
					return false;
			}
			else
			{
				flag = false;
			}

			if(front->_right)
			{
				q.push(front->_right);
				if(flag == false)    
				{   
					return false;
				}    
				else
				{
					flag = false;
				}
			}
		}
		return true;
	}

	bool FullTree() //满二叉树
	{
		//根据定律，满二叉树的节点是二的k方减一。（k为深度）
		size_t deep = Hight();
		size_t size = Size();

		if(pow(2,deep)-1 == size)
			return true;
		else
			return false;
	}

	Node* Find(const T& x)
	{
		return _Find(_root,x);
	}
	Node* _Find(Node* root,const T& x)
	{
		if(root == NULL)
			return NULL;
		if(root->_data == x)
			return root;
		Node* ret = _Find(root->_left,x);
		if(ret )
		return ret;
		return _Find(root->_right,x);
	}
	void MirrorTree()
	{
		_MirrorTree();
	}
    void _MirrorTree(Node* root)
	{
		if(root == NULL)
			return ;

		swap(root->_left,root->_right);
		_MirrorTree(root->_left);
		_MirrorTree(root->_right);
	}

	
	
};

/*int main()
{
	//int a1[] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int a1[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree<int> t1(a1,sizeof(a1)/sizeof(a1[0]),'#');
	t1.PrevOrder();
	t1.PrevOrderR();
	t1.InOrder();
	t1.InOrderR();
	t1.PostOrder();
	t1.PostOrderR();
	cout<<t1.Size()<<endl;
	cout<<t1.LeafSize()<<endl;
	cout<<t1.Hight()<<endl;
	cout<<t1.GetLevelK(3)<<endl;
	t1.LevelOrder();
	cout<<t1.IsCompleteTree()<<endl;
	t1.LevelOrderR();
	t1.Find(8);

}*/