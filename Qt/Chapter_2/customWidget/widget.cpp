#include "widget.h"

// qApp은 QApplication 클래스의 전역 인스턴스 → 헤더 파일 필요
#include <QApplication>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 사용자 정의 위젯에 위젯을 배치하기 위해서는 부모로 현재의 위젯(this)을 설정
    QPushButton *quit = new QPushButton("Quit", this);
    quit->resize(75, 35);

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Widget::~Widget() {}
