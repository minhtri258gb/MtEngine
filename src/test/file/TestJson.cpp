#define __MT_TEST_JSON_CPP__

#include <iostream>

#include "common.h"
#include "TestJson.h"
#include "FileJson.h"

using namespace std;
using namespace mt::test;


TestJson::TestJson()
{

}

TestJson::~TestJson()
{

}

void TestJson::run()
{
    FileJson file("../res/test/file.json");


    
	cout << "Test Done" << endl;
}
