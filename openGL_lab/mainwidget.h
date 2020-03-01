#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QTimer>

#include <memory>
#include <functional>
#include <GL/glu.h>


#include "figure.h"

namespace LabaGL
{


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

    virtual void update();

private:
    virtual void wheelEvent(QWheelEvent *event);

private:
    void initFigures();
    void initOfDraw();
    bool collision(const Figure*, const Figure*);
    void globalRotate();

private:
    GLuint m_nPyramid;
    GLfloat m_xRotate;
    GLfloat m_yRotate;
    int m_scroll;

    QPoint m_ptPositione;

    QTimer m_timer;

    std::unique_ptr<Figure> m_sphereLeft;
    std::unique_ptr<Figure> m_sphereRight;
    std::unique_ptr<Figure> m_sphereSolidLeft;
    std::unique_ptr<Figure> m_sphereSolidRight;
    std::unique_ptr<Figure> m_cylinder;

    std::unique_ptr<Figure> m_bottom;

    std::vector<std::function<void()>> m_listDraw;

    GLUquadricObj* m_qObj;

};

}

#endif // MAINWIDGET_H
