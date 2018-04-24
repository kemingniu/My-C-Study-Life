#pragma once

#include <vector>

class BitMap
{
public:
	BitMap(size_t range)
	{
		_bits.resize((range>>3) + 1, 0);
	}

	void Set(size_t x)
	{
		//size_t index = x/8;
		size_t index = (x>>3);
		size_t num = x%8;

		_bits[index] |= (1<<num);
	}

	void Reset(size_t x)
	{
		size_t index = (x>>3);
		size_t num = x%8;

		_bits[index] &= (~(1<<num));
	}

	bool Test(size_t x)
	{
		size_t index = (x>>3);
		size_t num = x%8;

		return _bits[index] & (1<<num);
	}

protected:
	vector<char> _bits;
	//vector<int> _bits;
};

void TestBitMap()
{
	//BitMap bm(100);

	//bm.Set(2);
	//bm.Set(16);

	//cout<<bm.Test(2)<<endl;
	//cout<<bm.Test(16)<<endl;

	//bm.Reset(2);
	//bm.Reset(16);

	//cout<<bm.Test(2)<<endl;
	//cout<<bm.Test(16)<<endl;
	//cout<<bm.Test(17)<<endl;
	//cout<<bm.Test(7)<<endl;

	BitMap bm(0xffffffff);
}