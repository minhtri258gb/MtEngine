#define _MT_PLUGIN_3_CPP_
#define BUILD_DLL

#define PLUGIN_NAME "Test3:Filesize"
#define PLUGIN_AUTHOR "Massan"
#define PLUGIN_VERSION "0.1"

#include <iostream>
#include <windows.h>
#include <assert.h>
#include "PluginBase.h"

using namespace std;
using namespace mt::mod;

class Test3 : public PluginBase {
public:

    // Variable

    // Forward
    void init()
    {
        cout << "constructor 3" << endl;
    }

    void close()
    {
        cout << "destructor 3" << endl;
    }

    void framework()
    {
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
        return PLUGIN_TYPE::PROCESS;
    }

    // void print(void) {
    //     // Print a whole bunch of strange characters onto the screen
    //     cout << "\"\3\4\5\6\3\4\5\6\3\4\5\6\3\4\5\6\"" << endl;
    // }

    // double calc(double val) {
    //     // Calculate the size of itself
    //     WIN32_FIND_DATAA data;
    //     FindFirstFileA(R"(.\plugins\test3.dll)", &data);
    //     return (data.nFileSizeHigh * (MAXDWORD + 1)) + data.nFileSizeLow;
    // }
};

Test3* g_Plugin = NULL;

extern "C" DLLAPI PluginBase* CreatePlugin(void)
{
    assert(g_Plugin == NULL);
    g_Plugin = new Test3();
    return g_Plugin;
}

extern "C" DLLAPI void DestroyPlugin(void)
{
    assert(g_Plugin);
    delete g_Plugin;
    g_Plugin = NULL;
}

extern "C" DLLAPI BOOL APIENTRY DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) {
    switch (reason) {
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
