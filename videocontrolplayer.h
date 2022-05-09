#ifndef VIDEOCONTROLPLAYER_H
#define VIDEOCONTROLPLAYER_H

#include <QObject>
#include <QWidget>
#include <tuple>

///
/// \brief The VideoControlPlayer class
///
/// 组合video player和文件输入框，构成一个文件输入
///
/// truple(filepath, HMStime beg, HMStime end) getValue()
///
///

class VideoControlPlayer
{
    Q_OBJECT
public:
    VideoControlPlayer();
};

#endif // VIDEOCONTROLPLAYER_H
