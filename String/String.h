#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
using namespace std;
//ʵ��һ�����׵�string��,����ʵ�ֵ������
class String{
public:
	String(const char* str="")
		:_str(new char[strlen(str)+1])
	{
		strcpy(_str,str);
	}
	String(const String& s)
		:_str(NULL)
	{
		String tmp(s._str);
		swap(_str,tmp._str);
	}
	String& operator=(const String& s)
	{
		if(this != &s)
		{
			String tmp(s._str);//������ʱ���󣬳���������Զ�����
			swap(_str,tmp._str);
		}
		return *this;
	}

	/*String& operator=( String s) //�򵥵�
	{
		swap(_str,s._str);
		return *this;
	}*/

	~String()
	{
		if(_str)
		{
			delete[] _str;
			_str = NULL;
		}
	}
	char* GetStr()
	{
		return _str;
	}
	char& operator[](size_t pos)
	{
		return _str[pos];
	}
private:
	char* _str;

};



#endif