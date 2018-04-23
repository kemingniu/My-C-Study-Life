//#include<iostream>
//#include<vector>
//#include<assert.h>
//using namespace std;
//
//
//
//
//template<typename T>
//class Heap
//{
//private:
//	vector<T> _a;
//public:
//	Heap(){}
//	Heap(const T* a,size_t n)
//	{
//		_a.reserve(n);
//		for(size_t i =0;i < n;++i )
//		{
//			_a.push_back(a[i]);
//		}
//
//		for(int  i = (n-2)/2;i >= 0;--i)
//		{
//			_AdjustDown(i);
//		}
//	}
//
//
//	void Push(const T& x)
//	{
//		_a.push_back(x);
//		_AdjustUp(_a.size()-1);
//	}
//
//	void Pop()
//	{
//		assert(!_a.empty());
//		swap(_a[0],_a[_a.size()-1]);
//		_a.pop_back();
//		_AdjustDown(0);
//	}
//
//	bool Empty()
//	{
//		return _a.empty();
//	}
//
//	size_t Size()
//	{
//		return _a.size();
//	}
//
//	T& Top()
//	{
//		return _a[0];
//	}
//
//protected:
//	void _AdjustDown(size_t root)
//	{
//		size_t parent = root;
//		size_t child = root*2+1;
//
//		while(child < _a.size())
//		{
//			if(child+1 < _a.size() && _a[child+1] > _a[child])
//			{
//				++child;
//			}
//
//			if(_a[child] > _a[parent])
//			{
//				swap(_a[child],_a[parent]);
//				parent = child;
//				child = parent*2+1;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//
//	void _AdjustUp(size_t child)
//	{
//		size_t parent = (child-1)/2;
//
//		while(child > 0)
//		{
//			if(_a[child] >  _a[parent])
//			{
//				swap(_a[child],_a[parent]);
//				child = parent;
//				parent = (child-1)/2;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//};
//
////int main()
////{
////	int a[] = {10,11, 13, 12, 16, 18, 15, 17, 14, 19};
////	Heap<int> hp(a, sizeof(a)/sizeof(a[0]));
////
////	hp.Push(20);
////	hp.Pop();
////}
//
//
////堆排序  降序  采用小堆
///*void AdjustDown(int* a,size_t n,int root)
//{
//	int parent = root;
//	int child = parent*2+1;
//
//	while(child < n)
//	{
//		if(child+1 < n && a[child+1] < a[child])
//			++child;
//
//		if(a[child] < a[parent] )
//		{
//			swap(a[child],a[parent]);
//			parent = child;
//			child = parent*2+1;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//
//void Heapsort(int* a,int size)
//{
//	for(int i = (size-2)/2;i>=0;--i)
//	{
//		AdjustDown(a,size,i);  //小堆
//	}
//
//	for(int i = 0;i < size; ++i)
//	{
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;
//	int end = size-1;
//	while(end > 0)
//	{
//		swap(a[0],a[end]);
//		AdjustDown(a,end,0);
//		end--;
//	}
//
//	for(int i = 0;i < size; ++i)
//	{
//		cout<<a[i]<<" ";
//	}
//
//}
//*/
////int main()
////{
////	int a[] = {2,3,6,8,9,3,5,6,10};
////	Heapsort(a, sizeof(a)/sizeof(a[0]));
////	
////}
//
////topk问题
////先建立K个数的堆，如果是求最大k个数，那么就建立小堆
////如果查找K个小数，就建大堆
//
////这里查询最大的K个数
//
//
//void AdjustDown(vector<int>& a,int root)
//{
//	int parent = root;
//	int child = parent*2+1;
//
//	while(child < a.size())
//	{
//		if(child+1 < a.size() && a[child+1] < a[child])
//			++child;
//
//		if(a[child] < a[parent] )
//		{
//			swap(a[child],a[parent]);
//			parent = child;
//			child = parent*2+1;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//
//void Topk(const vector<int>& a,int k)
//{
//
//	assert(a.size() >= k);
//	vector<int> topk;
//	for(int i = 0;i < k;++i)
//	{
//		topk.push_back(a[i]);
//	}
//
//	for(int i = (k-2)/2;i >=0;--i)
//	{
//		AdjustDown(topk,i);
//	}
//	for(int i = k;i < a.size();++i)
//	{
//		if(topk[0] < a[i])
//		{
//			topk[0] = a[i];
//			AdjustDown(topk,0);
//		}
//	}
//
//	for(int i = 0; i < k;++i)
//	{
//		cout<<topk[i]<<" ";
//	}
//	cout<<endl;
//}
//
//void TestTopk()
//{
//	vector<int> v;
//	v.resize(100, 10);
//
//	v[4] = 100;
//	v[5] = 101;
//	v[6] = 102;
//	v[7] = 103;
//
//	v[40] = 104;
//	v[55] = 105;
//	v[60] = 106;
//	v[70] = 107;
//
//	Topk(v, 9);
//}
//
//int main()
//{
//	TestTopk();
//}
//


#include<iostream>
#include<queue>
using namespace std;

//int main()
//{
//	priority_queue <int,vector<int>,less<int> > p;
//	priority_queue <int,vector<int>,greater<int> > q;
//	int a[5]={10,12,14,6,8};
//	
//		for(int i=0;i<5;i++)
//			p.push(a[i]),q.push(a[i]);
//
//		printf("less<int>:");
//			while(!p.empty())
//				printf("%d ",p.top()),p.pop();  
//
//		printf("\ngreater<int>:");
//			while(!q.empty())
//				printf("%d ",q.top()),q.pop();
//	
//}
