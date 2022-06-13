#ifndef ABSTRUCTOPTION_H
#define ABSTRUCTOPTION_H

#include <QWidget>
#include <QString>

class AbstructOption: public QWidget{
    Q_OBJECT
public:
    AbstructOption(QWidget* parent=nullptr):QWidget(parent){

    }
    virtual QString getCommand() = 0;
    virtual QString setInside(int now = 0) = 0;
};

#endif // ABSTRUCTOPTION_H
