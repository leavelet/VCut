#include "mainwindow.h"
#include "choosefile.h"
#include "filelist.h"

#include <QMessageBox>
#include <QFileInfo>
#include <QTime>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    topwidget = new QWidget(this);

    TabMain = new QTabWidget(topwidget);
    begin = new QPushButton("开始处理", topwidget);

    begin->setMaximumWidth(500);
    TabChoseFile = new ChooseFile();
    TabSetFFmpeg = new ffmpegWidget(TabChoseFile);
    TabMore = new QWidget();
    TabMain->insertTab(0, TabChoseFile, "选择文件");
    TabMain->insertTab(1, TabSetFFmpeg, "参数设置");
    TabMain->insertTab(2, TabMore, "更多选项");

    topLayout = new QVBoxLayout(topwidget);
    topLayout->addWidget(TabMain, Qt::AlignHCenter);
    topLayout->addWidget(begin, 1, Qt::AlignHCenter);

    topwidget->setLayout(topLayout);
    this->setCentralWidget(topwidget);
    connect(begin, &QPushButton::clicked, this, &MainWindow::beginProcess);
}

MainWindow::~MainWindow()
{
    delete topLayout;
}

void MainWindow::beginProcess(){
    if(TabChoseFile->fileToChoose->filelist.size() == 0){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("没有导入任何文件！");
        msgBox.exec();
    }
    vector<QString> commands;
    if(TabChoseFile->fileToChoose->mergeOrSingle->isChecked()){
        commands.push_back("");
        //merge
        auto dir = QDir::temp();
        dir.mkdir("VCut_tmp");
        dir.cd("VCut_tmp");
        QDir::setCurrent(dir.absolutePath());
        QString filename="merge_filelist.txt";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)){
            QTextStream stream( &file );
            for(auto &x: TabChoseFile->fileToChoose->filelist){
                stream << "file \" " << x.filename << "\" " << Qt::endl;
            }
             commands[0] = "ffmpeg -y -hide_banner -f concat -i \"merge_filelist.txt\" ";
            if(TabSetFFmpeg->finalCommand->document()->toPlainText().contains("ffmpeg命令")){
                 commands[0] += " -c copy 合成的视频" + QTime::currentTime().toString() + ".mp4";
            }
            else {
                QString appliedCommand = TabSetFFmpeg->finalCommand->document()->toPlainText();
                appliedCommand.erase(appliedCommand.constBegin(), appliedCommand.constBegin()+20);
                commands[0] += appliedCommand;
            }
        }
    }
    else{
        if(TabSetFFmpeg->finalCommand->document()->toPlainText().contains("ffmpeg命令")){
            for(auto iter = TabChoseFile->fileToChoose->filelist.begin();
                 iter != TabChoseFile->fileToChoose->filelist.end(); iter++){
                iter->command = TabSetFFmpeg->finalCommand->document()->toPlainText();
            }
        }
        for(auto &x: TabChoseFile->fileToChoose->filelist){
            QString command_of_file = x.command;
            command_of_file.erase(command_of_file.constBegin(), command_of_file.constBegin()+20);
            QString command_now = "ffmpeg -y -hide_banner";
            if(x.extract){
                command_now += " -ss " + x.beg_time.toString("hh:mm:ss.zzz") + " " + x.end_time.toString("hh:mm:ss.zzz") + " ";
            }
            command_now += "-i \" " + x.filename + "\" " + command_of_file;
            commands.push_back(command_now);
        }
    }
}
