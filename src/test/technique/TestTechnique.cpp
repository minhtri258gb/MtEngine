#define __MT_TEST_TECHNIQUE_CPP__

#include <iostream>

#include "common.h"
#include "TestTechnique.h"

using namespace std;
using namespace mt::test;

void TestTechnique::run()
{
	// this->remove_element_vector();
	this->time();
}

void TestTechnique::remove_element_vector()
{
	// vector<int> lstObj;
	// lstObj.push_back(1);
	// lstObj.push_back(5);
	// lstObj.push_back(2);
	// lstObj.push_back(8);
	// lstObj.push_back(7);
	// lstObj.push_back(12);

	// bool isEven(int k) {
	// 	return ((i%2) == 0);
	// };

	// lstObj.remove_if(vector.begin(), vector.end(), isEven);

	// // vector<vector<int>::iterator> lstIt;
	
	// for (vector<int>::iterator it = lstObj.begin(), itEnd = lstObj.end(); it != itEnd; it++)
	// {
	// 	if ((*it) % 2 == 0)
	// 	{
	// 		lstObj.erase(it);
	// 		// lstIt.push_back(it);
	// 	}
	// }

	// // for (vector<int>::iterator it : lstIt)
	// // {
	// // 	lstObj.erase(it);
	// // }

	// for (int n : lstObj)
	// 	cout << n << endl;
}



#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void TestTechnique::time()
{
	while (1)
	{
		cout << clock() << endl;
	}
}
