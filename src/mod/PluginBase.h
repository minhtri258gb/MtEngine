#ifndef __MT_PLUGIN_BASE_H__
#define __MT_PLUGIN_BASE_H__

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

namespace mt {
namespace mod {

class PluginBase {
public:

    // Datatype
    enum PLUGIN_TYPE
    {
        PROCESS = 0,
        MODEL,
        ENTITY,
        MAP
    };

    // Forwards
    virtual ~PluginBase() = default;
    virtual void init(void) = 0;
    virtual void close(void) = 0;
    virtual void framework(void) = 0;

    // Natives
    virtual std::string getPluginName(void) = 0;
    virtual std::string getPluginAuthor(void) = 0;
    virtual std::string getPluginVersion(void) = 0;
    virtual PLUGIN_TYPE getPluginType(void) = 0;

};

extern "C" DLLAPI PluginBase* CreatePlugin(void);
extern "C" DLLAPI void DestroyPlugin(void);

}}

#endif
