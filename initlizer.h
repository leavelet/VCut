#ifndef INITLIZER_H
#define INITLIZER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QWizard>
///
/// \brief The Initlizer class
///
/// 用来开始的时候指导安装ffmpeg
///
///
class Initlizer:QObject
{
    Q_OBJECT
public:
    Initlizer();
};

#endif // INITLIZER_H
