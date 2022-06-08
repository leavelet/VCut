#ifndef MATCHWIDGET_H
#define MATCHWIDGET_H

#endif // MATCHWIDGET_H
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
class matchwidget:public QWidget
{
public:
    QComboBox* cb;
    QGridLayout* thislayout;
    QLabel* labels[4];
    QLineEdit* lines[4];
    matchwidget(QWidget* parent);
    ~matchwidget();
public slots:
    void checkcurrenttext();
};
