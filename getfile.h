#ifndef GETFILE_H
#define GETFILE_H

#include <QObject>
#include <QWidget>
#include "FileLine.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "QFileDialog"

class getFile : public QWidget
{
    Q_OBJECT
public:
    QHBoxLayout* layout;
    FileLine* fl;
    QPushButton* pushbutton;
    explicit getFile(QWidget *parent = nullptr);
    ~getFile();
public slots:
    void pushButton_clicked();
    void editFinish();
signals:
    void fileChanged();

};

#endif // GETFILE_H
