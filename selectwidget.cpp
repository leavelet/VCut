#include "selectwidget.h"
#include <cmath>
#include <QMessageBox>
#include <QDir>

selectwidget::selectwidget(QWidget* parent):QWidget(parent)
{
    cb=new QComboBox(this);
    cb->addItem("数字匹配");
    cb->addItem("正则表达式");
    sunWidget = new QWidget(this);
    finish = new QPushButton("导入文件列表",this);
    chooseRoot = new QPushButton("选择文件目录", this);
    widget1=new matchwidget(sunWidget);
    widget2=new QPlainTextEdit(sunWidget);
    widget2->hide();
    videoRoot = "";
    thislayout=new QGridLayout(this);
    thislayout->addWidget(cb, 0, 0, 1, 1);
    thislayout->addWidget(chooseRoot, 0, 1, 1, 1);
    thislayout->addWidget(sunWidget, 1, 0, 8, 5);
    thislayout->addWidget(finish, 9, 1, 1, 2);
    connect(cb,&QComboBox::currentIndexChanged,this,&selectwidget::checkcurrenttext);
    connect(chooseRoot, &QPushButton::clicked, this, [&](){videoRoot = QFileDialog::getExistingDirectory(this,"选择视频文件夹","");});
    connect(finish, &QPushButton::clicked, this, &selectwidget::import);
}
selectwidget::~selectwidget()
{
    delete widget1;
    delete widget2;
    delete cb;
    delete thislayout;
}
void selectwidget::checkcurrenttext()
{
    if(cb->currentIndex() == 0)
    {
        widget1->show();
        widget2->hide();
    }
    else
    {
        widget2->show();
        widget1->hide();
    }
}

//syh, version 0, June 8
//aiming to solve problem of widget disappering, unsolved
//TODO
void selectwidget::resizeEvent(QResizeEvent* sizeChangd){
//    qDebug() << "size changed !" << Qt::endl;
    widget1->adjustSize();
    widget2->adjustSize();
}


//syh, version 1, June 8
//the slot for click import
void selectwidget::import(){
    bool valid = true;
    if(videoRoot == ""){
        QMessageBox::warning(this, "错误", "请先选择文件目录！");
        return;
    }
    QDir::setCurrent("videoRoot");
    if(cb->currentIndex() == 1){
        if(widget2->toPlainText().isEmpty()){
            valid = false;
        }


    }
    else{
        QString stable = widget1->lines[0]->text();
        QString subfix = widget1->lines[1]->text();
        QString from = widget1->lines[2]->text();
        QString to = widget1->lines[3]->text();
        bool withZero = true;
        if(from.isEmpty() || to.isEmpty() || subfix.isEmpty()){
            valid = false;
            goto empty;
        }
        if(from.length() != to.length()){
            withZero = false;
        }
        if(to[0] == '0' || from[0] == '0'){
            withZero = true;
        }
        for(int i = from.toInt(); i <= to.toInt(); i++){
            QString movable = "";
            if(withZero)
                for (int j = 1; j <= from.length() - std::ceil(std::log(i) / std::log(10) + 1); j++){
                    movable.push_back('0');
                }
            movable += QString::number(i);
            QString final = "";
            //末数字
            if(widget1->cb->currentIndex() == 0){
                final = QDir::cleanPath(stable + QDir::separator() + movable);
            }
            else{
                final = QDir::cleanPath(stable + QDir::separator() + movable);
            }
            if(subfix[0] != '.'){
                final.push_back('.');
            }
            final += subfix;
        }


    }
    empty:
    if(! valid){
            QMessageBox::warning(this, "错误", "没有填写完整，不能完成导入！");

    }
}
