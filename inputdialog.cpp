#include "inputdialog.h"

InputDialog::InputDialog(QWidget* parent, QString hint) : QDialog(parent)
{
    gridlayout = new QGridLayout(this);
    lytMain = new QFormLayout();
    topLaybel = new QLabel("添加自定义方案");

    gridlayout->addWidget(topLaybel);
    gridlayout->addLayout(lytMain, 1, 0, 2, 2);

    tLabel = new QLabel("方案名", this);
    tLine = new QLineEdit(this);
    lytMain->addRow(tLabel, tLine);

    tHint = new QLabel(hint, this);
    tCommand = new QLineEdit(this);
    lytMain->addRow(tHint, tCommand);

    buttonBox = new QDialogButtonBox
        ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
         Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                        this, &InputDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &InputDialog::reject);
    Q_ASSERT(conn);

    setLayout(lytMain);
}

std::pair<QString, QString> InputDialog::getStrings(QString hint, QWidget *parent, bool *ok)
{
    InputDialog *dialog = new InputDialog(parent, hint);
    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;
    std::pair<QString, QString> pa;
    if(ret){
        pa = std::make_pair(dialog->tLine->text(), dialog->tCommand->text());
    }
    else{
        pa = std::make_pair("", "");

    }
    delete dialog;
    return pa;
}
