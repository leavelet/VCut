#include "filestruct.h"

FileStruct::FileStruct()
{

}

FileStruct::FileStruct(QString name, QTime beg, QTime end){
    filename = name;
    beg_time = beg;
    end_time = end;
}

FileStruct::FileStruct(QString name):beg_time(0, 0){
    filename = name;
    QAVPlayer p;
    p.setSource(filename);
    int ms = double(p.duration())/p.videoFrameRate();
    int hour = ms/1000/3600;
    int minute = (ms/1000)%3600/60;
    int second = ms/1000 % 60;
    int m = ms % 1000;
    if(hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + m != ms)
        qDebug() << hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 << " not equal " << ms << Qt::endl;
    end_time = QTime(hour, minute, second, m);
}
