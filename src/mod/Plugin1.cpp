#define _MT_PLUGIN_1_CPP_
#define BUILD_DLL

#define PLUGIN_NAME "Test1:Maths"
#define PLUGIN_AUTHOR "Massan"
#define PLUGIN_VERSION "0.1"

#include <iostream>
#include <cmath>
#include <windows.h>
#include <assert.h>

#include "PluginBase.h"
#include "graphic/models/Model.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::mod;

class Test1 : public PluginBase, public Model {
public:

    // Variable

    // Forward
    void init()
    {
        cout << "constructor 1" << endl;
    }

    void close()
    {
        cout << "destructor 1" << endl;
    }

    void framework()
    {
    }

    void render()
    {
        cout << "OK render" << endl;
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
        return PLUGIN_TYPE::MODEL;
    }
};

Test1* g_Plugin = NULL;

extern "C" DLLAPI PluginBase* CreatePlugin(void)
{
    assert(g_Plugin == NULL);
    g_Plugin = new Test1();
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
