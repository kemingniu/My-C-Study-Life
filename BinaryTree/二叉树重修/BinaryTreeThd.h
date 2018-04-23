#pragma once

enum PointerTag{THREAD,LINK};//THREAD = 0,表示指向前去或者后继的线索，link = 1，表示指向左右孩子的指针

template<typename T>
struct BinaryTreeNodeThd{
	T _data;
	BinaryTreeNodeThd<T>* _left;
	BinaryTreeNodeThd<T>* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNodeThd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};
