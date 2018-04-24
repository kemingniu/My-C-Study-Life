#pragma once

#include "HashTable.h"

template<class K, class V, class __HashFunc = HASH_BUCKET::_HashFunc<K>>
class UnOrderedMap
{
	typedef HASH_BUCKET::HashTable<K, pair<K, V>, __HashFunc, HASH_BUCKET::_PairKeyOfValue<K, pair<K, V>>> HashTable;
public:
	typedef typename HashTable::Iterator Iterator;

	pair<Iterator, bool> Insert(const pair<K, V> kv)
	{
		return _tables.Insert(kv);
	}

	Iterator Find(const K& key)
	{
		return _tables.Find(key);
	}

	Iterator Begin()
	{
		return _tables.Begin();
	}

	Iterator End()
	{
		return _tables.End();
	}

	V& operator[](const K& key)
	{
		pair<Iterator, bool> ret = Insert(make_pair(key, V()));
		return ret.first->second;
	}

	void Reserver(size_t n)
	{
		_tables.Reserver(n);
	}

	HashTable _tables;
};

void TestUnOrderedMap()
{
	UnOrderedMap<string, string> dict;
	dict["sort"] = "ÅÅÐò";
	dict["string"] = "×Ö·û´®";
	dict["map"] = "Ó³Éä";
	dict["left"] = "×ó±ß";
	dict["left"] = "Ê£Óà";

	UnOrderedMap<string, string>::Iterator it = dict.Begin();
	while (it != dict.End())
	{
		cout<<it->first<<":"<<it->second<<endl;
		++it;
	}
}