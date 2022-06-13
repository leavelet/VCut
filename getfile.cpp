#include "getfile.h"
#include <QFileInfo>
#include <QMessageBox>

getFile::getFile(QWidget *parent)
    : QWidget{parent}
{
    fl=new FileLine(this);
    pushbutton=new QPushButton("打开文件",this);
    layout=new QHBoxLayout(this);
    layout->addWidget(pushbutton);
    layout->addWidget(fl);
    connect(pushbutton,&QPushButton::clicked,this,&getFile::pushButton_clicked);
    connect(fl,&QLineEdit::returnPressed,this,&getFile::editFinish);
    connect(fl,&FileLine::changed,this,&getFile::fileChanged);
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
void getFile::editFinish()
{
    QString name=fl->text();
    QFileInfo inputFile(name);
    if(inputFile.isFile())
    {
        fl->Filepath=name;
        emit fileChanged();
    }
    else
    {
        QMessageBox::warning(this,"Error","Please input a valid file.");
    }
}
