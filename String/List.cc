//C++实现双向链表

#include<iostream>
using namespace std;

#define DataType int
struct ListNode
{
	ListNode* _prev;
	ListNode* _next;
    DataType _data;

	ListNode(DataType x)
		:_prev(NULL)
		,_next(NULL)
		,_data(x)
	{}
};

class List
{
private:
	typedef ListNode node;
	node* _head;
	node* _tail;
public:

};