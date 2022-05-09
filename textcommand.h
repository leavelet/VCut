#ifndef TEXTCOMMAND_H
#define TEXTCOMMAND_H

#include <QObject>
#include <QWidget>
///
/// \brief The TextCommand class
///
/// 一个文本框，一个开始处理的按钮
///
/// 主要功能是，检查上面ffmpeg命令的正确性，开始执行并弹出输出弹窗
///

class TextCommand:QObject
{
    Q_OBJECT
public:
    TextCommand();
};

#endif // TEXTCOMMAND_H
