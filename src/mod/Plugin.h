#ifndef __MT_PLUGIN_H__
#define __MT_PLUGIN_H__

#include "PluginBase.h"

namespace mt {
namespace mod {

class PluginImpl;

class Plugin {
public:

    // Forwards
    Plugin();
    ~Plugin();
    void load(std::string pluginname);
    void close();

    // Natives
    PluginBase* getObject();

private:

    // Variable
    PluginImpl* impl;

};

}}

#endif
