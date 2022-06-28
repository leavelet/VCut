#ifndef ABSTRUCTOPTION_H
#define ABSTRUCTOPTION_H

#include <QWidget>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

enum optionKind{COMBO, CHECK};

class AbstructOption: public QWidget{
    Q_OBJECT
public:
    QJsonObject obj;
    int kind;
    AbstructOption(int kind, QWidget* parent=nullptr):QWidget(parent){

    }
    virtual QString getCommand() = 0;
    virtual QString setInside(int now = 0) = 0;
    virtual int getCurrentState() = 0;
    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) = 0;
};

#endif // ABSTRUCTOPTION_H
