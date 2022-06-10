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
    chooseLayout->addWidget(player, 0, 1, 8, 10);
    chooseLayout->addWidget(fileToChoose, 0, 0, 5, 1);
    chooseLayout->addWidget(fileImport, 5, 0, 3, 1);
    this->setLayout(chooseLayout);

    QObject::connect(player, &VideoPlayer::addfile, fileToChoose, [&](){
        FileStruct tmp(player->filename, player->begtime, player->endtime);
        fileToChoose->addfile(tmp);
    });
    QObject::connect(fileToChoose->Qlist, &QListWidget::currentRowChanged, this, [this](){
        FileStruct fs(*fileToChoose->listiterator);
        this->player->changeCurrentPlaying(fs);
    });

    fileImport->filelist = fileToChoose;

}

ChooseFile::~ChooseFile(){
    delete chooseLayout;
}
