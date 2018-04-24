#pragma once

#include "MyMap.h"

//template<class K, class V>
//struct Pair{};

template<class K, class V>
class Map
{
	typedef pair<K, V> ValueType;

	struct KeyOfValue
	{
		K operator()(const ValueType& kv)
		{
			return kv.first;
		}
	};

public:
	typedef typename RBTree<K, ValueType, KeyOfValue>::Iterator Iterator;

	pair<Iterator, bool> Insert(const ValueType& kv)
	{
		return _tree.Insert(kv);
	}

	V& operator[](const K& key)
	{
		//pair<Iterator, bool> ret = Insert(make_pair(key, V()));
		//return ret.first->second;
		return (*(Insert(make_pair(key, V())).first)).second;
	}

	Iterator Find(const K& key)
	{
		return _tree.Find(key);
	}

	Iterator Begin()
	{
		return _tree.Begin();
	}

	Iterator End()
	{
		return _tree.End();
	}

private:
	RBTree<K, ValueType, KeyOfValue> _tree;
};

void TestMap()
{
	Map<int, double> m1;
	m1.Insert(make_pair(2, 1.1));
	m1.Insert(make_pair(1, 2.2));
	m1[10] = 10.10;
	m1[2] = 2.2;
	m1[1] = 1.1;


	Map<int, double>::Iterator it = m1.Begin();
	while (it != m1.End())
	{
		cout<<it->first<<":"<<it->second<<endl;
		++it;
	}
	cout<<endl;

	Map<string, string> dict;
	dict["string"] = "×Ö·û´®";
	dict["right"] = "ÓÒ±ß";
	dict["left"] = "×ó±ß";
}