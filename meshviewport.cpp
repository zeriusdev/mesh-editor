#include "meshviewport.h"

MeshViewport::MeshViewport(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void MeshViewport::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    program = new QOpenGLShaderProgram(this);

    const char *vertexShader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 pos;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 1.0);\n"
        "}\n";

    const char *fragmentShader =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}\n";

    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program->link();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));

    vao.release();
    vbo.release();
}

void MeshViewport::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MeshViewport::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.release();
    program->release();
}