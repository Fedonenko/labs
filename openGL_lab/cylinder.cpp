#include "cylinder.h"

#include <memory>
#include <QtGui>

using namespace LabaGL;

Cylinder::Cylinder(const GLfloat radius, const GLfloat height, const QVector3D& position)
    : m_radius{ radius }
    , m_height{ height }
    , m_position{ position }
{
    m_colors.push_back(QColor(Qt::green));
    m_colors.push_back(QColor(Qt::magenta));

    vertexCalculation();
}

void Cylinder::draw()
{
    //m_position += m_motionVector;

    glTranslatef(m_position.x()
                 ,  m_position.y()
                 , m_position.z());

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

QVector3D Cylinder::motionVector() const
{
    return QVector3D{};
}

void Cylinder::setMotionVector(const QVector3D&)
{

}

float Cylinder::speed() const
{
    return 0.0;
}

void Cylinder::setSpeed(const float)
{

}

QVector3D Cylinder::currentPosition() const
{
    return QVector3D{};
}

std::vector<QVector3D> Cylinder::pointsCurrentPosition() const
{
    return std::vector<QVector3D>{};
}

void Cylinder::vertexCalculation()
{
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles

    int gradation = 20;

    for (alpha = 0.0; alpha < GL_PI; alpha += GL_PI/gradation)
    {
        for (beta = 0.0; beta < 2.01f*GL_PI; beta += GL_PI/gradation)
        {
            x = m_radius * cosf(beta) * sinf(alpha);
            y = m_radius * sinf(beta) * sinf(alpha);
            z = m_radius * cosf(alpha);

            m_vertex.push_back( {x, y, z} );

            x = m_radius*cosf(beta) * sinf(alpha + GL_PI/gradation);
            y = m_radius*sinf(beta) * sinf(alpha + GL_PI/gradation);
            z = m_radius*cosf(alpha + GL_PI/gradation);

            m_vertex.push_back( {x, y, z} );
        }
    }

}
