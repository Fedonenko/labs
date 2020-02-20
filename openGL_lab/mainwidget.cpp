#include "mainwidget.h"

#include <QOpenGLContext>
#include <QtGui>
#include <GL/glaux.h>
//#include <GLES3/gl3.h>
#include <GL/gl.h>

#define GL_PI 3.141592654f

using namespace LabaGL;

MainWidget::MainWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_xRotate{ 0 }
    , m_yRotate{ 0 }
    , m_position0{1.0f, 0.3f, 0.2f}
    , m_position1{0.2f, 1.0f, 0.2f}
    , m_position2{0.2f, 0.3f, 0.8f}
{

    m_timer.setInterval(5);
    connect(&m_timer, &QTimer::timeout, this, [this](){
        QVector3D interval{0.001f, 0.001f, 0.001f};

        m_position0 -= interval;
        m_position1 += interval;
        interval.setY(0.0f);
        m_position2 += interval;

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
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(m_xRotate, 1.0, 0.0, 0.0);
    glRotatef(m_yRotate, 0.0, 1.0, 0.0);

    glCallList(drawSphere(m_position0));
    glCallList(drawSphere(m_position1));
    glCallList(drawSphere(m_position2));
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

GLuint MainWidget::drawSphere(QVector3D point, GLfloat radius)
{
    GLuint n = glGenLists(1);

    glNewList(n, GL_COMPILE_AND_EXECUTE);

    const float PI = 3.141592f;
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles

    int gradation = 20;

    float x0 = point.x();
    float y0 = point.y();
    float z0 = point.z();

    GLfloat fSize = 0.7f;

    for (alpha = 0.0; alpha < GL_PI; alpha += GL_PI/gradation)
    {
        glColor3f(0.0, 1.0, 0.0);

        glBegin(/*GL_LINE_STRIP);//*/GL_TRIANGLE_STRIP);
        for (beta = 0.0; beta < 2.01f*GL_PI; beta += GL_PI/gradation)
        {
            x = radius*cosf(beta)*sinf(alpha);
            y = radius*sinf(beta)*sinf(alpha);
            z = radius*cosf(alpha);

            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(x + x0, y + y0, z + z0);

            x = radius*cosf(beta)*sinf(alpha + GL_PI/gradation);
            y = radius*sinf(beta)*sinf(alpha + GL_PI/gradation);
            z = radius*cosf(alpha + GL_PI/gradation);

            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(x + x0, y + y0, z + z0);
        }
        glEnd();
    }

        glBegin(GL_QUADS);

            glColor4f(1.0f, 0.0f, 0.0f, 1.0);
            glVertex3f(-fSize, -fSize, fSize);
            glVertex3f(fSize, -fSize, fSize);
            glVertex3f(fSize, -fSize, -fSize);
            glVertex3f(-fSize, -fSize, -fSize);

        glEnd();

    glEndList();

    return n;
}
