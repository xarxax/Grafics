#ifndef _FRAMERATE_EXT_H
#define _FRAMERATE_EXT_H

#include "basicplugin.h"

class Framerate : public QObject, BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void postFrame() Q_DECL_OVERRIDE;
   
 public slots:
    void updateFps();
    
 private:
    int fps;
    int counter;
    QTimer *timer;
 };
 
#endif