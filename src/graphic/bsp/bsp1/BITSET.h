//////////////////////////////////////////////////////////////////////////////////////////
//	BITSET.h
//	class declaration for set of bits to represent many true/falses
//	Downloaded from: www.paulsprojects.net
//	Created:	8th August 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef BITSET_H
#define BITSET_H

class BITSET
{
public:
	BITSET() : numBytes(0), bits(nullptr)
	{}
	~BITSET()
	{
		if(bits)
			delete [] bits;
		bits=nullptr;
	}

	bool Init(int numberOfBits);
	void ClearAll();
	void SetAll();

	void Clear(int bitNumber);
	void Set(int bitNumber);

	unsigned char IsSet(int bitNumber);

protected:
	int numBytes;	//size of bits array
	unsigned char * bits;
};

#endif