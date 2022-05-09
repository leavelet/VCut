#ifndef INFOLINE_H
#define INFOLINE_H

#include <QObject>
#include <QWidget>
///
/// \brief The InfoLine class
///
/// 一个文字+一个lineEdit，返回一个数字
///
/// 初始化的时候确定返回值种类
///
/// getValue()方法返回具体值
///

///
/// \brief The VALUEBACK enum
///
///种类 vcutInt 整数， vcutDouble 浮点数， 用模板实现
///
enum VALUEBACK{VcutInt, VcutDouble};

template<typename T>
class valueType{

};

class InfoLine:QObject
{
    Q_OBJECT
public:
    InfoLine();
};

#endif // INFOLINE_H
