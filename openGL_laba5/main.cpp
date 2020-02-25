#include <QApplication>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LabaGL::MainWidget widget;

    widget.show();

    widget.resize(320, 240);

    return a.exec();
}
