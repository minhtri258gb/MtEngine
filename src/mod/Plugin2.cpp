#define _MT_PLUGIN_2_CPP_
#define BUILD_DLL

#define PLUGIN_NAME "Test2:RandNum"
#define PLUGIN_AUTHOR "Massan"
#define PLUGIN_VERSION "0.1"

#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>
#include <assert.h>

#include "common.h"
#include "PluginBase.h"
#include "game/entities/Entity.h"

using namespace std;
using namespace mt::game;
using namespace mt::mod;

class Test2 : public PluginBase, public Entity {
public:

    // Variable

    // Forward
    void init()
    {
        cout << "constructor 2" << endl;
    }

    void close()
    {
        cout << "destructor 2" << endl;
    }

    void framework()
    {
    }

    void update()
    {
        cout << "update entity" << endl;
    }

    void render()
    {
        cout << "update render" << endl;
    }

    string getPluginName()
    {
        return PLUGIN_NAME;
    }

    string getPluginAuthor()
    {
        return PLUGIN_AUTHOR;
    }
    
    string getPluginVersion()
    {
        return PLUGIN_VERSION;
    }

    PLUGIN_TYPE getPluginType()
    {
        return PLUGIN_TYPE::ENTITY;
    }
    // void print(void) {
    //     cout << "This is Test2 Speaking!" << endl;
    // }

    // double calc(double val) {
    //     return val * this->_dist(this->_randGen);
    // }

private:
    // mt19937 _randGen {static_cast<unsigned>(time(nullptr))};
    // uniform_real_distribution<double> _dist {0.0, 100.0};
};

Test2* g_Plugin = NULL;

extern "C" DLLAPI PluginBase* CreatePlugin(void)
{
    assert(g_Plugin == NULL);
    g_Plugin = new Test2();
    return g_Plugin;
}

extern "C" DLLAPI void DestroyPlugin(void)
{
    assert(g_Plugin);
    delete g_Plugin;
    g_Plugin = NULL;
}

extern "C" DLLAPI BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
