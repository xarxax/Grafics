#ifndef _MOTION_BLUR_H
#define _MOTION_BLUR_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>


class MotionBlur : public QObject, public BasicPlugin, public QOpenGLFunctions_3_3_Core
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)


 public:
    void onPluginLoad();
    bool paintGL();
 
 private:
    void drawRect();
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureIdCur, textureIdPrev;
 };
 
 #endif
