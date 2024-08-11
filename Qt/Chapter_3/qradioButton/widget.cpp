#include "widget.h"
#include <QRadioButton>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(140, 110);
    bg = new QButtonGroup(this);
    for (int i = 0; i < 4; i++) {
        QString str = QString("RadioButton%1").arg(i + 1);
        rb[i] = new QRadioButton(str, this);
        rb[i]->move(10, 10 + 20 * i);
        bg->addButton(rb[i]);
    }
}

Widget::~Widget() {}
