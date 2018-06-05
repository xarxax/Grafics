#include <QApplication>
#include "glwidget.h"
#include <string>
using namespace std;

int main(int argc, char ** argv)
{
    QApplication a(argc, argv);

    // Specify an OpenGL 3.3 format using the appropriate profile.
    QSurfaceFormat glFormat;
    //glFormat.setVersion( 3, 3);  // Should not be needed... In fact,
                                   // breaks show-help-ng!!
    char* tmp = getenv ("VPROFILE");
    glFormat.setProfile( QSurfaceFormat::CoreProfile); 
    if (tmp!=NULL) 
    {
        if (QString(tmp)!=QString("CORE"))
            glFormat.setProfile( QSurfaceFormat::CompatibilityProfile ); 
    }
    QSurfaceFormat::setDefaultFormat(glFormat);
    // Used to pass command line args to the plugins
    string args;
    for (int i=1; i<argc; ++i) args+=argv[i];
    
    // Create OpenGL window
    GLWidget glWidget(args);
    glWidget.show();

    // Print OpenGL version and profile 
    QSurfaceFormat f = glWidget.format();
    cout << "OpenGL Version: " << f.majorVersion() << "." << f.minorVersion() << endl;
    cout << "OpenGL Profile: " << ((f.profile()==QSurfaceFormat::CoreProfile)?"Core":"Compatibility") << endl;

    // Plugin path
    QString pluginPath;
    tmp = getenv ("VPLUGINPATH");
    if (tmp!=NULL) pluginPath=QString(tmp);
    else
    {
        pluginPath = a.applicationDirPath();
        #if defined(__APPLE__)
        pluginPath.append("/../../../");
        #else
        pluginPath.append("/");
        # endif
        pluginPath.append("../../plugins/bin/");
    }
    glWidget.setPluginPath(pluginPath);

    // Load default plugins
    QString plugins = QString(getenv ("VPLUGINS"));
    glWidget.loadDefaultPlugins(plugins);

    // Load default object
    QString models = "/assig/grau-g/models";
    tmp = getenv ("VMODELS");
    if (tmp!=NULL) models=QString(tmp);
    glWidget.addObjectFromFile(models + "/default.obj");

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}

