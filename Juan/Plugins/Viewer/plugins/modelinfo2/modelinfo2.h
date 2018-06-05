#ifndef _MODELINFO2_EXT_H
#define _MODELINFO2_EXT_H

#include "basicplugin.h"

class Modelinfo2 : public QObject, BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)

 public:
    void postFrame() Q_DECL_OVERRIDE;
 };
 
 #endif
