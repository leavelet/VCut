#include "matchwidget.h"

matchwidget::matchwidget(QWidget* parent):QWidget(parent)
{
    cb=new QComboBox(this);
    cb->addItem("首数字");
    cb->addItem("末数字");
    labels[0]=new QLabel("不变动部分",this);
    labels[1]=new QLabel("后缀名",this);
    labels[2]=new QLabel("从",this);
    labels[3]=new QLabel("到",this);
    lines[0]=new QLineEdit(this);
    lines[1]=new QLineEdit(this);
    lines[2]=new QLineEdit(this);
    lines[3]=new QLineEdit(this);
    thislayout=new QGridLayout(this);
    thislayout->addWidget(cb,0,0,1,1);
    thislayout->addWidget(labels[0],1,0,1,1);
    thislayout->addWidget(labels[1],2,0,1,1);
    thislayout->addWidget(labels[2],3,0,1,1);
    thislayout->addWidget(labels[3],4,0,1,1);
    thislayout->addWidget(lines[0],1,1,1,1);
    thislayout->addWidget(lines[1],2,1,1,1);
    thislayout->addWidget(lines[2],3,1,1,1);
    thislayout->addWidget(lines[3],4,1,1,1);
    connect(cb,&QComboBox::currentTextChanged,this,&matchwidget::checkcurrenttext);
}
matchwidget::~matchwidget()
{
    delete cb;
    for(int i=0;i<4;i++)
    {
        delete lines[i];
        delete labels[i];
    }
    delete thislayout;
}
void matchwidget::checkcurrenttext()
{
    if(cb->currentText()=="首数字")
    {
        //flag=1;//首数字时的操作
    }
    else
    {
        //flag=0;//末数字时的操作
    }
}
