#include <QApplication>
#include <QFrame>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    // 프레임을 가지는 위젯의 기본 클래스
    // 다양한 스타일을 제공함
    QFrame *plainLine = new QFrame(&w);
    plainLine->setGeometry(QRect(0, 0, 270, 16));
    plainLine->setLineWidth(2);
    plainLine->setFrameStyle(QFrame::HLine | QFrame::Plain);

    QFrame *raisedLine = new QFrame(&w);
    raisedLine->setGeometry(QRect(0, 10, 270, 16));
    raisedLine->setLineWidth(2);
    raisedLine->setFrameStyle(QFrame::HLine | QFrame::Raised);

    QFrame *sunkenLine = new QFrame(&w);
    sunkenLine->setGeometry(QRect(0, 20, 270, 16));
    sunkenLine->setLineWidth(2);
    sunkenLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    w.show();
    return a.exec();
}
