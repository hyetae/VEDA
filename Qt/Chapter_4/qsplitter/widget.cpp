#include "widget.h"
#include <QSplitter>
#include <QLabel>
#include <QDial>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label = new QLabel("&Value", this);
    QDial *dial1 = new QDial(this);
    QDial *dial2 = new QDial(this);
    label->setBuddy(dial2);

    // 위젯들의 크기를 동적으로 조정
    // 핸들을 마우스로 드래그함
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(label);
    splitter->addWidget(dial1);
    splitter->addWidget(dial2);

    resize(splitter->sizeHint());
}

Widget::~Widget() {}
