#include "draw-flat.h"
#include "glwidget.h"
#include <cmath>

void DrawSmooth::cleanUp() {
  g->glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
  g->glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
  g->glDeleteBuffers(indexBuffers.size(),  &indexBuffers[0]);
  g->glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
  g->glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);

  g->glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
  
  coordBuffers.clear();
  normalBuffers.clear();
  indexBuffers.clear();
  stBuffers.clear();
  colorBuffers.clear();
  VAOs.clear();

  numIndices.clear(); 
}

DrawSmooth::~DrawSmooth() {
  cleanUp();
}

void DrawSmooth::onSceneClear() {
  cleanUp();
}

bool DrawSmooth::drawObject(int i) {
  g->glBindVertexArray(VAOs[i]);
  g->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
  g->glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);

  g->glBindVertexArray(0);
  g->glBindBuffer(GL_ARRAY_BUFFER,0);
  g->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  return true;
}

bool DrawSmooth::drawScene() {
  g = glwidget();
  g->makeCurrent();
  for (unsigned int i=0; i<coordBuffers.size(); ++i)  {   // for each buffer (that is, for each object)
    g->glBindVertexArray(VAOs[i]);
    g->glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);
  }
  g->glBindVertexArray(0);
  return true;
}

void DrawSmooth::onPluginLoad() {
  g = glwidget();
  g->makeCurrent();
  for(unsigned int i=0; i<scene()->objects().size(); ++i) addVBO(i);
}

void DrawSmooth::onObjectAdd() {
  addVBO(scene()->objects().size()-1);
}

void DrawSmooth::addVBO(unsigned int currentObject) {  
  // Step 1: Create and fill the four arrays (vertex coords, vertex normals, and face indices) 
  // This version: 
  //  - each coord/normal will appear n times (one for each corner with unique normal)
  //  - non-triangular faces (convexity is assumed) are triangulated on-the-fly: (v0,v1,v2,v3) -> (v0,v1,v2) (v0,v2,v3)
  vector<float> vertices; // (x,y,z)    Final size: 3*number of corners
  vector<float> normals;  // (nx,ny,nz) Final size: 3*number of corners
  vector<float> st;       // (s,t)      Final size: 2*number of corners  
  vector<float> colors;   // (r,g,b)    Final size: 3*number of corners
  vector<int> indices;    //            Final size: 3*number of triangles  
  
    // V'=3T. En aquest cas, per cada triangle, donem els seus tres vèrtexs. 
  // Això fa que un mateix vèrtex (x,y,z) aparegui múltiples cops al VBO: 
  // hi serà tantes vegades com triangles hi incideixen.
  const Object& obj = scene()->objects()[currentObject];
  const vector<Vertex> &verts=obj.vertices();
  const vector<Face> &faces=obj.faces();
  int index=0;
  for (int i=0; i<(int)faces.size(); ++i) {
    const Face &face=faces[i];
    Vector N=face.normal().normalized();
    for (int j=0; j<(int)face.numVertices(); ++j) {
      const Point &P=verts[face.vertexIndex(j)].coord();
      vertices.push_back(P.x()); vertices.push_back(P.y()); vertices.push_back(P.z());
      normals.push_back(N.x()); normals.push_back(N.y()); normals.push_back(N.z());
      float r=obj.boundingBox().radius();
      float s=Vector::dotProduct((1.0/r)*Vector(1,0,1), P);
      float t=Vector::dotProduct((1.0/r)*Vector(0,1,0), P);
      if ((int)verts.size()==81) {    // plane: special case for /assig models
        s=0.5f*(P.x()+1.0);
        t=0.5f*(P.y()+1.0);
      }
      if ((int)verts.size()==386) {   // cube: special case for /assig models
        s=Vector::dotProduct((1.0/2.0)*Vector(1,0,1), P);
        t=Vector::dotProduct((1.0/2.0)*Vector(0,1,0), P);
      }
      st.push_back(s);
      st.push_back(t);
      colors.push_back(abs(N.x()));
      colors.push_back(abs(N.y()));
      colors.push_back(abs(N.z()));
      indices.push_back(index);       // els index van de [0..V')
      ++index;
    }
  }

  // Step 2: Create empty buffers (coords, normals, st, indices)
  GLuint VAO;
  g->glGenVertexArrays(1, &VAO);
  VAOs.push_back(VAO);
  g->glBindVertexArray(VAO);

  GLuint coordBufferID;
  g->glGenBuffers(1, &coordBufferID);
  coordBuffers.push_back(coordBufferID);

  GLuint normalBufferID;
  g->glGenBuffers(1, &normalBufferID);
  normalBuffers.push_back(normalBufferID);

  GLuint colorBufferID;
  g->glGenBuffers(1, &colorBufferID);
  colorBuffers.push_back(colorBufferID);

  GLuint stBufferID;
  g->glGenBuffers(1, &stBufferID);
  stBuffers.push_back(stBufferID);

  GLuint indexBufferID;
  g->glGenBuffers(1, &indexBufferID);
  indexBuffers.push_back(indexBufferID);

  numIndices.push_back(indices.size());

  // Step 3: Define VBO data (coords, normals, indices)
  g->glBindBuffer(GL_ARRAY_BUFFER, coordBuffers[currentObject]);
  g->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
  g->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
  g->glEnableVertexAttribArray(0);

  g->glBindBuffer(GL_ARRAY_BUFFER, normalBuffers[currentObject]);
  g->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
  g->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
  g->glEnableVertexAttribArray(1);

  g->glBindBuffer(GL_ARRAY_BUFFER, colorBuffers[currentObject]);
  g->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
  g->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
  g->glEnableVertexAttribArray(2);

  g->glBindBuffer(GL_ARRAY_BUFFER, stBuffers[currentObject]);
  g->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*st.size(), &st[0], GL_STATIC_DRAW);
  g->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
  g->glEnableVertexAttribArray(3);

  g->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[currentObject]);
  g->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

  g->glBindVertexArray(0);
  g->glBindBuffer(GL_ARRAY_BUFFER,0);
  g->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}


