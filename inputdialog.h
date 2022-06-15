#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGridLayout>

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputDialog(QWidget* parent, QString hint = "hint");
    static std::pair<QString, QString> getStrings(QString hint = "hint", QWidget *parent = nullptr, bool *ok = nullptr);
    QGridLayout *gridlayout;
    QFormLayout *lytMain;
    QLabel *tLabel, *tHint, *topLaybel;
    QLineEdit *tLine, *tCommand;
    QDialogButtonBox *buttonBox;
};

#endif // INPUTDIALOG_H
