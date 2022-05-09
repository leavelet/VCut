#ifndef HMSTIME_H
#define HMSTIME_H

#include <QWidget>
///
/// \brief The HMSTime class
///
/// 转换为时间，分两种形式，HH:MM:SS或者t(秒)
///
class HMSTime
{
public:
    HMSTime();
    HMSTime(int T);
    HMSTime(const HMSTime &hmstime);
    HMSTime(int hour, int minute, int second);
    operator int() const;
private:
    int H, M, S, t;
};

#endif // HMSTIME_H
