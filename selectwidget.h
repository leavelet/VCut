#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#endif // SELECTWIDGET_H
#include <QComboBox>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QResizeEvent>
#include <QFileDialog>
#include <QDialog>

#include "matchwidget.h"
class selectwidget:public QWidget
{
public:
    QComboBox* cb;
    QWidget *sunWidget;
    matchwidget* widget1;
    QPlainTextEdit* widget2;
    QGridLayout* thislayout;
    QPushButton* finish, *chooseRoot;
    QResizeEvent* sizeChangd;
    QString videoRoot;
    void resizeEvent(QResizeEvent *sizeChangd);
    selectwidget(QWidget* parent);
    ~selectwidget();
public slots:
    void checkcurrenttext();
    void import();
};
