#include "object-mouseclick.h"
#include "glwidget.h"
#include <iostream>

void ObjectMouseClick::setSelectedObject(int selected) {
  if (selected<0 || selected>=(int)scene()->objects().size()) selected=-1;
  scene()->setSelectedObject(selected);
  glwidget()->update();
}

void ObjectMouseClick::encodeID(int index, GLubyte *color) {
  color[0]=color[1]=color[2]=index;
}

// maxim 255 objectes. com que el valor de cada color va entre 0 i 255:
// 0-254 id objecte
// 255 cap objecte (el color de fons es blanc)
int ObjectMouseClick::decodeID(GLubyte *color) {
  if (color[0]==255) return -1;
  return color[0];
}

// Pintar l'escena assegurant-se que cada objecte es pinta amb un color únic 
// que permeti identificar l'objecte (i diferent del color de fons)
void ObjectMouseClick::drawColorScene() {
  // enviar la modelViewProjectionMatrix, i el color identificador dels objectes
  QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
  programColor->setUniformValue("modelViewProjectionMatrix", MVP);
  cout << "b" << endl;
  for (unsigned int i=0; i<scene()->objects().size(); ++i) {
    cout << "c" << endl;
    GLubyte color[4];
    cout << "d" << endl;
    encodeID(i, color);
    cout << "e" << endl;
    programColor->setUniformValue("color", QVector4D(color[0]/255., color[1]/255., color[2]/255., 1));
    cout << "f" << endl;
    cout << i << endl;
    BasicPlugin * dp = drawPlugin();
    cout <<  "drawPlugin() returns " << (void *) dp << endl;
    if (drawPlugin()) drawPlugin()->drawObject(i);
  }
}

void ObjectMouseClick::mouseReleaseEvent(QMouseEvent* e) {
  GLWidget &g = *glwidget();
  g.makeCurrent();
  if (!(e->button()&Qt::LeftButton)) return;          // boto esquerre del ratoli
  if (e->modifiers()&(Qt::ShiftModifier)) return;     // res de tenir shift pulsat
  if (!(e->modifiers()&Qt::ControlModifier)) return;  // la tecla control ha d'estar pulsada
  
  glClearColor(1, 1, 1, 1);                           // esborrar els buffers amb un color de fons únic (blanc)
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  cout << "Hola" << endl;
  programColor->bind();                               // activar (bind) el shader program amb el VS+FS d’abans
  cout << "a" << endl;
  drawColorScene();
  cout << "z" << endl;
  programColor->release();
  cout << "Chao" << endl;
  int x=e->x();                                       // llegir el color del buffer de color sota la posició del cursor
  int y=glwidget()->height()-e->y();
  GLubyte read[4];
  glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
  cout << "1" << endl;
  int seleccio=decodeID(&read[0]);                    // obtenir l'identificador de l'objecte corresponent i, 
  setSelectedObject(seleccio);                        // si no és color de fons, establir l'objecte seleccionat
  cout << "2" << endl;
  glwidget()->update();                             // cridar a updateGL per tal que es repinti l'escena
}

void ObjectMouseClick::onPluginLoad() {
  GLWidget &g = *glwidget();
  g.makeCurrent();
  initializeOpenGLFunctions();
  // Carregar shader, compile & link (capsa contenidora)
  vsBox=new QOpenGLShader(QOpenGLShader::Vertex, this);
  vsBox->compileSourceFile("plugins/object-mouseclick/object-mouseclick-box.vert");
  fsBox=new QOpenGLShader(QOpenGLShader::Fragment, this);
  fsBox->compileSourceFile("plugins/object-mouseclick/object-mouseclick-box.frag");
  programBox=new QOpenGLShaderProgram(this);
  programBox->addShader(vsBox);
  programBox->addShader(fsBox);
  programBox->link();
  // Carregar shader, compile & link (escena colors unics)
  vsColor=new QOpenGLShader(QOpenGLShader::Vertex, this);
  vsColor->compileSourceFile("plugins/object-mouseclick/object-mouseclick-color.vert");
  fsColor=new QOpenGLShader(QOpenGLShader::Fragment, this);
  fsColor->compileSourceFile("plugins/object-mouseclick/object-mouseclick-color.frag");
  programColor=new QOpenGLShaderProgram(this);
  programColor->addShader(vsColor);
  programColor->addShader(fsColor);
  programColor->link();
  created=false;
}

// rellena un vbo con los datos proporcionados:
// vbo_id = identificador del vbo
// size = número de elementos del array de datos
// data = array de datos
// attribute_id = identificador del atributo correspondiente del shader
// attribute_size = número de elementos que componen el atributo (ie. 3 para vértices)
// Se asume que los datos del array serán de tipo float
void ObjectMouseClick::generate_vbo(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size) {
  g->glGenBuffers(1, &vbo_id);
  g->glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  g->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
  g->glVertexAttribPointer(attribute_id, attribute_size, GL_FLOAT, GL_FALSE, 0, 0);
  g->glEnableVertexAttribArray(attribute_id);
}

void ObjectMouseClick::createBuffers() {
  // dades
  GLfloat cube_vertices[]={
    1, 1, 1,
    0, 1, 1,
    1, 0, 1,
    0, 0, 1,
    1, 0, 0,
    0, 0, 0,
    1, 1, 0,
    0, 1, 0,
    1, 1, 1,
    0, 1, 1,
    0, 1, 1,
    0, 1, 0,
    0, 0, 1,
    0, 0, 0,
    1, 0, 1,
    1, 0, 0,
    1, 1, 1,
    1, 1, 0
  };
  GLfloat cube_colors[]={
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0
  };
  // VAO Capsa
  g->glGenVertexArrays(1, &cubeVAO);
  g->glBindVertexArray(cubeVAO);
  // VBOs Capsa
  generate_vbo(verticesVBO, 18*3, &cube_vertices[0], 0, 3);
  generate_vbo(colorVBO, 18*3, &cube_colors[0], 2, 3);
}

void ObjectMouseClick::drawBoxes() {
  int selected = scene()->selectedObject();
  cout << selected << endl;
  if (selected >= 0 && selected<(int)scene()->objects().size()) {
    // crear buffers
    if (!created) {
      created=true;
      createBuffers();
    }
    
    // establir modelViewProjection
    QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
    programBox->setUniformValue("modelViewProjectionMatrix", MVP);
    
    Object &obj=scene()->objects()[selected];
    
    // pintar la capsa contenidora de tots els objectes de l'escena
    programBox->setUniformValue("boundingBoxMin",obj.boundingBox().min());
    programBox->setUniformValue("boundingBoxMax",obj.boundingBox().max());
    g->glBindVertexArray(cubeVAO);
    g->glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);
    g->glBindVertexArray(0);
  }
}

void ObjectMouseClick::postFrame() { 
  g = glwidget();
  g->makeCurrent(),
  programBox->bind();
  GLint polygonMode;                              // en que polygon mode estamos? (GL_LINE, GL_FILL, GL_POINTS)
  g->glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
  g->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // pinta el wireframe
  drawBoxes();                                    // de las cajas contenedoras de todos los objetos de la escena
  g->glPolygonMode(GL_FRONT_AND_BACK, polygonMode);  // reestablecer el poygon mode anterior
  programBox->release();
}

