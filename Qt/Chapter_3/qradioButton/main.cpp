#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 헤더 파일 참고
    Widget w;
    w.show();
    return a.exec();
}
