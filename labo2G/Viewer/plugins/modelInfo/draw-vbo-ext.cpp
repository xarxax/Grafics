#include "draw-vbo-ext.h"
#include "glwidget.h"
#include <cstdio>

// número total d’objectes carregats,
// número total de polígons,
// número total de vèrtexs,
// i el percentatge de polígons que són triangles

float square(float x){
    return x*x;
}
void ModelInfo::printModelInfo() {
  // do count
  Scene* scn=scene();
  float area=0;
  for (int i=0; i<(int)scn->objects().size(); ++i) {
    const Object &obj=scn->objects()[i];
    //we know #poligons
    for (int j=0; j<(int)obj.faces().size(); ++j) {
      const Face &face=obj.faces()[j];
      float xlen = distance(face.vertex[1],face.vertexIndex[1]);
      float ylen = distance(face.vertexIndex(2),face.vertexIndex(0));

      area += xlen *ylen/2 ;

    }
  }
  // print model info
  printf("Area: %f\n", area);
}

void ModelInfo::onPluginLoad() {
  printModelInfo();
}

void ModelInfo::onObjectAdd() {
  printModelInfo();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(model-info, ModelInfo)   // plugin name, plugin class
#endif

