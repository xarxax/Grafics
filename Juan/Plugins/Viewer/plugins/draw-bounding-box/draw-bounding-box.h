#ifndef _DRAWBOUNDINGBOX_H  
#define _DRAWBOUNDINGBOX_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class DrawBoundingBox : public QObject, BasicPlugin {

  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)

  void createBuffers();
  void generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
  void drawBoxes();

  GLuint textureID;
  QOpenGLShaderProgram* program;
  QOpenGLShader* vs;
  QOpenGLShader* fs;

  bool created;
  GLuint cubeVAO;
  GLuint verticesVBO;
  GLuint colorVBO;
  GLWidget *g;

public:
  void onPluginLoad();
  void postFrame();

};

#endif


