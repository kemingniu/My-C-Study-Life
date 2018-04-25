#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
using namespace std;
//实现一个简易的string类,这里实现的是深拷贝
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
			String tmp(s._str);//建立临时对象，出作用域后自动析构
			swap(_str,tmp._str);
		}
		return *this;
	}

	/*String& operator=( String s) //简单点
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