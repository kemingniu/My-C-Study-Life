#pragma once

#include <set>

// ¼üÖµ¶Ô key/value
//template<class K, class V>
//struct pair
//{
//	K first;
//	V second;
//
//	pair(const K& key, const V& value)
//		:first(key)
//		,second(value)
//	{}
//};

//void test_set()
//{
//	pair<set<int>::iterator, bool> ret;
//	set<int> s1;
//	s1.insert(4);
//	s1.insert(40);
//	s1.insert(12);
//	s1.insert(1);
//	ret = s1.insert(9);
//	ret = s1.insert(3);
//	ret = s1.insert(9);
//	s1.insert(9);
//
//	set<int>::iterator it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		cout<<*it1<<" ";
//		++it1;
//	}
//	cout<<endl;
//
//
//	set<int> s2;
//	int a[4] = {3, 4, 9, 0};
//	//s2.insert(++s1.begin(), --s1.end());
//	s2.insert(a, a+4);
//	set<int>::iterator it2 = s2.begin();
//	while (it2 != s2.end())
//	{
//		cout<<*it2<<" ";
//		++it2;
//	}
//	cout<<endl;
//}

//void test_set()
//{
//	pair<set<int>::iterator, bool> ret;
//	set<int> s1;
//	s1.insert(4);
//	s1.insert(40);
//	s1.insert(12);
//	s1.insert(1);
//	ret = s1.insert(9);
//	ret = s1.insert(3);
//	ret = s1.insert(9);
//	s1.insert(9);
//
//	set<int>::iterator it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		cout<<*it1<<" ";
//		++it1;
//	}
//	cout<<endl;
//
//	set<int>::iterator pos = s1.find(30);
//	if (pos != s1.end())
//	{
//		s1.erase(pos);
//	}
//
//	//s1.erase(30);
//	set<int>::iterator first = s1.lower_bound(3);
//	++first;
//	set<int>::iterator last = s1.upper_bound(20);
//	s1.erase(first, last);
//
//	it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		cout<<*it1<<" ";
//		++it1;
//	}
//	cout<<endl;
//
//	//pos = s1.find(3);
//	//if (pos != s1.end())
//	if(s1.count(3))
//	{
//		cout<<"´æÔÚ"<<endl;
//	}
//}

#include <map>
#include <string>

//template<class K, class V>
//pair<K, V> make_pair(const K& k, const V& v)
//{
//	return pair<K, V>(k, v);
//}

//void test_map()
//{
//	// ÊµÏÖ×Öµä
//	map<string, string> dict;
//	dict.insert(pair<string, string>("sort", "ÅÅĞò"));
//	dict.insert(pair<string, string>("insert", "²åÈë"));
//	dict.insert(pair<string, string>("erase", "É¾³ı"));
//	dict.insert(pair<string, string>("left", "×ó±ß"));
//
//	dict["left"] = "Ê£Óà";
//	cout<<dict["left"]<<endl;
//	cout<<dict["right"]<<endl;
//
//	//dict.erase("sort");
//	map<string, string>::iterator it = dict.begin();
//	while (it != dict.end())
//	{
//	//	cout<<(*it).first<<":"<<(*it).second<<endl;
//		cout<<it->first<<":"<<it->second<<endl;
//		++it;
//	}
//
//	string strs[] = {"sort", "insert","sort","sort","sort", "insert", "left"};
//	map<string, int> countMap;
//	cout<<countMap["right"]<<endl;
//
//	for (size_t i = 0; i < sizeof(strs)/sizeof(string); ++i)
//	{
//		countMap[strs[i]]++;
//		//map<string, int>::iterator pos = countMap.find(strs[i]);
//		//if (pos != countMap.end())
//		//{
//		//	pos->second++;
//		//	//(*pos).second++;
//		//}
//		//else
//		//{
//		//	countMap.insert(make_pair(strs[i], 1));
//		//}
//	}
//}

//void test_map()
//{
//	// ÊµÏÖ×Öµä
//	map<string, string> dict;
//	dict["left"] = "×ó±ß";
//	dict["left"] = "Ê£Óà";
//	dict["sort"] = "ÅÅĞò";
//	map<string, string>::iterator it = dict.begin();
//	while (it != dict.end())
//	{
//		cout<<it->first<<":"<<it->second<<endl;
//		++it;
//	}
//
//	string strs[] = {"sort", "insert","sort","sort","sort", "insert", "left"};
//	map<string, int> countMap;
//	for (size_t i = 0; i < sizeof(strs)/sizeof(string); ++i)
//	{
//		//countMap[strs[i]]++;
//		pair<map<string, int>::iterator, bool> ret = countMap.insert(make_pair(strs[i], 1));
//		if (ret.second == false)
//		{
//			ret.first->second++;
//		}
//	}
//}

void test_set()
{
	set<int> s1;
	s1.insert(1);
	s1.insert(1);
	s1.insert(2);
	s1.insert(0);
	s1.insert(5);
	s1.insert(0);
	s1.insert(4);
	s1.insert(3);

	multiset<int> s2;
	s2.insert(1);
	s2.insert(1);
	s2.insert(2);
	s2.insert(0);
	s2.insert(5);
	s2.insert(0);
	s2.insert(4);
	s2.insert(3);

	multimap<string, string> dict;
	dict.insert(make_pair("left", "×ó±ß"));
	dict.insert(make_pair("left", "Ê£Óà"));
}