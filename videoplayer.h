#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QEvent>
#include <QStyle>
#include <QDebug>
#include <QtAVPlayer/qavplayer.h>
#include <QtAVPlayer/qavvideoframe.h>
#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QCheckBox>
#include <QTime>
#include <QVideoSink>
#include <QGraphicsScene>
#include <QLabel>
#include <QString>

#include "getfile.h"
#include "filestruct.h"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = Q_NULLPTR);
    ~VideoPlayer();
    QTime begtime,endtime;
    int total_time;
    int precise_stoppedTime;
    QString filename = "";
    void changeCurrentPlaying(FileStruct file);
    void setCurrentTime(qint64 t);

private:

    QAVPlayer* player;
    QVideoWidget* videoWidget;
    QPushButton *changeState, *addToList, *beginTimeBtn, *endTimeBtn;
    QCheckBox *setVolume, *muteBtn, *preciseAdjustBtn;
    QSlider *timeSlider;
    QHBoxLayout *settingsLayout, *settingsLayout_2;
    QGridLayout *totalLayout;
    getFile *fileChoose;
    QAVAudioOutput audioOutput;
    QLabel *currentTime, *begin_end_time;
    QTimer *timer;

signals:
    void timeChanged();
    void videoChaged();
    void addfile();
public slots:
    void open();
    void playPauseSwitch();
    void changeTime();
    void mute();
    void updateTime();
    void setBeginTime();
    void setEndTime();
    void preciseAdjust();
};

QTime ms_to_Qtime(int ms);

#endif // VIDEOPLAYER_H
