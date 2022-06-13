#ifndef FFMPEGWIDGET_H
#define FFMPEGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "ffoptions.h"

class ffmpegWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ffmpegWidget(QWidget *parent = nullptr);
    FFOptionsCheck* check;
    FFOptionsCombo* comb;
    QHBoxLayout* layout;

signals:

};

#endif // FFMPEGWIDGET_H
