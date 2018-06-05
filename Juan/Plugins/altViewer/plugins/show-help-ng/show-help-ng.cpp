#include "show-help-ng.h"
#include "glwidget.h"
#include <QPainter>

void ShowHelpNg::postFrame() 
{
  QPainter painter;
  painter.begin(glwidget());
  QFont font;
  font.setPixelSize(32);
  painter.setFont(font);
  painter.setPen(QColor(50,50,50));
  int x = 15;
  int y = 50;
  painter.drawText(x, y, QString("L - Load object     A - Add plugin"));    
  painter.end();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(show-help-ng, ShowHelpNg)   // plugin name, plugin class
#endif
