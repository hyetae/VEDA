#include "widget.h"

#include <QApplication>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("&Quit", this);
    quit->resize(75, 35);

    connect(quit, SIGNAL(clicked()), this, SLOT(slotQuit()));
}

void Widget::slotQuit() {
    qDebug("slotQuit");
    emit clicked(); // 시그널은 호출하는 게 아니라 emit 키워드로 발생시킨다
}

Widget::~Widget() {}
