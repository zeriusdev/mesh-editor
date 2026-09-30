#ifndef MESHVIEWPORT_H
#define MESHVIEWPORT_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class MeshViewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MeshViewport(QWidget *parent = nullptr);
    ~MeshViewport() override;
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;
    float m_angle = 0.0f;
    QMatrix4x4 m_projection;
};

#endif // MESHVIEWPORT_H
