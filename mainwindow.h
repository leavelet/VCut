//written by syh

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QProcess>
#include <QDir>

#include "choosefile.h"
#include "ffmpegwidget.h"


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
    QWidget *TabMore;
    ffmpegWidget* TabSetFFmpeg;
    ChooseFile* TabChoseFile;
    QVBoxLayout *topLayout;
public slots:
    void beginProcess();

};
#endif // MAINWINDOW_H
