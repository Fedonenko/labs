#ifndef CYLINDER_H
#define CYLINDER_H

#include "figure.h"

namespace LabaGL {


class Cylinder
        : public Figure
{
public:
    Cylinder();

    virtual void draw() override;

    virtual QVector3D motionVector() const override;
    virtual void setMotionVector(const QVector3D&) override;

    virtual float speed() const override;
    virtual void setSpeed(const float) override;

    virtual QVector3D currentPosition() const override;
    virtual std::vector<QVector3D> pointsCurrentPosition() const override;

};

}

#endif // CYLINDER_H
