#ifndef CHOOSEFILE_H
#define CHOOSEFILE_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include "videoplayer.h"
#include "filelist.h"
#include "selectwidget.h"

class ChooseFile : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseFile(QWidget *parent = nullptr);
    ~ChooseFile();
    selectwidget* fileImport;
    VideoPlayer* player;
    Filelist* fileToChoose;

private:
    QSplitter* fileProcessor;
    QGridLayout* chooseLayout;

};

#endif // CHOOSEFILE_H
