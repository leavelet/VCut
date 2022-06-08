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

#include "getfile.h"
#include "filestruct.h"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = Q_NULLPTR);
    ~VideoPlayer();
    QTime begtime, endtime;
    QString filename = "";
    void changeCurrentPlaying(FileStruct file);

private:

    QAVPlayer* player;
    QVideoWidget* videoWidget;
    QPushButton *changeState, *addToList;
    QCheckBox *setVolume, *preciseAdjust;
    QSlider *timeSlider;
    QHBoxLayout *settingsLayout;
    QGridLayout *totalLayout;
    getFile *fileChoose;
    QAVAudioOutput audioOutput;

signals:
    void timeChanged();
    void videoChaged();
    void addfile();
public slots:
    void open();
    void playPauseSwitch();

};

QTime ms_to_Qtime(int ms);

#endif // VIDEOPLAYER_H
