#include "ffoptions.h"
#include "inputdialog.h"

FFOptionsCombo::FFOptionsCombo(QWidget* parent):
    AbstructOption(COMBO, parent), sum(2)
{
}
FFOptionsCombo::FFOptionsCombo(QString name, QString _base, QString _hint, QWidget* parent):
    AbstructOption(COMBO, parent), baseCommand(_base), hint(_hint), sum(2), name(name)
{
    init();
}

FFOptionsCombo::~FFOptionsCombo(){
    delete layout;
}

void FFOptionsCombo::init(){
    text = new QLabel(this);
    chooseList = new QComboBox(this);
    chooseList->addItem("自动");//0
    chooseList->addItem("自定义");//1
    commands.push_back(std::make_pair(false, ""));//0
    commands.push_back(std::make_pair(false, ""));//1
    display_name.push_back("自动");
    display_name.push_back("自定义");

    chooseList->setCurrentIndex(0);
    layout = new QHBoxLayout(this);

    text->setText(name);

    layout->addWidget(text,1);
    layout->addWidget(chooseList,10);

    connect(chooseList, &QComboBox::currentIndexChanged, this, [this](){
        int cnt = chooseList->currentIndex();
        if( cnt == 1){
            addCustomItem();
            return;
        }
        else{
            emit stateChanged();
        }
    });
}

void FFOptionsCombo::addCustomItem(){
    bool ok;
    auto ans = InputDialog::getStrings(hint, this, &ok);
    if (ok && !ans.second.isEmpty()){
        if(ans.first.isEmpty()){
            QString tmp = QString("自定义方案%1").arg(customAdd.size()+1);
            display_name.push_back(tmp);

        }
        else{
            display_name.push_back(ans.first);
        }
        commands.push_back(std::make_pair(true, ans.second));
        chooseList->addItem(display_name[sum]);
        customAdd.insert(sum);
        chooseList->setCurrentIndex(sum);
        sum ++;
    }
}

void FFOptionsCombo::addItem(bool fromBase, QString display, QString command){
    sum++;
    display_name.push_back(display);
    commands.push_back(std::make_pair(fromBase, command));
    chooseList->addItem(display_name[sum-1]);
}

QString FFOptionsCombo::getCommand(){
    int now = chooseList->currentIndex();
    if(now <= 1) return "";
    else {
        if(commands[now].first){
            QString ret;
            if(baseCommand.endsWith('='))
                 ret = baseCommand + commands[now].second;
            else
                 ret = baseCommand + " " + commands[now].second;
            return ret;
        }
        else{
            QString ret = commands[now].second;
            return ret;
        }
    }
}

QString FFOptionsCombo::setInside(int x){
    if(x > sum) chooseList->setCurrentIndex(0);
    else chooseList->setCurrentIndex(x);
    return commands[x].second;
}

int FFOptionsCombo::getCurrentState(){
    return chooseList->currentIndex();
}

void FFOptionsCombo::read(const QJsonObject &json){
    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();
    if (json.contains("baseCommand") && json["baseCommand"].isString())
        baseCommand = json["baseCommand"].toString();
    if (json.contains("hint") && json["hint"].isString())
        hint = json["hint"].toString();
    //init();
    chooseList->clear();
    commands.clear();
    display_name.clear();
    sum=0;
    if (json.contains("commands") && json["commands"].isArray()) {
        QJsonArray optionArray = json["commands"].toArray();
        for (int Index = 0; Index < optionArray.size(); ++Index) {
            QJsonObject optionObject = optionArray[Index].toObject();
            if(    optionObject.contains("isBase") && optionObject["isBase"].isBool()
                && optionObject.contains("command") && optionObject["command"].isString()
                && optionObject.contains("display") && optionObject["display"].isString())
                addItem(optionObject["isBase"].toBool(), optionObject["display"].toString(), optionObject["command"].toString());
        }
    }
    if (json.contains("state") && json["state"].isDouble()){
        int s = json["state"].toInt();
        setInside(s);
    }
}
void FFOptionsCombo::write(QJsonObject &json){
    json["name"] = name;
    json["baseCommand"] = baseCommand;
    json["hint"] = hint;
    QJsonArray optionArray;
    for(int i = 0; i < sum; i++){
        QJsonObject item;
        item["display"] = display_name[i];
        item["isBase"] = commands[i].first;
        item["command"] = commands[i].second;
        optionArray.append(item);
    }
    json["state"]=getCurrentState();
    json["commands"] = optionArray;
}
