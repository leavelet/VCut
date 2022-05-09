#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QWidget>

///
/// \brief The VideoPlayer class
///
/// 视频播放器，结构是视频在上面，下面放“开始/暂停”“解除静音”和进度条
///
/// 方法:
///     open()
///
///     changePlayStatus()
///
///     changeVloumeSatue()
///
///     changePercent(HMSTime)
///
///     [返回HMSTime]getPercent()
///
class VideoPlayer
{
    Q_OBJECT
public:
    VideoPlayer();
};

#endif // VIDEOPLAYER_H
