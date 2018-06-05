#include "modelinfo.h"
#include "glwidget.h"
#include <iostream>

using namespace std;

void Modelinfo::onPluginLoad()
{
    Scene* scn = scene();
    // per cada objecte
    int objs = 0, verts = 0, faces = 0, tris = 0;
    double triperc;
    objs = scn->objects().size();
    for (unsigned int i=0; i<scn->objects().size(); ++i)    
    {
        const Object& obj = scn->objects()[i];
        // per cada cara
	faces += obj.faces().size();
	verts += obj.vertices().size();
        for(unsigned int c=0; c<obj.faces().size(); c++)
        {
            const Face& face = obj.faces()[c];
            // per cada vertex
	    if (face.numVertices() == 3) tris += 1;
        }
    }
    triperc = ((double)tris/(double)faces)*100;
    cout << "objects: " << objs << " vertices: " << verts << " faces: " << faces << " triangles: " << tris << " triangle percentage: " << triperc << "%" << endl;
}