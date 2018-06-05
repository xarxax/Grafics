#include "framerate.h"
#include "glwidget.h"
#include <QPainter>

void Framerate::onPluginLoad()
{   
    glwidget()->makeCurrent();
  
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateFps()));
    timer->start(1000);
    
    fps = counter = 0;
}

void Framerate::postFrame()
{
    glwidget()->makeCurrent();
  
    ++counter;
    
    QPainter painter;
    painter.begin(glwidget());
    QFont font;
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor(50,50,50));
    int x = 15;
    int y = 50;
    QString screen_text = QString("framerate: ") + QString::number(fps);
    painter.drawText(x, y, screen_text);   
    painter.end();
}

void Framerate::updateFps()
{
    fps = counter;
    counter = 0;
}