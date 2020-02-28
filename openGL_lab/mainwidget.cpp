#include "mainwidget.h"

#include <QOpenGLContext>
#include <QtGui>
#include <GL/glaux.h>
//#include <GLES3/gl3.h>
#include <GL/gl.h>

#include "cylinder.h"
#include "plane.h"
#include "sphere.h"

using namespace LabaGL;

MainWidget::MainWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_xRotate{ 0 }
    , m_yRotate{ 0 }
    , m_sphereLeft{ nullptr }
    , m_sphereRight{ nullptr }
    , m_sphereSolidLeft{ nullptr }
    , m_sphereSolidRight{ nullptr }
    , m_bottom{ nullptr }
    , m_cylinder{ nullptr }
{
    initFigures();

    m_timer.setInterval(5);
    connect(&m_timer, &QTimer::timeout, this, [this](){
        update();
    });

    m_timer.start();
}

void MainWidget::initializeGL()
{
    auto functions = QOpenGLContext::currentContext()->functions();

    functions->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    functions->glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    //m_nPyramid = createPyramid(1.2f);
}

void MainWidget::resizeGL(int w, int h)
{
    GLdouble ratio = qreal(w) / qreal(h ? h : 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, /*200 */static_cast<GLint>(w), /*200*/ static_cast<GLint>(h));
    glFrustum(-1.0 * ratio, 1.0 * ratio, -1.0, 1.0, 1.0, 10.0);
}

void MainWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();   ///задаёт матрице проектирования единичную матрицу

    {
        globalRotate();
        m_sphereLeft->draw();
    }

    {
        globalRotate();
        m_sphereRight->draw();
    }

    {
        globalRotate();
        m_sphereSolidLeft->draw();
    }

    {
        globalRotate();
        m_sphereSolidRight->draw();
    }

    {
        globalRotate();
        m_bottom->draw();
    }

    {
        globalRotate();
        m_cylinder->draw();
    }
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    m_ptPositione = e->pos();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if( e->buttons() == Qt::LeftButton)
    {
        m_xRotate += 180 * static_cast<GLfloat>(e->y() - m_ptPositione.y()) / height();
        m_yRotate += 180 * static_cast<GLfloat>(e->x() - m_ptPositione.x()) / width();
        update();

        m_ptPositione = e->pos();
    }
}

void MainWidget::update()
{
    bool isCollision = collision(m_sphereLeft.get(), m_sphereRight.get());

    std::vector<QColor> colors;

    if( isCollision)
    {
        colors.push_back(QColor(Qt::gray));
        colors.push_back(QColor(Qt::yellow));

        m_sphereLeft->setMotionVector(m_sphereLeft->motionVector() * -1);
        m_sphereRight->setMotionVector(m_sphereRight->motionVector() * -1);
    }
    else
    {
        colors.push_back(QColor(Qt::blue));
        colors.push_back(QColor(Qt::darkGreen));
    }

    m_sphereLeft->setColors(colors);
    m_sphereRight->setColors(colors);

    if(collision(m_sphereLeft.get(), m_sphereSolidLeft.get()))
    {
        m_sphereLeft->setMotionVector(m_sphereLeft->motionVector() * -1);
    }

    if(collision(m_sphereRight.get(), m_sphereSolidRight.get()))
    {
        m_sphereRight->setMotionVector(m_sphereRight->motionVector() * -1);
    }


    QOpenGLWidget::update();
}

void MainWidget::initFigures()
{
    m_sphereLeft = std::make_unique<Sphere>( QVector3D{ -1, 0, 0 }, 0.7f, QVector3D{0.01f, 0, 0} );
    m_sphereRight = std::make_unique<Sphere>( QVector3D{ 1, 0, 0 }, 0.4f, QVector3D{-0.005f, 0, 0} );

    m_sphereSolidLeft = std::make_unique<Sphere>( QVector3D{ -2.5, 0, 0 }, 0.5f, QVector3D{ 0.0, 0, 0 } );
    m_sphereSolidRight = std::make_unique<Sphere>( QVector3D{ 2.5, 0, 0 }, 0.5f, QVector3D{ 0.0, 0, 0 } );

    m_bottom = std::make_unique<Plane>();

    m_cylinder = std::make_unique<Cylinder>(0.4f, 0.5f, QVector3D{ -2.0, 0.0, -3 });
}

bool MainWidget::collision(const Figure* figure1, const Figure* figure2)
{

    switch (figure1->mode())
    {
        case ModeFigure::modeSphere:
        {
        const auto r1 = figure1->radius();
        const auto r2 = figure2->radius();

        const auto point1 = figure1->currentPosition();
        const auto point2 = figure2->currentPosition();

        auto d = sqrtf(
               (point1.x()-point2.x()) * (point1.x()-point2.x())
             + (point1.y()-point2.y()) * (point1.y()-point2.y())
             + (point1.z()-point2.z()) * (point1.z()-point2.z()))
             - r1-r2;
        if( d <= 0)
        {
            return true;
        }

        return  false;
    }
    default:
        return  false;
    }

}

void MainWidget::globalRotate()
{
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(m_xRotate, 1.0, 0.0, 0.0);
    glRotatef(m_yRotate, 0.0, 1.0, 0.0);
}
