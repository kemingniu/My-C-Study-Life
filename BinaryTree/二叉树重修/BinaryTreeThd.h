#pragma once

enum PointerTag{THREAD,LINK};//THREAD = 0,��ʾָ��ǰȥ���ߺ�̵�������link = 1����ʾָ�����Һ��ӵ�ָ��

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
