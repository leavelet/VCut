#include "selectwidget.h"

selectwidget::selectwidget(QWidget* parent):QWidget(parent)
{
    cb=new QComboBox(this);
    cb->addItem("选项1");
    cb->addItem("选项2");
    sunWidget = new QWidget(this);
    finish = new QPushButton("导入内容",this);
    widget1=new matchwidget(sunWidget);
    widget2=new QPlainTextEdit(sunWidget);
    widget2->hide();
    thislayout=new QGridLayout(this);
    thislayout->addWidget(cb, 0, 0, 1, 5);
    thislayout->addWidget(sunWidget, 1, 0, 8, 5);
    thislayout->addWidget(finish, 9, 1, 1, 2);
    connect(cb,&QComboBox::currentIndexChanged,this,&selectwidget::checkcurrenttext);
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
