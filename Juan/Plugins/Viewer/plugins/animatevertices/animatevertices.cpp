#include "animatevertices.h"
#include <iostream>
#include <cstdlib>
#include <camera.h>

void Animatevertices::onPluginLoad()
{
    glwidget()->makeCurrent();
    //connect(&timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
    timer.start();
    elapsedTimer.start();
    
    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(QString("plugins/animatevertices/animate-vertices-1.vert"));
    //cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(QString("plugins/animatevertices/animate-vertices-1.frag"));
    //cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    //cout << "Link log:" << program->log().toStdString() << endl;
}

void Animatevertices::preFrame()
{
    glwidget()->makeCurrent();
    // bind shader and define uniforms
    // transpose((inv(3x3 model*view)))
    program->bind();
    float t;
    t = (float)elapsedTimer.elapsed();
    program->setUniformValue("time", t/1000);
    QMatrix3x3 NM = camera()->viewMatrix().normalMatrix();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("normalMatrix", NM);
}

void Animatevertices::postFrame()
{
    glwidget()->makeCurrent();
    // unbind shader
    program->release();
}