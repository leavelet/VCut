#ifndef FILELIST_H
#define FILELIST_H

#include <QListWidget>
#include <QPushButton>
#include <QTime>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QResizeEvent>

#include "videoplayer.h"
#include "filestruct.h"
/// 实现add,remove,getval方法
/// 向上向下移动+-的button

class Filelist: public QWidget
{
public:
    QLabel *label;
    QCheckBox *mergeOrSingle;
    QListWidget *Qlist;
    QGridLayout *topLayout;
    QHBoxLayout *topText;
    QPushButton *buttonRemove, *buttonUp, *buttonDown;
    Filelist(QWidget* parent);
    ~Filelist();
    std::list<FileStruct> filelist;
    std::list<FileStruct>::iterator listiterator;
public slots:
    void addfile(FileStruct s);
    void setconnect();
    void removebutton_clicked();
    //void addbutton_clicked();
    void upbutton_clicked();
    void downbutton_clicked();
};
#endif // FILELIST_H
