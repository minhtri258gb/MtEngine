#define __MT_TEST_CPP__

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "Test.h"
#include "file/TestJson.h"
#include "audio/Audio.h"
#include "technique/TestTechnique.h"
#include "thread/Thread.h"
#include "engine/file/FileCFG.h"

using namespace std;
using namespace mt;
using namespace mt::test;

void Test::run()
{

	// ===============================================================================================
	// Test CFG File
	FileCFG* fCFG = new FileCFG("../res/terrains/static/hm1/info.cfg");
	string name = fCFG->get("name");
	cout << "cout: " << name << endl;
	delete fCFG;
	// ===============================================================================================

	// TestJson test; // faild hien loi nhung build duoc
	// TestTechnique test;
	// Thread test;

	// test.run();

	// ===============================================================================================

	// vec3 a(1,1,1);
	// vec3 b(10,10,10);
	// vec3 c = a.mix(b, 0.5f);
	// cout << a.x << ' ' << a.y << ' ' << a.z << endl;
	// cout << b.x << ' ' << b.y << ' ' << b.z << endl;
	// cout << c.x << ' ' << c.y << ' ' << c.z << endl;

	// ===============================================================================================
	// float width = 1920.0f;
	// float height = 1080.0f;

	// glm::mat4 ma = glm::mat4(1.0f);
	// // glm::mat4 ma = glm::mat4(5,0,0,0,0,0,3,0,0,1,3,0,1,0,0,1);
	// ma = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	// cout << ma[0][0] << '\t' << ma[0][1] << '\t' << ma[0][2] << '\t' << ma[0][3] << '\t' << endl;
	// cout << ma[1][0] << '\t' << ma[1][1] << '\t' << ma[1][2] << '\t' << ma[1][3] << '\t' << endl;
	// cout << ma[2][0] << '\t' << ma[2][1] << '\t' << ma[2][2] << '\t' << ma[2][3] << '\t' << endl;
	// cout << ma[3][0] << '\t' << ma[3][1] << '\t' << ma[3][2] << '\t' << ma[3][3] << '\t' << endl;
	// cout << "============================\n";

	// // mat4 mb(5,0,0,0,0,0,3,0,0,1,3,0,1,0,0,1);
	// mat4 mb;
	// mb.ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	// cout << mb[ 0] << '\t' << mb[ 1] << '\t' << mb[ 2] << '\t' << mb[ 3] << '\t' << endl;
	// cout << mb[ 4] << '\t' << mb[ 5] << '\t' << mb[ 6] << '\t' << mb[ 7] << '\t' << endl;
	// cout << mb[ 8] << '\t' << mb[ 9] << '\t' << mb[10] << '\t' << mb[11] << '\t' << endl;
	// cout << mb[12] << '\t' << mb[13] << '\t' << mb[14] << '\t' << mb[15] << '\t' << endl;


	// ===============================================================================================
	// vec3 a1(1,2,3);
	// vec3 b1(7,8,9);
	// vec3 c1 = a1 ^ b1;
	// float d1 = a1 * b1;

	// glm::vec3 a2(1,2,3);
	// glm::vec3 b2(7,8,9);
	// glm::vec3 c2 = glm::cross(a2,b2);
	// float d2 = glm::dot(a2,b2);

	// cout << "c1 = " << c1.x << ' ' << c1.y << ' ' << c1.z << endl;
	// cout << "d1 = " << d1 << endl;
	// cout << "c2 = " << c2.x << ' ' << c2.y << ' ' << c2.z << endl;
	// cout << "d2 = " << d2 << endl;


	// ===============================================================================================
	// glm::vec3 posg(1,3,5);
	// glm::vec3 forg(11,22,33);
	// glm::mat4 ma = glm::lookAt(posg, forg, glm::vec3(0,1,0));
	// cout << ma[0][0] << '\t' << ma[0][1] << '\t' << ma[0][2] << '\t' << ma[0][3] << '\t' << endl;
	// cout << ma[1][0] << '\t' << ma[1][1] << '\t' << ma[1][2] << '\t' << ma[1][3] << '\t' << endl;
	// cout << ma[2][0] << '\t' << ma[2][1] << '\t' << ma[2][2] << '\t' << ma[2][3] << '\t' << endl;
	// cout << ma[3][0] << '\t' << ma[3][1] << '\t' << ma[3][2] << '\t' << ma[3][3] << '\t' << endl;
	// cout << "1 ============================\n";

	
	// vec3 posm(1,3,5);
	// vec3 form(11,22,33);
	// mat4 mb;
	// mb.lookAt(posm, form, vec3(0,1,0));
	// cout << mb[ 0] << '\t' << mb[ 1] << '\t' << mb[ 2] << '\t' << mb[ 3] << '\t' << endl;
	// cout << mb[ 4] << '\t' << mb[ 5] << '\t' << mb[ 6] << '\t' << mb[ 7] << '\t' << endl;
	// cout << mb[ 8] << '\t' << mb[ 9] << '\t' << mb[10] << '\t' << mb[11] << '\t' << endl;
	// cout << mb[12] << '\t' << mb[13] << '\t' << mb[14] << '\t' << mb[15] << '\t' << endl;
	// cout << "2 ============================\n\n";

	// ===============================================================================================

	// mt::mat4 a(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
	// mt::mat4 b(32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17);
	// mt::mat4 mb = a * b;
	
	// float dd[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	// float ee[16] = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17};
	// mt2::mat4 d(dd);
	// mt2::mat4 e(ee);
	// mt2::mat4 ma = d * e;


	// cout << mb[ 0] << '\t' << mb[ 1] << '\t' << mb[ 2] << '\t' << mb[ 3] << '\t' << endl;
	// cout << mb[ 4] << '\t' << mb[ 5] << '\t' << mb[ 6] << '\t' << mb[ 7] << '\t' << endl;
	// cout << mb[ 8] << '\t' << mb[ 9] << '\t' << mb[10] << '\t' << mb[11] << '\t' << endl;
	// cout << mb[12] << '\t' << mb[13] << '\t' << mb[14] << '\t' << mb[15] << '\t' << endl;
	// cout << "===============\n";
	
	// cout << ma[ 0] << '\t' << ma[ 1] << '\t' << ma[ 2] << '\t' << ma[ 3] << '\t' << endl;
	// cout << ma[ 4] << '\t' << ma[ 5] << '\t' << ma[ 6] << '\t' << ma[ 7] << '\t' << endl;
	// cout << ma[ 8] << '\t' << ma[ 9] << '\t' << ma[10] << '\t' << ma[11] << '\t' << endl;
	// cout << ma[12] << '\t' << ma[13] << '\t' << ma[14] << '\t' << ma[15] << '\t' << endl;
}
