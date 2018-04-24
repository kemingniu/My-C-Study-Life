#pragma once
#include <vector>

namespace OPEN
{

enum State
{
	EMPTY = 1,
	EXITS = 2,
	DELETE = 3,
};

template<class K, class V>
struct HashNode
{
	K _key;
	V _value;
	State	  _state;

	HashNode()
		:_state(EMPTY)
	{}
};

template<class K>
struct _HashFunc
{	
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct _HashFunc<string>
{
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str )
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str()); 
	}
};

template<class K, class V, class __HashFunc = _HashFunc<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{}

	bool Insert(const K& key, const V& value)
	{
		CheckCapacity();

		size_t hash = HashFunc(key);
		size_t index = hash;
		size_t i = 1;
		while (_tables[index]._state == EXITS)
		{
			if (_tables[index]._key == key)
			{
				return false;
			}

			// 线性探测或者二次探测
			/*++index;
			if (index == _tables.size())
			{
				index = 0;
			}*/

			index = (hash+i*i) % _tables.size();
			++i;
		}

		_tables[index]._key = key;
		_tables[index]._value = value;
		_tables[index]._state = EXITS;
		++_size;

		return true;
	}

	Node* Find(const K& key)
	{
		size_t index = HashFunc(key);
		while (_tables[index]._state != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if(_tables[index]._state != DELETE)
					return &_tables[index];
				else
					return NULL;
			}
			++index;
			if(index == _tables.size())
				index = 0;
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* ret = Find(key);
		if(ret)
		{
			ret->_state = DELETE;
			--_size;
			return true;
		}
		else
		{
			return false;
		}
	}

	size_t HashFunc(const K& key)
	{
		__HashFunc func;
		return func(key) % _tables.size();
	}

	size_t GetNextPrime(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList [_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for (int i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}

		return _PrimeList[_PrimeSize-1];
	}

	void CheckCapacity()
	{
		if (_tables.size() == 0)
		{
			_tables.resize(GetNextPrime(1));
		}
		else if(_size*10 / _tables.size() >= 7)
		{
			HashTable<K, V, __HashFunc> newTables;
			newTables._tables.resize(GetNextPrime(_tables.size()));
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._state == EXITS)
				{
					newTables.Insert(_tables[i]._key, _tables[i]._value);
				}
			}

			_tables.swap(newTables._tables);
		}
	}

private:
	vector<Node> _tables;
	size_t _size;
};


void TestHashTable()
{
	int a[] = {89, 18, 49, 58, 9};
	HashTable<int, int> t;
	for (size_t i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		t.Insert(a[i], i);
	}

	for (size_t i = 0; i < 100; ++i)
	{
		t.Insert(i, 0);
	}

	HashTable<string, string> dict;
	dict.Insert("left", "左边");
	dict.Insert("right", "右边");
	dict.Insert("string", "字符串");
	dict.Insert("left", "左边");

	//HashTable<StudentInfo, string, HashFuncStuInfo> infoMap;
}
}


//namespace HASH_BUCKET
//{
//
//template<class K, class V>
//struct HashNode
//{
//	K _key;
//	V _value;
//
//	HashNode<K, V>* _next;
//
//	HashNode(const K& key, const V& value)
//		:_key(key)
//		,_value(value)
//		,_next(NULL)
//	{}
//};
//
//template<class K, class V>
//class HashTable
//{
//	typedef HashNode<K, V> Node;
//public:
//	HashTable()
//		:_size(0)
//	{}
//
//	~HashTable()
//	{
//		for (size_t i = 0; i < _tables.size(); ++i)
//		{
//			Node* cur = _tables[i];
//			while(cur)
//			{
//				Node* next = cur->_next;
//				delete cur;
//				cur = next;
//			}
//
//			_tables[i] = NULL;
//		}
//	}
//
//	size_t GetNextPrime(size_t size)
//	{
//		const int _PrimeSize = 28;
//		static const unsigned long _PrimeList [_PrimeSize] =
//		{
//			53ul,         97ul,         193ul,       389ul,       769ul,
//			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
//			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
//			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
//			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
//			1610612741ul, 3221225473ul, 4294967291ul
//		};
//
//		for (int i = 0; i < _PrimeSize; ++i)
//		{
//			if (_PrimeList[i] > size)
//			{
//				return _PrimeList[i];
//			}
//		}
//
//		return _PrimeList[_PrimeSize-1];
//	}
//
//	void CheckCapacity()
//	{
//		// 负载因子到1，则增容
//		if (_size == _tables.size())
//		{
//			vector<Node*> newTables;
//			newTables.resize(GetNextPrime(_tables.size()), NULL);
//			// 重新负载
//			for(size_t i = 0; i < _tables.size(); ++i)
//			{
//				Node* cur = _tables[i];
//				while (cur)
//				{
//					Node* next = cur->_next;
//					size_t index = HashFunc(cur->_key, newTables.size());
//					
//					// 头插
//					cur->_next = newTables[index];
//					newTables[index] = cur;
//
//					cur = next;
//				}
//			}
//
//			_tables.swap(newTables);
//		}
//	}
//
//	bool Insert(const K& key, const V& value)
//	{
//		// 增容 
//		CheckCapacity();
//
//		size_t index = HashFunc(key, _tables.size());
//		Node* cur = _tables[index];
//		while (cur)
//		{
//			if(cur->_key == key)
//			{
//				return false;
//			}
//
//			cur = cur->_next;
//		}
//		
//		Node* tmp = new Node(key, value);
//		tmp->_next = _tables[index];  //头插  
//		_tables[index] = tmp;
//		++_size;
//
//		return true;
//	}
//
//	Node* Find(const K& key)
//	{
//		size_t index = HashFunc(key, _tables.size());
//		Node* cur = _tables[index];
//		while (cur)
//		{
//			if (cur->_key == key)
//			{
//				return cur;
//			}
//
//			cur = cur->_next;
//		}
//
//		return NULL;
//	}
//
//	/*bool Remove(const K& key)
//	{
//		size_t index = HashFunc(key, _tables.size());
//		Node* cur = _tables[index];
//		if (cur && cur->_key == key) //如果第一个就是要删除的对象
//		{
//			_tables[index] = cur->_next;
//			delete cur;
//			--_size;
//
//			return true;
//		}
//
//		Node* prev = NULL;    //前后指针
//		while (cur)          //被删对象的前一个 直接指向被删对象的后一个，并且释放次删除对象
//		{
//			if (cur->_key == key)
//			{
//				prev->_next = cur->_next;
//				delete cur;
//				--_size;
//
//				return true;
//			}
//			else
//			{
//				prev = cur;
//				cur = cur->_next;
//			}
//		}
//		
//
//		return false;
//	}*/
//
//	bool Remove(const K& key)
//	{
//		Node* pos = Find(key);
//		if (pos)
//		{
//			if(pos->_next) //存在下一个，不是当前链的最后一个
//			{
//				Node* next = pos->_next;
//				pos->_key = next->_key;
//				pos->_value = next->_value;
//
//				pos->_next = next->_next;
//				delete next;
//			}
//			else //删除的是尾  首尾替换
//			{
//				size_t index = HashFunc(pos->_key, _tables.size());
//				Node* head = _tables[index];
//				pos->_key = head->_key;
//				pos->_value = head->_value;
//
//				_tables[index] = head->_next;
//				delete head;
//			}
//
//			--_size;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	size_t HashFunc(const K& key, size_t size)
//	{
//		return key % size;
//	}
//
//private:
//	//Node* _tables[]; 
//	vector<Node*> _tables;
//	size_t _size;
//};
//
//void TestHashTable()
//{
//	int a[] = {51, 105, 52, 3, 55, 2, 106, 53, 0};
//	HashTable<int, int> ht;
//	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
//	{
//		ht.Insert(a[i], i);
//	}
//
//	for (size_t i = 100; i < 154; ++i)
//	{
//		ht.Insert(i, 0);
//	}
//}
//
//}
//    迭代器实现
namespace HASH_BUCKET
{

template<class ValueType>
struct HashNode
{
	ValueType _valueField;

	HashNode<ValueType>* _next;

	HashNode(const ValueType& valueField)
		:_valueField(valueField)
		,_next(NULL)
	{}
};

template<class K, class V, class __HashFunc, class __KeyOfValue>
class HashTable;  //这里不加上下面找不到，类似声明

template<class K, class V, class __HashFunc, class __KeyOfValue>
struct __HashTableIterator
{
	typedef HashNode<V> Node;
	typedef __HashTableIterator<K, V, __HashFunc, __KeyOfValue> Self;

	Node* _node;
	HashTable<K, V, __HashFunc, __KeyOfValue>* _hashTables;

	__HashTableIterator(Node* node, HashTable<K, V, __HashFunc, __KeyOfValue>* hashTable)
		:_node(node)
		,_hashTables(hashTable)
	{}

	V& operator*()
	{
		return _node->_valueField;
	}

	V* operator->()
	{
		return &(_node->_valueField);
	}

	bool operator==(const Self& s) const
	{
		return _node == s->_node;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	Self& operator++()
	{//如果当前桶没有走完
	//否则找下一个不为空的桶
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			__KeyOfValue keyOfValue;
			Node* cur = NULL;
			size_t index = _hashTables->HashFunc(keyOfValue(_node->_valueField), _hashTables->_tables.size());
			for(size_t i = index+1; i < _hashTables->_tables.size(); ++i)
			{
				cur = _hashTables->_tables[i];
				if (cur)
				{
					break;
				}
			}

			_node = cur;   //
		}

		return *this;
	}
	
	Self& operator--()
	{
		
	}
};

template<class K>
struct _HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct _HashFunc<string>
{
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str )
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str()); 
	}
};

template<class K, class V>
struct _KeyOfValue
{
	const K& operator()(const V& value)
	{
		return value;
	}
};

template<class K, class V>
struct _PairKeyOfValue
{
	const K& operator()(const V& value)
	{
		return value.first;
	}
};

template<class K, class V, class __HashFunc = _HashFunc<K>,
					class __KeyOfValue = _KeyOfValue<K, V>>
class HashTable
{
	typedef V ValueType;
	typedef HashNode<ValueType> Node;

	friend struct __HashTableIterator<K, V, __HashFunc, __KeyOfValue>;
public:

	typedef __HashTableIterator<K, V, __HashFunc, __KeyOfValue> Iterator;
	HashTable()
		:_size(0)
	{}

	~HashTable()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			Node* cur = _tables[i];
			while(cur)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}

			_tables[i] = NULL;
		}
	}

	Iterator Begin()
	{
		Node* cur = NULL;
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			cur = _tables[i];
			if (_tables[i])
			{
				break;
			}
		}

		return Iterator(cur, this);
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

	size_t GetNextPrime(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList [_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for (int i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}
	
		return _PrimeList[_PrimeSize-1];
	}

	void CheckCapacity()
	{
		// 负载因子到1，则增容
		if (_size == _tables.size())
		{
			__KeyOfValue keyOfValue;
			vector<Node*> newTables;
			newTables.resize(GetNextPrime(_tables.size()), NULL);
			// 重新负载
			for(size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					size_t index = HashFunc(keyOfValue(cur->_valueField), newTables.size());
					
					// 头插
					cur->_next = newTables[index];
					newTables[index] = cur;

					cur = next;
				}
			}

			_tables.swap(newTables);
		}
	}

	pair<Iterator, bool> Insert(const ValueType& valueField)
	{
		// 增容 
		CheckCapacity();

		__KeyOfValue keyOfValue;
		size_t index = HashFunc(keyOfValue(valueField), _tables.size());
		Node* cur = _tables[index];
		while (cur)
		{
			if(keyOfValue(cur->_valueField)
				== keyOfValue(valueField))
			{
				return make_pair(Iterator(cur, this), false);
			}

			cur = cur->_next;
		}
		
		Node* tmp = new Node(valueField);
		tmp->_next = _tables[index];
		_tables[index] = tmp;
		++_size;

		return make_pair(Iterator(tmp, this), true);

	}

	Iterator Erase(Iterator pos)
	{	
		Iterator next = pos;
		++next;

		__KeyOfValue keyOfValue;
		size_t index = HashFunc(keyOfValue(pos._node->_valueField), _tables.size());
		Node* prev = NULL;
		Node* cur = _tables[index];
		while (cur)
		{
			if (keyOfValue(cur->_valueField) == keyOfValue(*pos))
			{
				if (prev == NULL)
				{
					_tables[index] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}

				delete cur;

				return next;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}

		assert(false);
	}

	size_t Erase(const K& key)
	{
		size_t index = HashFunc(key, _tables.size());
		Node* cur = _tables[index];
		if (cur && cur->_key == key)
		{
			_tables[index] = cur->_next;
			delete cur;
			--_size;

			return 1;
		}

		Node* prev = NULL;
		while (cur)
		{
			if (cur->_key == key)
			{
				prev->_next = cur->_next;
				delete cur;
				--_size;

				return 1;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		

		return 0;
	}

	void Reserver(size_t n)
	{
		_tables.resize(n, NULL);
	}

	Iterator Find(const K& key)
	{
		__KeyOfValue keyOfValue;
		size_t index = HashFunc(key, _tables.size());
		Node* cur = _tables[index];
		while (cur)
		{
			if (keyOfValue(cur->_valueField) == key)
			{
				return Iterator(cur, this);
			}

			cur = cur->_next;
		}

		return Iterator(NULL, this);
	}

	size_t HashFunc(const K& key, size_t size)
	{
		//return key % size;
		__HashFunc hashfunc;
		return hashfunc(key) % size;
	}

private:
	vector<Node*> _tables;
	size_t _size;
};

void TestHashTable()
{
	int a[] = {51, 105, 52, 3, 55, 2, 106, 53, 0};
	HashTable<int, int> hashset;
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		hashset.Insert(a[i]);
	}


	HashTable<int, int>::Iterator setIt = hashset.Begin();
	while (setIt != hashset.End())
	{
		cout<<*setIt<<" ";
		++setIt;
	}
	cout<<endl;

	HashTable<string, string> dictset;
	dictset.Insert("sort");
	dictset.Insert("string");
	dictset.Insert("int");
	

	HashTable<int, pair<int, int>, _HashFunc<int>, _PairKeyOfValue<int, pair<int, int>>> hashmap;
	hashmap.Insert(make_pair(1, 1));
	hashmap.Insert(make_pair(100, 100));
}

}