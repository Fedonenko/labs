#ifndef FIGURE_H
#define FIGURE_H

#include <QOpenGLWidget>
#include <QVector3D>

namespace LabaGL
{

static const GLfloat GL_PI = 3.141592654f;

enum ModeFigure
{
    modeSphere,
    modeParallelepiped,
    modePlace,
    modePolyhedron
};

class Figure
{
public:
    virtual ~Figure() = default;

    virtual void draw() = 0;

    virtual QVector3D motionVector() const = 0;
    virtual void setMotionVector(const QVector3D&) = 0;

    virtual float speed() const = 0;
    virtual void setSpeed(const float) = 0;

    virtual QVector3D currentPosition() const = 0;
    virtual std::vector<QVector3D> pointsCurrentPosition() const = 0;

    virtual std::vector<QColor> colors() const { return std::vector<QColor>{}; }
    virtual void setColors( const std::vector<QColor>& ){}

    virtual GLfloat radius() const { return 0.0f; }
    virtual LabaGL::ModeFigure mode() const { return ModeFigure::modePolyhedron; }
};

}

#endif // FIGURE_H
