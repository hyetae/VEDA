#include "widget.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    // 레이블 추가
    // 부모로 Widget 클래스 설정
    QLabel *label = new QLabel("<font size=20>Hello, World!</font>", &w);
    label->setGeometry(10, 90, 75, 35);

    w.show();
    return a.exec();
}
