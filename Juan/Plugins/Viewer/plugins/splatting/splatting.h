#ifndef _MULTITEX_H
#define _MULTITEX_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class Splatting : public QObject, public BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void preFrame();
    void postFrame();
    
 private:
    QGLShaderProgram* program;
    QGLShader* vs;
    QGLShader* fs; 
    GLuint textureId0, textureId1, textureId2;
 };
 
 #endif
