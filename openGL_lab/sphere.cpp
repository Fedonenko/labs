#include "sphere.h"

#include <memory>

#include <QOpenGLContext>
#include <QtGui>

using namespace LabaGL;

Sphere::Sphere(const QVector3D& position
               , const GLfloat radius
               , const QVector3D& motionVector)
    : m_currentPosition{ position }
    , m_radius{ radius }
    , m_motionVector{ motionVector }
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
    m_currentPosition += m_motionVector;

    glTranslatef(m_currentPosition.x()
                 ,  m_currentPosition.y()
                 , m_currentPosition.z());

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

    glLoadIdentity();
}

QVector3D Sphere::motionVector() const
{
    return  m_motionVector; //motionVector
}

void Sphere::setMotionVector(const QVector3D &value)
{
    if(value == m_motionVector)
    {
        return;
    }
    m_motionVector = value;
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
    return m_currentPosition;
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

GLfloat Sphere::radius() const
{
    return m_radius;
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
    }
}

