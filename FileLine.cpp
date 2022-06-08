#include "FileLine.h"
bool iswindows()
{
#ifdef Q_OS_WINDOWS
    return true;
#else
    return false;
#endif
}

FileLine::FileLine(QWidget *parent):QLineEdit(parent)
{
    setAcceptDrops(true);
}
QString FileLine::getvalue()
{
    return Filepath;
}
bool FileLine::operator()(QString& name)
{
    QFileInfo file(name);
    if(file.isFile())
        return true;
    else
        return false;
}
void FileLine::dragEnterEvent(QDragEnterEvent* e)
{
    e->accept();
}
void FileLine::dropEvent(QDropEvent* e)
{
    QString path;
    if(iswindows())
        path=e->mimeData()->text().replace("file:///","");
    else
        path=e->mimeData()->text().replace("file://","");
    setText(path);
    Filepath=path;
}
