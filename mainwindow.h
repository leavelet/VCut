//written by syh

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "choosefile.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTabWidget *TabMain;
    QPushButton *begin;
    QWidget *topwidget;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *TabSetFFmpeg, *TabMore;
    ChooseFile* TabChoseFile;
    QVBoxLayout *topLayout;
signals:

};
#endif // MAINWINDOW_H
