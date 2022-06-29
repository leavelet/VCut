#ifndef FILESTRUCT_H
#define FILESTRUCT_H
#include <QString>
#include <QTime>
#include <QtAVPlayer/qavplayer.h>

class FileStruct
{
public:
    FileStruct();
    FileStruct(QString name, QTime beg, QTime end);
    FileStruct(QString name);
    QString filename;
    QTime beg_time, end_time;
    QString command;
};

#endif // FILESTRUCT_H
