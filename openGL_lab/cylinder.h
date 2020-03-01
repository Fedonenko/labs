#ifndef CYLINDER_H
#define CYLINDER_H

#include "figure.h"

namespace LabaGL {


class Cylinder
        : public Figure
{
public:
    Cylinder(const GLfloat radius, const GLfloat height, const QVector3D& position = QVector3D{0,0,0});

    virtual void draw() override;

    virtual QVector3D motionVector() const override;
    virtual void setMotionVector(const QVector3D&) override;

    virtual float speed() const override;
    virtual void setSpeed(const float) override;

    virtual QVector3D currentPosition() const override;
    virtual std::vector<QVector3D> pointsCurrentPosition() const override;

private:
    void vertexCalculation();

private:
    GLfloat m_radius;
    GLfloat m_height;
    QVector3D m_position;

    std::vector<QVector3D> m_vertex;

    std::vector<QColor> m_colors;
};

}

#endif // CYLINDER_H
