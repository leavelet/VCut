#ifndef FFMPEGCONTROLLER_H
#define FFMPEGCONTROLLER_H

#include <QMainWindow>


/// \brief The FFmpegController class
///
/// 自己实现的ffmpeg库，方法：
///
/// addItem(filePath, startIime, endTime)(其中会绑定这个Item的changed)
///
/// addEffect(int)
///
/// addHardCoreOpt(int KIND)
///
/// setOutPut(fileName)
///
/// [QString]generate()


class FFmpegController
{
public:
    FFmpegController();
};

#endif // FFMPEGCONTROLLER_H
