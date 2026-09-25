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
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    QOpenGLShaderProgram *program = nullptr;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
};

#endif // MESHVIEWPORT_H
