#include <QApplication>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LabaGL::MainWidget widget;

    widget.resize(600, 240);

    widget.show();

    return a.exec();
}
