#include "ffmpegwidget.h"

ffmpegWidget::ffmpegWidget(QWidget *parent)
    : QWidget{parent}
{
    check = new FFOptionsCheck("abc", "no", "giao", 1, this);
    comb = new FFOptionsCombo("comb", "base2", "hddd", this);
    layout = new QHBoxLayout(this);
    layout->addWidget(check);
    layout->addWidget(comb);

}
