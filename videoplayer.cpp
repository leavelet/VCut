#include "videoplayer.h"
#include <QtAVPlayer/qavvideoframe.h>
#include <QPalette>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}
{
    videoWidget = new QVideoWidget(this);
    player = new QAVPlayer;
    changeState = new QPushButton("暂停/播放",this);
    addToList = new QPushButton("添加到队列",this);
    setVolume = new QCheckBox("声音预览", this);
    preciseAdjust = new QCheckBox("精细调节", this);
    timeSlider = new QSlider(Qt::Horizontal, this);
    totalLayout = new QGridLayout();
    settingsLayout = new QHBoxLayout();
    fileChoose = new getFile(this);

    settingsLayout->addWidget(changeState);
    settingsLayout->addWidget(setVolume);
    settingsLayout->addWidget(preciseAdjust);
    settingsLayout->addWidget(timeSlider);
    videoWidget->show();
    totalLayout->addWidget(fileChoose, 0, 0, 1, 8);
    totalLayout->addWidget(addToList, 0, 8, 1, 1);
    totalLayout->addWidget(videoWidget, 1, 0, 16, 9);
    totalLayout->addLayout(settingsLayout, 17, 0, 1, 9);
    this->setLayout(totalLayout);

    QObject::connect(changeState, &QPushButton::clicked, this, &VideoPlayer::playPauseSwitch);
    QObject::connect(fileChoose, &getFile::fileChanged, this, &VideoPlayer::open);
    QObject::connect(player, &QAVPlayer::audioFrame, player, [this](const QAVAudioFrame &frame) { this->audioOutput.play(frame); });
    QObject::connect(player, &QAVPlayer::videoFrame, player, [this](const QAVVideoFrame &frame) {
        QVideoFrame videoFrame = frame.convertTo(AV_PIX_FMT_YUV420P);
        videoFrame.toImage().save("frame.jpg");
        qDebug() << videoFrame.pixelFormat() << Qt::endl;
        qDebug() << videoFrame.isValid() << Qt::endl;
        this->videoWidget->videoSink()->setVideoFrame(videoFrame);
    });
    //it seams there are no mistakes
    QObject::connect(addToList, &QPushButton::clicked, [this](){emit addfile();});

}

VideoPlayer::~VideoPlayer(){
    delete player;
    delete changeState;
    delete setVolume;
    delete preciseAdjust;
    delete timeSlider;
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
    int total_time = int(double(player->duration())/double(player->videoFrameRate())*1000);
    endtime = ms_to_Qtime(total_time);
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
