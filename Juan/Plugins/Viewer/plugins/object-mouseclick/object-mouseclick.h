#ifndef _DRAWBOUNDINGBOX_H  
#define _DRAWBOUNDINGBOX_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

class ObjectMouseClick : public QObject, BasicPlugin, QOpenGLFunctions_3_3_Core {

  Q_OBJECT
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  Q_INTERFACES(BasicPlugin)

  void createBuffers();
  void generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
  void drawBoxes();

  GLuint textureID;
  QOpenGLShaderProgram* programBox, *programColor;
  QOpenGLShader* vsBox, *vsColor;
  QOpenGLShader* fsBox, *fsColor;

  bool created;
  GLuint cubeVAO;
  GLuint verticesVBO;
  GLuint colorVBO;
  GLWidget *g;

  void setSelectedObject(int selected);
  void encodeID(int index, GLubyte *color);
  int decodeID(GLubyte *color);
  void drawColorScene();

public:
  void onPluginLoad();
  void postFrame();
  void mouseReleaseEvent(QMouseEvent* e);

};

#endif


