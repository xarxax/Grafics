#ifndef _SHOWHELPNG_H
#define _SHOWHELPNG_H

#include "basicplugin.h"

class ShowHelpNg : public QObject, BasicPlugin
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
