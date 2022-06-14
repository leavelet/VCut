#include "mainwindow.h"
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include "choosefile.h"
#include "filelist.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    topwidget = new QWidget(this);

    TabMain = new QTabWidget(topwidget);
    begin = new QPushButton("开始处理", topwidget);

    begin->setMaximumWidth(500);
    TabSetFFmpeg = new ffmpegWidget();
    TabChoseFile = new ChooseFile();
    TabMore = new QWidget();
    TabMain->insertTab(0, TabChoseFile, "选择文件");
    TabMain->insertTab(1, TabSetFFmpeg, "参数设置");
    TabMain->insertTab(2, TabMore, "更多选项");

    topLayout = new QVBoxLayout(topwidget);
    topLayout->addWidget(TabMain, Qt::AlignHCenter);
    topLayout->addWidget(begin, 1, Qt::AlignHCenter);

    topwidget->setLayout(topLayout);
    this->setCentralWidget(topwidget);
}

MainWindow::~MainWindow()
{
    delete topLayout;
}
