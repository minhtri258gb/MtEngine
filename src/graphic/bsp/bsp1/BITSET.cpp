//////////////////////////////////////////////////////////////////////////////////////////
//	BITSET.cpp
//	functions for class for set of bits to represent many true/falses
//	Downloaded from: www.paulsprojects.net
//	Created:	8th August 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////
#include "memory.h"
// #include "LOG.h"
#include "BITSET.h"

// extern LOG errorLog;

bool BITSET::Init(int numberOfBits)
{
	//Delete any memory allocated to bits
	if (bits)
		delete [] bits;
	bits=nullptr;

	//Calculate size
	numBytes=(numberOfBits>>3)+1;

	//Create memory
	bits=new unsigned char[numBytes];
	if (!bits)
	{
		// errorLog.OutputError("Unable to allocate space for a bitset of %d bits", numberOfBits);
		return false;
	}

	ClearAll();

	return true;
}

void BITSET::ClearAll()
{
	memset(bits, 0, numBytes);
}

void BITSET::SetAll()
{
	memset(bits, 0xFF, numBytes);
}

void BITSET::Clear(int bitNumber)
{
	bits[bitNumber>>3] &= ~(1<<(bitNumber & 7));
}

void BITSET::Set(int bitNumber)
{
	bits[bitNumber>>3] |= 1<<(bitNumber&7);
}

unsigned char BITSET::IsSet(int bitNumber)
{
	return bits[bitNumber>>3] & 1<<(bitNumber&7);
}
