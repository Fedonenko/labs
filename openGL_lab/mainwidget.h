#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QTimer>

namespace LabaGL {

class MainWidget
        : public QOpenGLWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;

    GLuint drawSphere(QVector3D point = QVector3D{0, 0, 0}, GLfloat radius = 0.5);

private:
    GLuint m_nPyramid;
    GLfloat m_xRotate;
    GLfloat m_yRotate;
    QPoint m_ptPositione;

    QVector3D m_position0;
    QVector3D m_position1;
    QVector3D m_position2;

    QTimer m_timer;

};

}

#endif // MAINWIDGET_H
