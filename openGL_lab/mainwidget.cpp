#include "mainwidget.h"

#include <QOpenGLContext>
#include <QtGui>
#include <GL/glaux.h>
//#include <GLES3/gl3.h>
#include <GL/gl.h>

static const GLfloat GL_PI = 3.141592654f;

using namespace LabaGL;

//--------------------------------------SPHERE

Sphere::Sphere(const QVector3D& position
               , const GLfloat radius
               , const QVector3D& interval)
    : m_currentPosition{ position }
    , m_radius{ radius }
    , m_interval{ interval }
{
    m_colors.push_back(QColor(Qt::green));
    m_colors.push_back(QColor(Qt::red));

    vertexCalculation();
}

Sphere::~Sphere()
{
}

void Sphere::draw()
{
    m_currentPosition += m_interval;

    glTranslatef(m_currentPosition.x()
                 ,  m_currentPosition.y()
                 , m_currentPosition.z());

    GLuint n = glGenLists(1);
    glNewList(n, GL_COMPILE_AND_EXECUTE);

    glBegin(/*GL_LINE_STRIP);//*/GL_TRIANGLE_STRIP);

    bool checkColor = false;

    for(auto vertex : m_vertex)
    {
        if(checkColor)
        {
            if(m_colors.empty())
            {
                glColor3f(1.0, 1.0, 1.0);
            }
            else
            {
                glColor3f(static_cast<GLfloat>(m_colors.at(0).redF()),
                          static_cast<GLfloat>(m_colors.at(0).greenF()),
                          static_cast<GLfloat>(m_colors.at(0).blueF()));
            }
            checkColor = false;
        }
        else
        {
            if(m_colors.size() > 1)
            {
                glColor3f(static_cast<GLfloat>(m_colors.at(1).redF()),
                          static_cast<GLfloat>(m_colors.at(1).greenF()),
                          static_cast<GLfloat>(m_colors.at(1).blueF()));
            }
            checkColor = true;
        }
        glVertex3f(vertex.x(), vertex.y(), vertex.z());
    }

    glEnd();

    glEndList();

    glCallList(n);

    glLoadIdentity();
}

QVector3D Sphere::drivingVector() const
{
    return  QVector3D{};
}

void Sphere::setDrivingVector(const QVector3D &)
{

}

float Sphere::speed() const
{
    return 0.0;
}

void Sphere::setSpeed(const float)
{

}

QVector3D Sphere::currentPosition() const
{
    return QVector3D{};
}

std::vector<QVector3D> Sphere::pointsCurrentPosition() const
{
    std::vector<QVector3D> points;

    for(auto point : m_vertex)
    {
        points.push_back(point + m_currentPosition);
    }

    return points;
}

std::vector<QColor> Sphere::colors() const
{
    return m_colors;
}

void Sphere::setColors( const std::vector<QColor>& colors)
{
    if(colors == m_colors)
    {
        return;
    }

    m_colors = colors;
}

void Sphere::vertexCalculation()
{
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles

    int gradation = 20;

    for (alpha = 0.0; alpha < GL_PI; alpha += GL_PI/gradation)
    {
        for (beta = 0.0; beta < 2.01f*GL_PI; beta += GL_PI/gradation)
        {
            x = m_radius*cosf(beta)*sinf(alpha);
            y = m_radius*sinf(beta)*sinf(alpha);
            z = m_radius*cosf(alpha);

            m_vertex.push_back( {x, y, z} );

            x = m_radius*cosf(beta)*sinf(alpha + GL_PI/gradation);
            y = m_radius*sinf(beta)*sinf(alpha + GL_PI/gradation);
            z = m_radius*cosf(alpha + GL_PI/gradation);

            m_vertex.push_back( {x, y, z} );
        }
        glEnd();
    }
}

///--------------------------------------PLANE

Plane::Plane()
{

}

Plane::~Plane()
{

}

void Plane::draw()
{
    GLuint n = glGenLists(1);

    glNewList(n, GL_COMPILE_AND_EXECUTE);

    GLfloat fSize = 0.7f;

    glBegin(GL_QUADS);

        glColor4f(1.0f, 0.0f, 0.0f, 1.0);
        glVertex3f(-fSize, -fSize, fSize);
        glVertex3f(fSize, -fSize, fSize);
        glVertex3f(fSize, -fSize, -fSize);
        glVertex3f(-fSize, -fSize, -fSize);

    glEnd();

    glEndList();

    glCallList(n);

    glLoadIdentity();
}

QVector3D Plane::drivingVector() const
{
    return QVector3D{};
}

void Plane::setDrivingVector(const QVector3D &)
{

}

float Plane::speed() const
{
    return 0.0;
}

void Plane::setSpeed(const float)
{

}

QVector3D Plane::currentPosition() const
{
    return QVector3D{};
}

std::vector<QVector3D> Plane::pointsCurrentPosition() const
{
    return std::vector<QVector3D>{};
}

//---------------------------------------WIDGET

MainWidget::MainWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_xRotate{ 0 }
    , m_yRotate{ 0 }
    , m_sphereLeft{ nullptr }
    , m_sphereRight{ nullptr }
    , m_bottom{ nullptr }
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
        glTranslatef(0.0, 0.0, -3.0);
        glRotatef(m_xRotate, 1.0, 0.0, 0.0);
        glRotatef(m_yRotate, 0.0, 1.0, 0.0);

        m_sphereLeft->draw();
    }

    {
        glTranslatef(0.0, 0.0, -3.0);
        glRotatef(m_xRotate, 1.0, 0.0, 0.0);
        glRotatef(m_yRotate, 0.0, 1.0, 0.0);

        m_sphereRight->draw();
    }

    {
        glTranslatef(0.0, 0.0, -3.0);
        glRotatef(m_xRotate, 1.0, 0.0, 0.0);
        glRotatef(m_yRotate, 0.0, 1.0, 0.0);

        m_bottom->draw();
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
    const bool isCollision = collision(m_sphereLeft.get(), m_sphereRight.get());

    if(isCollision)
    {
        std::vector<QColor> colors;

        colors.push_back(QColor(Qt::gray));
        colors.push_back(QColor(Qt::yellow));

        m_sphereLeft->setColors(colors);
    }

    QOpenGLWidget::update();
}

void MainWidget::initFigures()
{
    m_sphereLeft = std::make_unique<Sphere>( QVector3D{ -1, 0, 0 }, 0.7f, QVector3D{0.01f, 0, 0} );
    m_sphereRight = std::make_unique<Sphere>( QVector3D{ 1, 0, 0 }, 0.4f, QVector3D{-0.001f, 0, 0} );
    m_bottom = std::make_unique<Plane>();
}

bool MainWidget::collision(const Figure* figure1, const Figure* figure2)
{
    //sqrt((x1-x2)^2+(y1-y2)^2+(z1-z2)^2)-R1-R2
    const auto points1 = figure1->pointsCurrentPosition();
    const auto points2 = figure2->pointsCurrentPosition();

    const auto r1 = 0.7f;
    const auto r2 = 0.4f;

    for(const auto& point1 : points1)
    {
        for(const auto& point2 : points2)
        {
            auto d = sqrtf(
                   (point1.x()-point2.x()) * (point1.x()-point2.x())
                 + (point1.y()-point2.y()) * (point1.y()-point2.y())
                 + (point1.z()-point2.z()) * (point1.z()-point2.z()))
                 - r1-r2;
            if( d <= 0)
            {
                //return true;
            }
        }
    }

    return  false;
}
