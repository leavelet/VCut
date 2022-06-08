#include "getfile.h"

getFile::getFile(QWidget *parent)
    : QWidget{parent}
{
    fl=new FileLine(this);
    pushbutton=new QPushButton("打开文件",this);
    layout=new QHBoxLayout(this);
    layout->addWidget(pushbutton);
    layout->addWidget(fl);
    connect(pushbutton,&QPushButton::clicked,this,&getFile::pushButton_clicked);
}
getFile::~getFile()
{
    delete layout;
}
void getFile::pushButton_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,tr("打开文件"),"");
    fl->setText(path);
    fl->Filepath=path;
    emit fileChanged();
}
