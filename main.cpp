#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QRect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    QSize windowInitSize(screenWidth*0.9, screenWidth*0.9);

    MainWindow w;
    w.resize(900, 900);
    w.show();
    return a.exec();
}
