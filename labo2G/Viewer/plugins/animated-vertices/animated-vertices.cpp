#include "animated-vertices.h"


void AnimatedVertices::onPluginLoad() {
   // QString vs_src =;
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("/home2/users/alumnes/1181909/dades/training/Viewer/plugins/animated-vertices/animate-vertices-1.vert");
    
    //QString fs_src = ;
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("/home2/users/alumnes/1181909/dades/training/Viewer/plugins/animated-vertices/animate-vertices-1.frag");
    
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    elapsedTimer.start();
    // keep repainting
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
    timer->start();
    
}

void AnimatedVertices::preFrame() {
    //bin shader and define uniforms
    program->bind();
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));
    QMatrix3x3 NM=camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", NM); 
    QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
}

void AnimatedVertices::postFrame(){
    // unbind shader
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(animated-vertices, AnimatedVertices)  // plugin name, plugin class
#endif
