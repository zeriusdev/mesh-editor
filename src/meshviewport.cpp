#include "meshviewport.h"
#include <QMatrix4x4>
#include <QTimer>

MeshViewport::MeshViewport(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        m_angle += 1.0f;
        update();
    });
    timer->start(16);
}

MeshViewport::~MeshViewport()
{
    makeCurrent();
    delete m_vao;     m_vao = nullptr;
    delete m_vbo;     m_vbo = nullptr;
    delete m_program; m_program = nullptr;
    doneCurrent();
}

void MeshViewport::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_program = new QOpenGLShaderProgram();

    const char *vertexShader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 pos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "    gl_Position = projection * view * model *  vec4(pos, 1.0);\n"
        "}\n";

    const char *fragmentShader =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}\n";

    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    m_program->link();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    m_vbo = new QOpenGLBuffer();
    m_vao = new QOpenGLVertexArrayObject();

    m_vao->create();
    m_vao->bind();

    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));

    m_vao->release();
    m_vbo->release();
}

void MeshViewport::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, float(w) / float(h), 0.1f, 100.0f);
}

void MeshViewport::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 model;
    model.rotate(m_angle, 0.0f, 0.0f, 1.0f);
    QMatrix4x4 view;
    view.lookAt(QVector3D(0.0f, 0.0f, 1.0f),
                QVector3D(0.0f, 0.0f, 0.0f),
                QVector3D(0.0f, 1.0f, 0.0f));
    m_program->bind();
    m_program->setUniformValue("projection", m_projection);
    m_program->setUniformValue("model", model);
    m_program->setUniformValue("view", view);
    m_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_vao->release();
    m_program->release();
}