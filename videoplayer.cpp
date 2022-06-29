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
    preciseAdjustBtn = new QCheckBox("精细调节", this);
    beginTimeBtn = new QPushButton("设置为开始时间", this);
    endTimeBtn = new QPushButton("设置为结束时间", this);
    begin_time_label = new QLabel("当前设置的开始时间为：");
    end_time_label = new QLabel("当前设置的结束时间为：");
    begin_time = new QLineEdit("00:00:00:000");
    end_time = new QLineEdit("00:00:00:000");
    timeSlider = new QSlider(Qt::Horizontal, this);
    timer = new QTimer(this);
    timeSlider->setMinimum(0);
    timeSlider->setMaximum(1000);
    timeSlider->setTickInterval(1);
    totalLayout = new QGridLayout();
    settingsLayout = new QHBoxLayout();
    settingsLayout_2 = new QHBoxLayout();
    begin_end_layout = new QHBoxLayout();
    fileChoose = new getFile(this);

    settingsLayout->addWidget(changeState);
    settingsLayout->addWidget(muteBtn);
    settingsLayout->addWidget(preciseAdjustBtn);
    settingsLayout->addWidget(timeSlider);
    settingsLayout->addWidget(currentTime);
    settingsLayout_2->addWidget(beginTimeBtn);
    settingsLayout_2->addWidget(endTimeBtn);
    begin_end_layout->addWidget(begin_time_label);
    begin_end_layout->addWidget(begin_time);
    begin_end_layout->addWidget(end_time_label);
    begin_end_layout->addWidget(end_time);

    videoWidget->show();
    totalLayout->addWidget(fileChoose, 0, 0, 1, 8);
    totalLayout->addWidget(addToList, 0, 8, 1, 1);
    totalLayout->addWidget(videoWidget, 1, 0, 16, 9);
    totalLayout->addLayout(settingsLayout, 25, 0, 1, 10);
    totalLayout->addLayout(settingsLayout_2, 27, 2, 1, 6);
    totalLayout->addLayout(begin_end_layout, 29, 2, 1, 6);
    this->setLayout(totalLayout);
    QObject::connect(changeState, &QPushButton::clicked, this, &VideoPlayer::playPauseSwitch);
    QObject::connect(fileChoose, &getFile::fileChanged, this, &VideoPlayer::open);
    QObject::connect(timeSlider, &QSlider::sliderMoved, this, &VideoPlayer::changeTime);
    QObject::connect(muteBtn, &QCheckBox::stateChanged, this, &VideoPlayer::mute);
    QObject::connect(beginTimeBtn, &QPushButton::clicked, this, &VideoPlayer::setBeginTime);
    QObject::connect(endTimeBtn, &QPushButton::clicked, this, &VideoPlayer::setEndTime);
    QObject::connect(preciseAdjustBtn, &QCheckBox::stateChanged, this, &VideoPlayer::preciseAdjust);
    QObject::connect(begin_time, &QLineEdit::textChanged, this, &VideoPlayer::user_setTime);
    QObject::connect(player, &QAVPlayer::audioFrame, player, [this](const QAVAudioFrame &frame) { this->audioOutput.play(frame); });
    QObject::connect(player, &QAVPlayer::videoFrame, player, [this](const QAVVideoFrame &frame) {
        QVideoFrame videoFrame = frame.convertTo(AV_PIX_FMT_YUV420P);
        this->videoWidget->videoSink()->setVideoFrame(frame);
    });
    //it seems there are no mistakes
    QObject::connect(addToList, &QPushButton::clicked, this, [this](){emit addfile();});
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
    timer->start(500);
    extract = false;
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
    if(!preciseAdjustBtn->isChecked()){
        int totalTime = player->duration();
        int current_position = timeSlider->sliderPosition();
        player->seek(double(totalTime)/1000*current_position);
        QString str1 = ms_to_Qtime(totalTime*current_position/1000).toString("hh:mm:ss");
        QString str2 = ms_to_Qtime(totalTime).toString("hh:mm:ss");
        currentTime->setText(str1 + "/" + str2);
        player->play();
    }
    else{
        player->pause();
        int current_position = timeSlider->sliderPosition();
        player->seek(precise_stoppedTime + (current_position - 500)*10);
        QString str1 = ms_to_Qtime(player->position()).toString("hh:mm:ss:zzz");
        QString str2 = ms_to_Qtime(player->duration()).toString("hh:mm:ss:zzz");
        currentTime->setText(str1 + "/" + str2);
    }
}

void VideoPlayer::updateTime(){
    if (player->state() != QAVPlayer::PausedState){
        int totalTime = player->duration();
        int cur_time = player->position();
        int current_position = timeSlider->sliderPosition();
        timeSlider->setValue(1000*cur_time/totalTime);
        QString str1 = ms_to_Qtime(totalTime*current_position/1000).toString("hh:mm:ss");
        QString str2 = ms_to_Qtime(totalTime).toString("hh:mm:ss");
        currentTime->setText(str1 + "/" + str2);
    }
}

void VideoPlayer::mute(){
    if(muteBtn->isChecked())
    this->audioOutput.setVolume(0);
    else
    this->audioOutput.setVolume(100);
}

void VideoPlayer::setBeginTime(){
    extract = true;
    begtime = ms_to_Qtime(player->position());
    QString str1 = begtime.toString("hh:mm:ss:zzz");
    QString str2 = endtime.toString("hh:mm:ss:zzz");
    begin_time->setText(str1);
    end_time->setText(str2);
}

void VideoPlayer::setEndTime(){
    extract = true;
    endtime = ms_to_Qtime(player->position());
    QString str1 = begtime.toString("hh:mm:ss:zzz");
    QString str2 = endtime.toString("hh:mm:ss:zzz");
    begin_time->setText(str1);
    end_time->setText(str2);
}

void VideoPlayer::preciseAdjust(){
    if(preciseAdjustBtn->isChecked()){
        player->pause();
        int totalTime = player->duration();
        int current_position = timeSlider->sliderPosition();
        precise_stoppedTime = double(totalTime)/1000*current_position;
        player->seek(precise_stoppedTime);
        QString str1 = ms_to_Qtime(totalTime*current_position/1000).toString("hh:mm:ss:zzz");
        QString str2 = ms_to_Qtime(totalTime).toString("hh:mm:ss:zzz");
        currentTime->setText(str1 + "/" + str2);
        timeSlider->setSliderPosition(500);
    }
    else
    {
        player->play();
    }
}

void VideoPlayer::user_setTime(){
    QString str1 = begin_time->text();
    QString str2 = end_time->text();
    begtime = QTime::fromString(str1,"hh:mm:ss:zzz");
    endtime = QTime::fromString(str2,"hh:mm:ss:zzz");
}
