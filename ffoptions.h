#ifndef FFOPTIONS_H
#define FFOPTIONS_H

#include "AbstructOption.h"
#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <vector>
#include <QMessageBox>
#include <QInputDialog>

using std::pair;
using std::vector;

class FFOptionsCombo : public AbstructOption
{
public:
    FFOptionsCombo(QString name, QString base, QString hint, QWidget* parent = nullptr);

    int sum;
    QString baseCommand, hint;
    QLabel* text;
    QComboBox* chooseList;
    QHBoxLayout* layout;

    vector<QString> display_name;
    vector<pair<bool, QString>> commands;


    virtual QString getCommand();
    virtual QString setInside(int now = 0);

    void addCustomItem();
    void addItem(bool fromBase, QString display, QString command);
};


class FFOptionsCheck : public AbstructOption
{
public:
    FFOptionsCheck(QString name, QString command_checked, QString command_unchecked, int st,  QWidget* parent = nullptr);
    QString command_checked, command_unchecked;
    QCheckBox* box;

    virtual QString getCommand();
    virtual QString setInside(int now = 0);
};

#endif // FFOPTIONS_H
