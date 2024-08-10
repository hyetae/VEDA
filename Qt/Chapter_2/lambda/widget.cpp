#include "widget.h"

#include <QApplication>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("&Quit", this);
    quit->resize(75, 35);

    // 사용자 정의 슬롯 대신 람다 함수 처리 가능
    connect(quit, &QPushButton::clicked, [](){ qApp->quit(); });
}
Widget::~Widget() {}
