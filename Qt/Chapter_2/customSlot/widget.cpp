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

// 사용자 정의 슬롯은 구현 필요
void Widget::slotQuit() {
    qDebug("slotQuit");
    qApp->quit(); // QMetaOBject::invokeMethod(qApp, "quit");
}

Widget::~Widget() {}
