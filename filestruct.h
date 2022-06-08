#ifndef FILESTRUCT_H
#define FILESTRUCT_H
#include <QString>
#include <QTime>

class FileStruct
{
public:
    FileStruct();
    FileStruct(QString name, QTime beg, QTime end);
    QString filename;
    QTime beg_time, end_time;
};

#endif // FILESTRUCT_H
