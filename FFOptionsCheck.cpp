#include "ffoptions.h"

FFOptionsCheck::FFOptionsCheck(QString name, QString _command_checked, QString _command_unchecked, int def,  QWidget* parent):
    AbstructOption(parent), command_checked(_command_checked), command_unchecked(_command_unchecked)
{
    box = new QCheckBox(name, this);
    if(def)
        box->setCheckState(Qt::Checked);
    else
        box->setCheckState(Qt::Unchecked);
}

QString FFOptionsCheck::getCommand(){
    if(box->checkState()==Qt::Checked){
        return command_checked;
    }
    else{
        return command_unchecked;
    }
}

QString FFOptionsCheck::setInside(int st){
    if(st != 0 && st != 1){
        box->setCheckState(Qt::Unchecked);
        return command_unchecked;
    }
    if(st){
        box->setCheckState(Qt::Checked);
        return command_checked;
    }
    else{
        box->setCheckState(Qt::Unchecked);
        return command_unchecked;
    }
}
