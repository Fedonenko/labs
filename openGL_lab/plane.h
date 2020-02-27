#ifndef PLANE_H
#define PLANE_H

#include "figure.h"

namespace LabaGL
{

class Plane
        : public Figure
{
public:
    Plane();
    ~Plane() override;

public:
    virtual void draw() override;

    virtual QVector3D motionVector() const override;
    virtual void setMotionVector(const QVector3D&) override;

    virtual float speed() const override;
    virtual void setSpeed(const float) override;

    virtual QVector3D currentPosition() const override;
    virtual std::vector<QVector3D> pointsCurrentPosition() const override;

private:
    QVector3D m_position;

};

}

#endif // PLANE_H
