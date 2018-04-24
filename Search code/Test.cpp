#include <iostream>
#include <assert.h>
using namespace std;

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "RBTree.h"

#include "set_map.h"
#include "MySet.h"
#include "MyMap.h"

#include "HashTable.h"
#include "MyUnOrderedSet.h"
#include "MyUnOrderedMap.h"
#include "OP.h"

#include "BitMap.h"
#include "BloomFilter.h"


int main()
{
	/*TestBSTree();
	cout<<"======================================"<<endl;
	TestBSTreeR();*/

	//TestAVLTree();
	//TestRBTree();
	//TestSet();
	//TestMap();

	//test_set();
	//test_map();

	//HASH_BUCKET::TestHashTable();
	//TestUnOrderSet();
	//TestUnOrderedMap();
	//TestOP();

	//TestBitMap();

	TestBloomFilter();

	return 0;
}