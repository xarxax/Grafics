#ifndef _MODELINFO_EXT_H
#define _MODELINFO_EXT_H

#include <vector>
#include "basicplugin.h"

using namespace std;

class Modelinfo : public QObject, public BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
   
 private:
 };
 
 #endif
 
 
