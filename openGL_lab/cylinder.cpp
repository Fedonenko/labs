#include "cylinder.h"

using namespace LabaGL;

Cylinder::Cylinder()
{

}

void Cylinder::draw()
{

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
