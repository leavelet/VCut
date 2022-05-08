#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(900, 800);
    w.show();
    int x = w.x(), y = w.y();
    qDebug("x: %d y: %d\n", x, y);

    return a.exec();
}
