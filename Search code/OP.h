#pragma once

#include "MyMap.h"
#include "MyUnOrderedMap.h"
#include <Windows.h>
#include <time.h>

void TestOP()
{
	Map<int, string> dict1;
	UnOrderedMap<int, string> dict2;

	const size_t N = 10000000;
	srand(time(0));
	vector<size_t> v;
	v.reserve(N);
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(rand());
	}

	int begin = GetTickCount();
	for (size_t i = 0; i < v.size(); ++i)
	{
		dict1[v[i]] = "UnOrderedMap<int, string> dict2";
	}

	for (size_t i = 0; i < v.size(); ++i)
	{
		dict1.Find(rand());
	}
	int end = GetTickCount();
	cout<<"Map::"<<end-begin<<endl;


	begin = GetTickCount();
	dict2.Reserver(N);
	for (size_t i = 0; i < v.size(); ++i)
	{
		dict2[v[i]] = "UnOrderedMap<int, string> dict2";
	}

	for (size_t i = 0; i < v.size(); ++i)
	{
		dict2.Find(rand());
	}
	end = GetTickCount();
	cout<<"UnOrderedMap::"<<end-begin<<endl;
}