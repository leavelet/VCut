#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <QWidget>
#include <QLabel>
#include "videoplayer.h"

class videoInfo : public QWidget
{
    Q_OBJECT
public:
    explicit videoInfo(VideoPlayer* player, QWidget *parent = nullptr);
    QLabel* info;
    VideoPlayer* player;

signals:

public slots:
    void changeInfo();

};

#endif // VIDEOINFO_H
