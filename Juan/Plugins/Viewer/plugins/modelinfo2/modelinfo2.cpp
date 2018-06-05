#include "modelinfo2.h"
#include "glwidget.h"
#include <QPainter>

void Modelinfo2::postFrame()
{
    glwidget()->makeCurrent();
  
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
    
    QPainter painter;
    painter.begin(glwidget());
    QFont font;
    font.setPixelSize(16);
    painter.setFont(font);
    painter.setPen(QColor(50,50,50));
    int x = 15;
    int y = 50;
    QString screen_text = QString("objects: ") + QString::number(objs);
    painter.drawText(x, y, screen_text);
    screen_text = QString("vertices: ") + QString::number(verts);
    painter.drawText(x, y+=20, screen_text);
    screen_text = QString("faces: ") + QString::number(faces);
    painter.drawText(x, y+=20, screen_text);
    screen_text = QString("triangles: ") + QString::number(tris);
    painter.drawText(x, y+=20, screen_text);
    screen_text = QString("triangle %: ") + QString::number(triperc) + QString("%");
    painter.drawText(x, y+=20, screen_text);

    painter.end();
}