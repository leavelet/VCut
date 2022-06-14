#include "ffoptions.h"
#include "inputdialog.h"

FFOptionsCombo::FFOptionsCombo(QString name, QString _base, QString _hint, QWidget* parent):
    AbstructOption(parent), baseCommand(_base), hint(_hint), sum(2)
{
    text = new QLabel(this);
    chooseList = new QComboBox(this);
    chooseList->addItem("自动");//0
    chooseList->addItem("自定义");//1
    commands.push_back(std::make_pair(false, ""));//0
    display_name.push_back("自动");
    display_name.push_back("自定义");

    chooseList->setCurrentIndex(0);
    layout = new QHBoxLayout(this);

    text->setText(name);

    layout->addWidget(text);
    layout->addWidget(chooseList);

    connect(chooseList, &QComboBox::currentIndexChanged, this, [this](){
        int cnt = chooseList->currentIndex();
        if( cnt == 1){
            addCustomItem();
            return;
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
