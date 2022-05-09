#ifndef BATCH_H
#define BATCH_H

#include <QObject>
#include <QWidget>

#include "ffmpegcontroller.h"
#include "regex.h"
#include "videoplayer.h"

///
/// \brief The batch class
///
/// 批处理的有关上层代码
///
///
class batch:QWidget
{
    Q_OBJECT
public:
    batch();
};

#endif // BATCH_H
