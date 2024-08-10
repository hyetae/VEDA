#include "widget.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QWideget을 윈도우로 사용
    QWidget w;

    // 부모 = w(QWideget)
    QLabel hello("<font color=blue>Hello <i>Qt!</i><font>", &w);
    hello.resize(75, 35);

    // 부모 = w(QWideget)
    QPushButton quit("Quit", &w);
    quit.move(10,40);
    quit.resize(75,35);

    QObject::connect(&quit, &QPushButton::clicked, &hello, [&](){ hello.setText("<b>Hi</>");});

    w.show();
    return a.exec();
}
