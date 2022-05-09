#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <QObject>
#include <QWidget>
///
/// \brief The OutputFile class
///
/// 一个组件组合，通过位置，名称，和后缀名确定输出的文件
///
/// getValue()方法，返回一个QString，默认值是输入文件名后加上日期时间
///
/// 如果输出位置已存在该文件，返回nullptr
class OutputFile:QObject
{
    Q_OBJECT
public:
    OutputFile();
};

#endif // OUTPUTFILE_H
