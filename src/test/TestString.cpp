#define __MT_TEST_STRING_CPP__

#include <iostream>

#include "common.h"
#include "TestString.h"

using namespace std;
using namespace mt::test;


void plus_str()
{
	for (int i=0; i<25; i++)
		cout << string("F") + to_string(i) << endl;
}

void TestString::run()
{
	plus_str();
}
