#include "ffoptions.h"

FFOptionsCombo::FFOptionsCombo(QString name, QString _base, QString _hint, QWidget* parent):
    AbstructOption(parent), baseCommand(_base), hint(_hint), sum(1)
{
    text = new QLabel(this);
    chooseList = new QComboBox(this);
    chooseList->addItem("自动");//0
    chooseList->addItem("自定义");//1
    commands.push_back(std::make_pair(false, ""));//0


    chooseList->setCurrentIndex(0);
    layout = new QHBoxLayout(this);

    text->setText(name);

    layout->addWidget(text);
    layout->addWidget(chooseList);

    connect(chooseList, &QComboBox::currentIndexChanged, this, [this](){
        if(chooseList->currentIndex() == 1){
            addCustomItem();
        }
    });
}

void FFOptionsCombo::addCustomItem(){
    bool ok;QString text;
    text = QInputDialog::getText(this, "输入自定义命令", hint, QLineEdit::Normal, text, &ok);
    if (ok && !text.isEmpty()){
        display_name.push_back("点击改名");
        commands.push_back(std::make_pair(true, text));
        sum++;
        chooseList->addItem("点击改名");
    }
}

void FFOptionsCombo::addItem(bool fromBase, QString display, QString command){
    sum++;
    display_name.push_back(display);
    commands.push_back(std::make_pair(fromBase, command));
    sum++;
    chooseList->addItem(display_name[sum-1]);
    chooseList->setCurrentIndex(sum-1);
}

QString FFOptionsCombo::getCommand(){
    int now = chooseList->currentIndex();
    if(now <= 1) return "";
    else {
        if(commands[now].first){
            return baseCommand + " " + commands[now].second;
        }
        else{
            return commands[now].second;
        }
    }
}

QString FFOptionsCombo::setInside(int x){
    if(x > sum) chooseList->setCurrentIndex(0);
    else chooseList->setCurrentIndex(x);
    return commands[x].second;
}
