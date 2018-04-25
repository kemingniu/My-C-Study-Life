#ifndef __STRING2_H__
#define __STRING2_H__

#include<iostream>
using namespace std;

//实现string类的部分接口，并采用拷贝构造

class String2
{
public:
	String2(const char* str ="")
		:_str(new char[strlen(str)+1+4])
	{
		strcpy(_str+4,str);
		_str += 4;
		GetRefCount() = 1;
	}
	String2(const String2& s)
		:_str(s._str)
	{
		GetRefCount()++;
	}
	String2& operator=(const String2& s)
	{
		if(this != &s)
		{
			Release();
			_str = s._str;
			GetRefCount()++;
		}
		return *this;
	}
	~String2()
	{
		Release();
	}
	void Release()
	{
		if(--GetRefCount() == 0)
		{
			delete[] (_str-4);
		}
	}
	int& GetRefCount()
	{
		return *((int*)(_str-4));
	}
	void CopyOnWrite()
	{
		if(GetRefCount() > 1)
		{
			char* newstr = new char[strlen(_str)+1+4];
			strcpy(newstr+4,_str);
			newstr += 4;
			GetRefCount()--;
			_str = newstr;
			GetRefCount() = 1;
		}
	}
	char& operator[](size_t pos)
	{
		CopyOnWrite();
		return _str[pos];
	}
	char operator[](size_t pos)const 
	{
		return _str[pos];
	}
	char* GetStr()
	{
		return _str;
	}
	size_t GetLength()
	{
		return strlen(_str);
	}
private:
	char* _str;
	
};

#endif
