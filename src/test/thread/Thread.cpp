#define __MT_THREAD_CPP__

#include <iostream>
#include <thread>

#include "common.h"
#include "Thread.h"

using namespace std;
using namespace mt::test;

class baa
{
public:

    // Operator
    void operator () (int params) {
        cout << "do somthing\n";
    }

};

void Thread::run()
{
    cout<<"0"<<endl;
	thread thread_obj(baa(), 12);
    cout<<"2"<<endl;
    // thread_obj.join();
    // thread_obj2.join();
    while(1) {}
}
