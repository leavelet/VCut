#include "filestruct.h"

FileStruct::FileStruct()
{

}

FileStruct::FileStruct(QString name, QTime beg, QTime end){
    filename = name;
    beg_time = beg;
    end_time = end;
}
