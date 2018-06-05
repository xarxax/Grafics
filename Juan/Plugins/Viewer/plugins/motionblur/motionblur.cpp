#include "motionblur.h"

const int IMAGE_SIZE = 512;

void MotionBlur::onPluginLoad()
{
    GLWidget &g = *glwidget();	
    g.makeCurrent();
    initializeOpenGLFunctions();

    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    QString vsCode = 	"#version 330 core\n"
			"in vec3 vertex;"
			"void main(){"
			" gl_Position    = vec4(vertex,1.0);}";
    vs->compileSourceCode(vsCode);
    cout << "VS log:" << vs->log().toStdString() << endl;


    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    QString fsCode =    "#version 330 core\n"
			"out vec4 fragColor;"
			"uniform sampler2D colorMap;"
			"uniform float SIZE = 512;"
			"uniform float alpha;"			
			"void main(){"
			"   vec2 st = gl_FragCoord.xy / SIZE;"	
			"   fragColor = vec4(texture(colorMap, st).rgb, alpha);}";
    fs->compileSourceCode(fsCode);
    cout << "FS log:" << fs ->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    // uniforms
    program->bind();
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_SIZE));
    program->release();

    // Setup texture for current view
    glActiveTexture(GL_TEXTURE0);

    glGenTextures( 1, &textureIdCur);
    glBindTexture(GL_TEXTURE_2D, textureIdCur);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0, GL_RGB, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

   // Setup texture for previous view
    glActiveTexture(GL_TEXTURE0);
    glGenTextures( 1, &textureIdPrev);
    glBindTexture(GL_TEXTURE_2D, textureIdPrev);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0, GL_RGB, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Resize to power-of-two viewport size
    g.resize(IMAGE_SIZE,IMAGE_SIZE);

    // Clear
    glClearColor(1,1,1,0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // auto-refresh timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
    timer->start();
}


void MotionBlur::drawRect()
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        
        // Create & bind empty VAO
        glGenVertexArrays(1, &VAO_rect);
        glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, 0, 
                            1, -1, 0, 
                           -1,  1, 0, 
                            1,  1, 0};

        GLuint VBO_coords;
        glGenBuffers(1, &VBO_coords);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    // 2. Draw
    glBindVertexArray (VAO_rect);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}



bool MotionBlur::paintGL()
{
    // Clear
    glClearColor(1,1,1,0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Pass A. Draw scene (depth test enabled, alpha blending disabled)
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    if (drawPlugin()) drawPlugin()->drawScene();

    // Copy color buffer to textureIdCur 
    glBindTexture(GL_TEXTURE_2D, textureIdCur);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE);
    glBindTexture(GL_TEXTURE_2D, 0);	

    // Clear
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Pass B. Draw quad using texture from prev frame (depth test disabled, alpha blending enabled)
    // COMPLETEU AQUESTA PART	
    glBindTexture(GL_TEXTURE_2D, textureIdPrev);
    program->bind();
    program->setUniformValue("alpha", float(1.0));
    drawRect();
    program->release();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Pass C. Draw quad using texture from this frame (depth test disabled, alpha blending enabled)
    glBindTexture(GL_TEXTURE_2D, textureIdCur);
    program->bind();
    program->setUniformValue("alpha", float(0.05)); // POSEU VALOR ALPHA DE L'ENUNCIAT
    drawRect();
    program->release();
    glBindTexture(GL_TEXTURE_2D, 0);	

    // Copy color buffer to textureIdPrev (will be used for next frame)
    // COMPLETEU AQUESTA PART
    glBindTexture(GL_TEXTURE_2D, textureIdPrev);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_SIZE, IMAGE_SIZE);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(glowing, Glowing)   // plugin name, plugin class
#endif

