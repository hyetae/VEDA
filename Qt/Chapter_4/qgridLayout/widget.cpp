#include "widget.h"
#include <QGridLayout>
#include <QPushButton>
#define ROW 3

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 위젯을 격자로 정렬 시 사용
    // 기준점 = 0, 0
    QGridLayout *gl = new QGridLayout;
    QPushButton *pb[ROW * ROW];

    for (int y = 0; y < ROW; y++) {
        for (int x = 0; x < ROW; x++) {
            int p = x + y * ROW;
            QString str = QString("Button%1").arg(p + 1);
            pb[p] = new QPushButton(str, this);
            // x, y 값이 반대로 들어간다
            gl->addWidget(pb[p], x, y);
        }
    }
    setLayout(gl);
}

Widget::~Widget() {}
