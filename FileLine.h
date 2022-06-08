#ifndef FILELINE_H
#define FILELINE_H

#include <QLineEdit>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "QFileInfo"
///
/// \brief The FileLine class
///
/// \abstract 实现一个可以用拖放和输入文件名两种方式获取文件的文字框
///
/// 大概思路：如果有拖放并且被拖放的内容是文件，把这个文件转为绝对地址的字符串并显示。最后保留可见的字符串
///
/// 方法:
///     getValue，返回QString
///
///     重载(),bool，文件是否合法
///
/// 信号:
///     如果发生了更改，触发changed
bool iswindows();

class FileLine : public QLineEdit
{
public:
    QString Filepath;
    FileLine(QWidget *parent);
    QString getvalue();
    bool operator()(QString& name);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
signals:
    void changed();
};

#endif // FILELINE_H
