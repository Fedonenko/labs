#include "mainwidget.h"

#include <QMouseEvent>
#include <QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLContext>


using namespace LabaGL;

MainWidget::MainWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_qObj = gluNewQuadric();

}

void MainWidget::initializeGL()
{
    auto functions = QOpenGLContext::currentContext()->functions();

    functions->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    functions->glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

void MainWidget::paintGL()
{
    //CExampleDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(m_xRotate, 1.0, 0.0, 0.0);
    glRotatef(m_yRotate, 0.0, 1.0, 0.0);

    GLuint n = glGenLists(1);
    glNewList(n, GL_COMPILE_AND_EXECUTE);

    glBegin(/*GL_LINE_STRIP);//*/GL_TRIANGLE_STRIP);


	glColor3f(0.0f, 0.5f, 0.5f);
	gluSphere(m_qObj, 1.0, 10, 10);

    glEndList();

    glCallList(n);

	//SwapBuffers(pDC->m_hDC);

}

void MainWidget::resizeGL(int w, int h)
{
    GLdouble ratio = qreal(w) / qreal(h ? h : 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, /*200 */static_cast<GLint>(w), /*200*/ static_cast<GLint>(h));
    glFrustum(-1.0 * ratio, 1.0 * ratio, -1.0, 1.0, 1.0, 10.0);
}

void MainWidget::mousePressEvent(QMouseEvent* e)
{
    m_ptPositione = e->pos();
}

void MainWidget::mouseMoveEvent(QMouseEvent* e)
{
    if( e->buttons() == Qt::LeftButton)
    {
        m_xRotate += 180 * static_cast<GLfloat>(e->y() - m_ptPositione.y()) / height();
        m_yRotate += 180 * static_cast<GLfloat>(e->x() - m_ptPositione.x()) / width();
        update();

        m_ptPositione = e->pos();
    }

}
