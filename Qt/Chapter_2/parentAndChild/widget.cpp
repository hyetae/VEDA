#include "widget.h"

#include <QApplication>
#include <QPushButton>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 레이블 함께 배치
    QPushButton *quit = new QPushButton("Quit", this);
    quit->setGeometry(10, 10, 75, 35);

    QLabel *label = new QLabel("<font color=blue>Hello Qt!</font>", this);
    label->setGeometry(10, 50, 75, 35);

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Widget::~Widget() {}
