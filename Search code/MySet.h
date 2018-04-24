#pragma once

#include "RBTree.h"

template<class K>
class Set
{
	struct KeyOfValue
	{
		K operator()(const K& key)
		{
			return key;
		}
	};

public:
	typedef typename RBTree<K, K, KeyOfValue>::Iterator Iterator;

	pair<Iterator, bool> Insert(const K& key)
	{
		return _t.Insert(key);
	}

	Iterator Begin()
	{
		return _t.Begin();
	}

	Iterator End()
	{
		return _t.End();
	}

	/*Iterator Find(const K& key)
	{
		return _t.Find(key);
	}*/
private:
	RBTree<K, K, KeyOfValue> _t;
};

void TestSet()
{
	Set<int> s1;
	s1.Insert(1);
	s1.Insert(5);
	s1.Insert(7);
	s1.Insert(2);

	Set<int>::Iterator it1 = s1.Begin();
	while (it1 != s1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}