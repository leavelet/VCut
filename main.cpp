#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QRect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(900, 700);
    w.show();
    return a.exec();
}
