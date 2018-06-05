#ifndef _ANIMATEDVERTICES_H  
#define _ANIMATEDVERTICES_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>

class AnimatedVertices : public QObject, public BasicPlugin{
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
    QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs;
    QElapsedTimer elapsedTimer;
};
 
#endif
