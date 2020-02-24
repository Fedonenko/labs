#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QTimer>

#include <memory>

namespace LabaGL
{

class Figure
{
public:
    virtual ~Figure() = default;

    virtual void draw() = 0;

    virtual QVector3D drivingVector() const = 0;
    virtual void setDrivingVector(const QVector3D&) = 0;

    virtual float speed() const = 0;
    virtual void setSpeed(const float) = 0;

    virtual QVector3D currentPosition() const = 0;
    virtual std::vector<QVector3D> pointsCurrentPosition() const = 0;

    virtual std::vector<QColor> colors() const { return std::vector<QColor>{}; }
    virtual void setColors( const std::vector<QColor>& ){}
};

class Sphere
        : public Figure
{
public:
    Sphere(const QVector3D& position
           , const GLfloat radius
           , const QVector3D& interval = {0.0, 0.0, 0.0});

    ~Sphere() override;

public:
    virtual void draw() override;

    virtual QVector3D drivingVector() const override;
    virtual void setDrivingVector(const QVector3D&) override;

    virtual float speed() const override;
    virtual void setSpeed(const float) override;

    virtual QVector3D currentPosition() const override;
    virtual std::vector<QVector3D> pointsCurrentPosition() const override;

    virtual std::vector<QColor> colors() const override;
    virtual void setColors( const std::vector<QColor>& ) override;

private:
    void vertexCalculation();

private:
    QVector3D m_currentPosition;
    GLfloat m_radius;
    QVector3D m_interval;
    std::vector<QVector3D> m_vertex;

    std::vector<QColor> m_colors;

};

class Plane
        : public Figure
{
public:
    Plane();
    ~Plane() override;

public:
    virtual void draw() override;

    virtual QVector3D drivingVector() const override;
    virtual void setDrivingVector(const QVector3D&) override;

    virtual float speed() const override;
    virtual void setSpeed(const float) override;

    virtual QVector3D currentPosition() const override;
    virtual std::vector<QVector3D> pointsCurrentPosition() const override;

private:
    QVector3D m_position;

};

class MainWidget
        : public QOpenGLWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;

    virtual void update();

private:
    void initFigures();
    bool collision(const Figure* figure1, const Figure* figure2);

private:
    GLuint m_nPyramid;
    GLfloat m_xRotate;
    GLfloat m_yRotate;
    QPoint m_ptPositione;

    QTimer m_timer;

    std::unique_ptr<Figure> m_sphereLeft;
    std::unique_ptr<Figure> m_sphereRight;
    std::unique_ptr<Figure> m_bottom;

};

}

#endif // MAINWIDGET_H
