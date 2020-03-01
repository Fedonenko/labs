#ifndef SPHERE_H
#define SPHERE_H

#include "figure.h"

namespace  LabaGL
{

class Sphere
        : public Figure
{
public:
    Sphere(const QVector3D& position
           , const GLfloat radius
           , const QVector3D& motionVector = {0.0, 0.0, 0.0});

    ~Sphere() override;

public:
    virtual void draw() override;

    virtual QVector3D motionVector() const override;
    virtual void setMotionVector(const QVector3D&) override;

    virtual float speed() const override;
    virtual void setSpeed(const float) override;

    virtual QVector3D currentPosition() const override;
    virtual std::vector<QVector3D> pointsCurrentPosition() const override;

    virtual std::vector<QColor> colors() const override;
    virtual void setColors( const std::vector<QColor>& ) override;

    virtual GLfloat radius() const override;

    virtual LabaGL::ModeFigure mode() const override { return ModeFigure::modeSphere; }

private:
    void vertexCalculation();
    void initDrawFigure();

private:
    QVector3D m_currentPosition;
    GLfloat m_radius;
    QVector3D m_motionVector;
    std::vector<QVector3D> m_vertex;

    std::vector<QColor> m_colors;

    GLuint m_nSphere;

};

}


#endif // SPHERE_H
