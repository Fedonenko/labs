#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QPoint>

#include <GL/glu.h>

namespace LabaGL
{


class MainWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);

    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;

private:
    QPoint m_ptPositione;
    GLfloat m_xRotate;
    GLfloat m_yRotate;

    GLUquadricObj* m_qObj;

};

}
#endif // MAINWIDGET_H
