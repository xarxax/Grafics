#include "animated-vertices.h"


void AnimatedVertices::onPluginLoad() {
    QString vs_src =
        "#version 330 core\n"
        "layout (location = 0) in vec3 vertex;"
        "layout (location = 1) in vec3 normal;"
        "layout (location = 2) in vec3 color;"
        "layout (location = 3) in vec2 texCoord;"
        "out vec4 frontColor;"
        "out vec2 vtexCoord;"
        "uniform mat4 modelViewProjectionMatrix;"
        "uniform mat3 normalMatrix;"
        "uniform float time;"
        "uniform float amplitude=0.1;"
        "uniform float freq = 1;"
        "const float PI = 3.141592;"
        "void main(){"
        "   vec3 N = normalize(normalMatrix * normal);"
        "   frontColor = vec4(N.z);"
        "   vtexCoord = texCoord;"
        "   vec3 d = normal * amplitude*(sin(2*PI*freq*time));"
        "   vec3 animated_vertex = vertex + d;"
        "   gl_Position = modelViewProjectionMatrix * vec4(animated_vertex, 1.0);"
        "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    
    QString fs_src = 
        "#version 330 core\n"
        "in vec4 frontColor;"
        "in vec2 vtexCoord;"
        "out vec4 fragColor;"
        "void main(){"
        "   fragColor = frontColor;"
        "}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    
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
