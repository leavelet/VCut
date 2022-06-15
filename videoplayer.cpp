#include "videoplayer.h"
#include <QtAVPlayer/qavvideoframe.h>
#include <QPalette>
#include <QString>
#include <QDebug>
#include <QImage>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}
{
    videoWidget = new QVideoWidget(this);
    player = new QAVPlayer;
    changeState = new QPushButton("暂停/播放",this);
    addToList = new QPushButton("添加到队列",this);
    muteBtn = new QCheckBox("静音", this);
    currentTime = new QLabel("00:00:00", this);
    timeSlider = new QSlider(Qt::Horizontal, this);
    timer = new QTimer(this);
    timeSlider->setMinimum(0);
    timeSlider->setMaximum(1000);
    timeSlider->setTickInterval(1);
    totalLayout = new QGridLayout();
    settingsLayout = new QHBoxLayout();
    fileChoose = new getFile(this);

    settingsLayout->addWidget(changeState);
    settingsLayout->addWidget(muteBtn);
    settingsLayout->addWidget(timeSlider);
    settingsLayout->addWidget(currentTime);
    videoWidget->show();
    totalLayout->addWidget(fileChoose, 0, 0, 1, 8);
    totalLayout->addWidget(addToList, 0, 8, 1, 1);
    totalLayout->addWidget(videoWidget, 1, 0, 16, 9);
    totalLayout->addLayout(settingsLayout, 25, 0, 1, 5);
    this->setLayout(totalLayout);
    QObject::connect(changeState, &QPushButton::clicked, this, &VideoPlayer::playPauseSwitch);
    QObject::connect(fileChoose, &getFile::fileChanged, this, &VideoPlayer::open);
    QObject::connect(timeSlider, &QSlider::sliderMoved, this, &VideoPlayer::changeTime);
    QObject::connect(muteBtn, &QCheckBox::stateChanged, this, &VideoPlayer::mute);
    QObject::connect(player, &QAVPlayer::audioFrame, player, [this](const QAVAudioFrame &frame) { this->audioOutput.play(frame); });
    QObject::connect(player, &QAVPlayer::videoFrame, player, [this](const QAVVideoFrame &frame) {
//        QVideoFrame videoFrame = frame.convertTo(AV_PIX_FMT_RGB32);
        this->videoWidget->videoSink()->setVideoFrame(frame);
    });
    //it seems there are no mistakes
    QObject::connect(addToList, &QPushButton::clicked, [this](){emit addfile();});
    QObject::connect(timer, &QTimer::timeout, this, &VideoPlayer::updateTime);
    QObject::connect(player, &QAVPlayer::paused, this, &VideoPlayer::updateTime);
    QObject::connect(player, &QAVPlayer::played, this, &VideoPlayer::updateTime);
}

VideoPlayer::~VideoPlayer(){
    delete player;
    delete changeState;
    delete timeSlider;
    delete addToList;
    delete muteBtn;
    delete currentTime;
}

QTime ms_to_Qtime(int ms){
    int hour = ms/1000/3600;
    int minute = (ms/1000)%3600/60;
    int second = ms/1000 % 60;
    int m = ms % 1000;
    if(hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + m != ms)
        qDebug() << hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 << " not equal " << ms << Qt::endl;
    return QTime(hour, minute, second, m);
}
void VideoPlayer::open(){
    filename = fileChoose->fl->Filepath;
    player->setSource(filename);
    player->pause();
    begtime = QTime(0, 0);
    total_time = player->duration();
    endtime = ms_to_Qtime(player->duration());
    timer->start(1000);
}

void VideoPlayer::playPauseSwitch(){
    if (player->state() != QAVPlayer::PausedState) { // No frames if it is already paused
        player->pause();
    }
    else {
        player->play();
    }
}

void VideoPlayer::changeCurrentPlaying(FileStruct file){
    begtime = file.beg_time;
    endtime = file.end_time;
    filename = file.filename;
    player->setSource(filename);
    player->pause();
}

void VideoPlayer::changeTime(){
    int totalTime = player->duration();
    int current_position = timeSlider->sliderPosition();
    player->seek(double(totalTime)/1000*current_position);
    QString str1 = ms_to_Qtime(totalTime*current_position/1000).toString("hh:mm:ss");
    QString str2 = ms_to_Qtime(totalTime).toString("hh:mm:ss");
    currentTime->setText(str1 + "/" + str2);
    player->play();
}

void VideoPlayer::updateTime(){
    int totalTime = player->duration();
    int cur_time = player->position();
    int current_position = timeSlider->sliderPosition();
    timeSlider->setValue(1000*cur_time/totalTime);
    QString str1 = ms_to_Qtime(totalTime*current_position/1000).toString("hh:mm:ss");
    QString str2 = ms_to_Qtime(totalTime).toString("hh:mm:ss");
    currentTime->setText(str1 + "/" + str2);
}

void VideoPlayer::mute(){
    if(muteBtn->isChecked())
    this->audioOutput.setVolume(0);
    else
    this->audioOutput.setVolume(100);
}
