#include "choosefile.h"
#include <QString>
#include <QThread>
#include <future>
#include <QVideoSink>
#include <QListWidget>
#include "filestruct.h"

ChooseFile::ChooseFile(QWidget *parent)
    : QWidget{parent}
{
    chooseLayout = new QGridLayout;
    player = new VideoPlayer(this);
    fileToChoose = new Filelist(this);
    fileImport = new selectwidget(this);
    fileProcessor =  new QSplitter(Qt::Vertical, this);

    fileProcessor->addWidget(fileToChoose);
    fileProcessor->addWidget(fileImport);
    QPalette p=fileProcessor->palette();
    p.setColor(QPalette::Window,QColor(25,155,245,100));
    fileProcessor->setPalette(p);

    QList<int> splitlist(2);
    splitlist[0]=3*height();
    splitlist[1]=2*height();
    fileProcessor->setSizes(splitlist);

    chooseLayout->addWidget(fileProcessor, 0, 0, 4, 1);
    chooseLayout->addWidget(player, 0, 1, 4, 3);
    this->setLayout(chooseLayout);

    QObject::connect(player, &VideoPlayer::addfile, fileToChoose, [&](){
        FileStruct tmp(player->filename, player->begtime, player->endtime, player->extract);
        fileToChoose->addfile(tmp);
    });
    QObject::connect(fileToChoose->Qlist, &QListWidget::currentRowChanged, this, [this](){
        if(!fileToChoose->filelist.empty() && fileToChoose->listiterator != fileToChoose->filelist.end()) {
            FileStruct fs(*fileToChoose->listiterator);
            this->player->changeCurrentPlaying(fs);
        }
    });
    fileImport->filelist = fileToChoose;
}

ChooseFile::~ChooseFile(){
    delete chooseLayout;
}
