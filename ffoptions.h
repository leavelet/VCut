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

#include <set>

using std::pair;
using std::vector;

class FFOptionsCombo : public AbstructOption
{
public:
    FFOptionsCombo(QWidget* parent = nullptr);
    FFOptionsCombo(QString name, QString base, QString hint, QWidget* parent = nullptr);
    virtual ~FFOptionsCombo();

    int sum;
    QString name, baseCommand, hint;
    QLabel* text;
    QComboBox* chooseList;
    QHBoxLayout* layout;

    vector<QString> display_name;
    vector<pair<bool, QString>> commands;
    std::set<int> customAdd;

    virtual QString getCommand();
    virtual QString setInside(int now = 0);
    virtual int getCurrentState();
    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json);

    void addCustomItem();
    void addItem(bool fromBase, QString display, QString command);
    void init();
};


class FFOptionsCheck : public AbstructOption
{
    Q_OBJECT
public:
    FFOptionsCheck(QWidget* parent = nullptr);
    FFOptionsCheck(QString name, QString command_checked, QString command_unchecked, int st,  QWidget* parent = nullptr);
    virtual ~FFOptionsCheck();

    int state;
    QString name, command_checked, command_unchecked;
    QCheckBox* box;
    QHBoxLayout* layout;

    virtual QString getCommand();
    virtual QString setInside(int now = 0);
    virtual int getCurrentState();
    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json);
    void init();
};

#endif // FFOPTIONS_H
