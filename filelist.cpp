/* first coded by hxz
 * edited by syh
*/

#include "filelist.h"
#include <QApplication>
#include <QClipboard>
#include "getfile.h"
Filelist::Filelist(QWidget* parent):QWidget(parent)
{
    label = new QLabel("文件队列", this);
    mergeOrSingle = new QCheckBox("合并影片", this);
    Qlist = new QListWidget(this);
    buttonRemove = new QPushButton("-",this);
    buttonUp=new QPushButton("↑",this);
    buttonDown=new QPushButton("↓",this);
    buttonClear=new QPushButton("clear",this);
    buttonCopy=new QPushButton("copy",this);
    Qlist->setSortingEnabled(false);

    connect(buttonRemove,&QPushButton::clicked,this,&Filelist::removebutton_clicked);
    connect(Qlist,&QListWidget::currentRowChanged,this,&Filelist::setconnect);
    connect(buttonClear,&QPushButton::clicked,this,&Filelist::clearbutton_clicked);
    connect(buttonCopy,&QPushButton::clicked,this,&Filelist::copybutton_clicked);

    topText = new QHBoxLayout();
    topText->addWidget(label);
    topText->addWidget(mergeOrSingle);

    buttonLayout=new QHBoxLayout();
    buttonLayout->addWidget(buttonUp);
    buttonLayout->addWidget(buttonDown);
    buttonLayout->addWidget(buttonRemove);
    buttonLayout->addWidget(buttonCopy);
    buttonLayout->addWidget(buttonClear);

    topLayout = new QGridLayout(this);
    topLayout->addLayout(topText, 0, 0, 1, 1);
    topLayout->addWidget(Qlist, 1, 0, 10, 1);
    topLayout->addLayout(buttonLayout,11,0,1,1);
}
void Filelist::addfile(FileStruct s)
{

    filelist.push_back(s);
    listiterator=filelist.end();
    QListWidgetItem* item_new=new QListWidgetItem(s.filename);
    item_new->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
    Qlist->addItem(item_new);
    Qlist->setCurrentRow(Qlist->count());
}
Filelist::~Filelist()
{
    delete buttonRemove;
    /*
    delete button2;
    button2=NULL;
    */
    delete buttonUp;
    delete buttonDown;
}
void Filelist::setconnect()
{
    int r=Qlist->currentRow();
    int cnt=Qlist->count();
    disconnect(buttonUp,0,this,0);
    disconnect(buttonDown,0,this,0);
    if(r>=0&&r<cnt)
    {
        if(r!=0)
        {
            buttonUp->setEnabled(true);
            connect(buttonUp,&QPushButton::clicked,this,&Filelist::upbutton_clicked);
        }
        else
        {
            buttonUp->setEnabled(false);
        }
        if(r!=cnt-1)
        {
            buttonDown->setEnabled(true);
            connect(buttonDown,&QPushButton::clicked,this,&Filelist::downbutton_clicked);
        }
        else
        {
            buttonDown->setEnabled(false);
        }
        listiterator=filelist.begin();
        for(int i=0;i<r;i++)
        {
            listiterator++;
        }
    }
    qDebug()<<(*listiterator).filename;
}
void Filelist::removebutton_clicked()
{
    int r=Qlist->currentRow();
    int cnt=Qlist->count();
    if(r>=0&&r<cnt)
    {
        delete Qlist->takeItem(r);
        filelist.erase(listiterator);
    }
    Qlist->setCurrentRow(cnt);
    if(!filelist.empty())
        listiterator=filelist.end();
}
/*
void Filelist::addbutton_clicked()
{
    int r=currentRow();
    int cnt=count();
    if(r>=0&&r<cnt)
    {
        QListWidgetItem* item_new=new QListWidgetItem("new file");
        insertItem(r+1,item_new);
        item_new->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
        this->editItem(item_new);
        setCurrentRow(r+1);
    }
}
*/

void Filelist::upbutton_clicked()
{
    int r=Qlist->currentRow();
    QListWidgetItem* this_item=Qlist->takeItem(r);
    QListWidgetItem* last_item=Qlist->takeItem(r-1);
    Qlist->insertItem(r-1,this_item);
    Qlist->insertItem(r,last_item);
    Qlist->setCurrentRow(r-1);
    FileStruct temp=(*listiterator);
    std::list<FileStruct>::iterator i=listiterator;
    listiterator++;
    (*i)=(*listiterator);
    (*listiterator)=temp;
}
void Filelist::downbutton_clicked()
{
    int r=Qlist->currentRow();
    QListWidgetItem* next_item=Qlist->takeItem(r+1);
    QListWidgetItem* this_item=Qlist->takeItem(r);
    Qlist->insertItem(r,next_item);
    Qlist->insertItem(r+1,this_item);
    Qlist->setCurrentRow(r+1);
    FileStruct temp=(*listiterator);
    std::list<FileStruct>::iterator i=listiterator;
    listiterator--;
    (*i)=(*listiterator);
    (*listiterator)=temp;
}
void Filelist::clearbutton_clicked()
{
    int cnt=Qlist->count();
    for(int i=0;i<cnt;i++)
    {
        delete Qlist->takeItem(0);
    }
    filelist.clear();
}
void Filelist::copybutton_clicked()
{
    int r=Qlist->currentRow();
    int cnt=Qlist->count();
    if(r>=0&&r<cnt)
    {
        QListWidgetItem* item_new=new QListWidgetItem(Qlist->item(r)->text());
        Qlist->insertItem(r+1,item_new);
        Qlist->setCurrentRow(r+1);
        FileStruct file=*listiterator;
        filelist.insert(listiterator,file);
    }
}
