#include "ffoptions.h"

FFOptionsCheck::FFOptionsCheck(QWidget* parent)
:AbstructOption(CHECK, parent)
{

}
FFOptionsCheck::FFOptionsCheck(QString name, QString _command_checked, QString _command_unchecked, int def,  QWidget* parent):
    AbstructOption(CHECK, parent), command_checked(_command_checked), command_unchecked(_command_unchecked), name(name), state(def)
{
    init();
}

FFOptionsCheck::~FFOptionsCheck(){
    delete layout;
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
void FFOptionsCheck::init(){
    layout = new QHBoxLayout(this);
    box = new QCheckBox(name, this);
    layout->addWidget(box);
    if(state)
        box->setCheckState(Qt::Checked);
    else
        box->setCheckState(Qt::Unchecked);
    connect(box, &QCheckBox::stateChanged, this, &FFOptionsCheck::stateChanged);
}

int FFOptionsCheck::getCurrentState(){
    if(box->isChecked()) return 1;
    else return 0;
}
void FFOptionsCheck::read(const QJsonObject &json){
    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    if (json.contains("command_checked") && json["command_checked"].isString())
        command_checked = json["command_checked"].toString();

    if (json.contains("command_unchecked") && json["command_unchecked"].isString())
        command_checked = json["command_unchecked"].toString();

    if (json.contains("state") && json["state"].isBool()){
        bool s = json["state"].toBool();
        if(s){
            state = 1;
        }
        else{
            state = 0;
        }
    }
    init();
}
void FFOptionsCheck::write(QJsonObject &json){
    json["name"] = name;
    json["command_checked"] = command_checked;
    json["command_unchecked"] = command_unchecked;
    json["state"] = state == 1 ? true : false;
}


