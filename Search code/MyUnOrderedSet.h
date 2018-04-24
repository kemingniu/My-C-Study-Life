#pragma once

#include "HashTable.h"

template<class K, class __HashFunc = HASH_BUCKET::_HashFunc<K>>
class UnOrderedSet
{
	typedef HASH_BUCKET::HashTable<K, K, __HashFunc> HashTable;
public:
	typedef typename HashTable::Iterator Iterator;

	pair<Iterator, bool> Insert(const K& key)
	{
		return _tables.Insert(key);
	}

	Iterator Find(const K& key)
	{
		return _tables.Find(key);
	}

	Iterator Erase(Iterator pos)
	{
		return _tables.Erase(pos);
	}

	size_t Erase(const K& key)
	{
		Iterator pos = Find(key);
		if (pos != End())
		{
			Erase(pos);
			return 1;
		}

		return 0;
	}

	Iterator Begin()
	{
		return _tables.Begin();
	}

	Iterator End()
	{
		return _tables.End();
	}

protected:
	HashTable _tables;
};

void TestUnOrderSet()
{
	UnOrderedSet<int> ht;
	ht.Insert(3);
	ht.Insert(1);
	ht.Insert(6);
	ht.Insert(3);

	UnOrderedSet<int>::Iterator it = ht.Begin();
	while (it != ht.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	
	it = ht.Find(1);
	it = ht.Erase(it);

	it = ht.Begin();
	while (it != ht.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}