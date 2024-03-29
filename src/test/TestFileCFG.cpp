#define __MT_TEST_FILE_CFG_CPP__

#include <sstream>

#include "common.h"

#include "engine/file/FileCFG.h"

#include "TestFileCFG.h"

using namespace std;
using namespace mt;
using namespace mt::test;

void TestFileCFG::run()
{
	// Test CFG File
	FileCFG fCFG = FileCFG("./res/maps/test.cfg");

	// Load config

	// fCFG->select("terrain");
	// string name = fCFG->get("name");
	// int number = fCFG->getInt("number");
	// float floata = fCFG->getFloat("float");

	// fCFG->select("map");
	// bool aa = fCFG->getBool("where");
	// vec3 origin = fCFG->getVec3("origin");

	// cout << "str: " << name << endl;
	// cout << "int: " << number << endl;
	// cout << "float: " << floata << endl;
	// cout << "bool: " << aa << endl;
	// cout << "vec3: " << origin.x << " " << origin.y << " " << origin.z << endl;

	// Load entity
	fCFG.select("entities");
	vector<string> lstEntCfg = fCFG.values();
	for (short i=0, sz=lstEntCfg.size(); i<sz; i++)
	{
		string entCfg = lstEntCfg.at(i);
		stringstream geek(entCfg);

		string entType, entName;
		float x, y, z, angle, scale;
		geek >> entType >> entName >> x >> y >> z >> angle >> scale;
		vec3 pos = vec3(x, y, z);
		vec3 scale3 = vec3(scale, scale, scale);

		cout << entCfg << endl;
	}
}
