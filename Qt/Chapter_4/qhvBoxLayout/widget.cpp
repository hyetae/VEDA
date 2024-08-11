#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *pb1 = new QPushButton();
    pb1->setText("Button1");
    QPushButton *pb2 = new QPushButton("Button2");
    QPushButton *pb3 = new QPushButton("Button3", this);

    /*
    // QHBoxLayout - 수평
    // 부모 위젯 또는 mainWidget()의 빈 영역을 분할해 자식 위젯 관리
    QHBoxLayout *hb = new QHBoxLayout;
    // 마진 설정
    hb->setContentsMargins(0, 0, 0, 0);
    hb->addWidget(pb1);
    hb->addWidget(pb2);
    hb->addWidget(pb3);
    setLayout(hb);
    */

    // QVBoxLayout - 수직
    // 위젯 추가 시 처음부터 부모를 지정하는 것이 좋음
    QVBoxLayout *vb = new QVBoxLayout(this); // -> setLayout();
    // 간격 설정
    vb->setSpacing(6);
    vb->addWidget(pb1);
    vb->addWidget(pb2);
    vb->addWidget(pb3);
}

Widget::~Widget() {}
