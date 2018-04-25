/*C++实现单链表
***
*/
#include<iostream>
#include<assert.h>
using namespace std;

#define DataType int

struct SlistNode
{
	SlistNode* _next;
	DataType _data;

	SlistNode(const DataType x)
		:_data(x)
		,_next(NULL)
	{}
};


class SList
{
private:
	typedef SlistNode node;
	node* _head;
	node* _tail;
public:
	SList()
		:_head(NULL)
		,_tail(NULL)
	{}
	void Copy(const SList& s)
	{
		node* tmp = s._head;
		while(tmp)
		{
			PushBack(tmp->_data);
			tmp = tmp->_next;
		}
	}
	void Destroy()
	{
		node* cur = _head;
		while(cur)
		{
			node* tmp = cur->_next;
			delete cur;
			cur = tmp;
		}
		_head = _tail = NULL;
	}
	SList(const SList& s)
		:_head(NULL)
		,_tail(NULL)
	{
		Copy(s);
	}
	 /*SList& operator=(const SList& s)
	 {
		 if(this != &s)
		 {
			 Destroy();
			 Copy(s);
		 }
		 return *this;
	 }*/

	 SList& operator=( SList& s) //swap操作是一个很有效的操作
	 {
		 swap(_head,s._head);
		 swap(_tail,s._tail);
		 return *this;
	 }
	
	 ~SList()
	 {
		 Destroy();
	 }

	 void PushBack(DataType x)
	 {
		 if(_head == NULL)
		 {
			 _head = _tail = new node(x);
		 }
		 else 
		 {
			 node* newtail = new node(x);
			 _tail->_next = newtail;
			 _tail = _tail->_next;
		 }
		 
	 }

	 void PopBack()
	 {
		 if(_head == NULL)
		 {
			return ;
		 }
		 else if(_head == _tail)
		 {
			 delete _tail;
			 _tail = _head = NULL;
		 }
		 else
		 {
			 node* cur  = _head;
			 while(cur->_next != _tail)
			 {
				 cur = cur->_next;
			 }
			 delete _tail;
			 _tail = cur;
		 }
	 }

	 void PushFront(DataType x)
	 {
		 if(_head == NULL)
		 {
			 _head = _tail = new node(x);
			 return;
		 }
		 else 
		 {
			 node* newnode = new node(x);
			 newnode->_next = _head;
			 _head = newnode;
		 }
		 
	 }

	 void PopFront()
	 {
		 if(_head == NULL)
		 {
			 return;
		 }
		 else if(_head == _tail)
		 {
			 delete _head;
			 _head = _tail = NULL;
		 }
		 else
		 {
			 node* tmp = _head;
			 _head = _head->_next;
			 delete tmp;
		 }
	 }

	 void Insert(node* pos,DataType x)//在pos前面插入一个节点
	 {
		 assert(pos);
		 if(_head == pos)
		 {
			 PushFront(x);
		 }
		 else
		 {
			 node* tmp = new node(x);
			 node* cur = _head;
			 while(cur->_next != pos)
			 {
				 cur = cur->_next;
			 }
			 tmp->_next = pos;
			 cur->_next = tmp;
		 }
	 }

	 void Erase(node* pos)
	 {
		 assert(pos);
		 if(pos == _head)
		 {
			 PopFront();
	 }else
		 {
			 node* cur = _head;
			 while(cur->_next != pos)
			 {
				 cur = cur->_next;
			 }

			 cur->_next = pos->_next;
			 delete pos;
		 }
	 }
	 node* Find(DataType x)
	 {
		 assert(_head);
		 node* cur = _head;
		 while(cur)
		 {
			 if(cur->_data == x)
				 return cur;
			 cur = cur->_next;
		 }
		 return NULL;
	 }

	 void Print()
	 {

		 node* cur = _head;
		 while(cur)
		 {
			 cout<<cur->_data<<" ";
			 cur = cur->_next;
		 }
		 cout<<endl;
	 }
};

	 void TestSlist1()
	 {
		 SList s1;
		 s1.PushBack(1);
		 s1.PushBack(2);
		 s1.PushBack(3);
		 s1.PushBack(4);
		 s1.Print();

		 s1.PopBack();
		 s1.PopBack();
		 s1.PopBack();
		 s1.PopBack();
		 s1.PopBack();
		 s1.Print();

		 s1.PushFront(0);
		 s1.PushFront(1);
		 s1.PushFront(2);
		 s1.PushFront(3);
		 s1.Print();

		 s1.PopFront();
		 s1.PopFront();
		 s1.PopFront();
		 s1.PopFront();
		 s1.PopFront();
		 s1.Print();
	 }

	 void TestSlist2()
	 {
		 SList s1;
		 s1.PushBack(1);
		 s1.PushBack(2);
		 s1.PushBack(3);
		 s1.PushBack(4);
		 s1.Print();

		 SlistNode* pos = s1.Find(3);
		 s1.Insert(pos, 30);
		 s1.Print();

		 s1.Erase(pos);
		 s1.Print();
	 }

	 void TestSlist3()
	 {
		 SList s1;
		 s1.PushBack(1);
		 s1.PushBack(2);
		 s1.PushBack(3);
		 s1.PushBack(4);
		 s1.Print();

		 SList s2(s1);
		 s2.PushBack(10);
		 s2.PushBack(11);
		 s2.Print();

		 s1 = s2;
		 s1.Print();
	 }

int main()
{
	TestSlist2();
	return 0;
}
