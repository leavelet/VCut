#ifndef FILELIST_H
#define FILELIST_H

#include <QListWidget>
#include <QPushButton>
#include <QTime>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QComboBox>

#include "videoplayer.h"
#include "filestruct.h"
/// 实现add,remove,getval方法
/// 向上向下移动+-的button

class Filelist: public QWidget
{
    Q_OBJECT
public:
    QLabel *label;
    QCheckBox *mergeOrSingle;
    QListWidget *Qlist;
    QGridLayout *topLayout;
    QHBoxLayout *topText;
    QPushButton *buttonRemove, *buttonUp, *buttonDown, *buttonClear, *buttonCopy;
    QHBoxLayout *buttonLayout;
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
    void clearbutton_clicked();
    void copybutton_clicked();
signals:
    void contentChanged();
};

#endif // FILELIST_H
