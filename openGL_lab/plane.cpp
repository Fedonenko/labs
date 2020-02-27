#include "plane.h"

using namespace LabaGL;

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

QVector3D Plane::motionVector() const
{
    return QVector3D{};
}

void Plane::setMotionVector(const QVector3D &)
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

