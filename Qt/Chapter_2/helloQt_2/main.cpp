#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[])
{
    // QCoreApplication 클래스 상속 -> quit() 슬롯 사용
    QApplication a(argc, argv);

    // QAbstractButton 클래스 상속 -> clicked() 시그널 사용
    QPushButton quit("Quit", nullptr);
    quit.resize(75, 35);
    quit.show();

    // QObject::connect() 메소드로 QPushButton 위젯의 시그널과 QApplication 클래스의 슬롯 연결
    QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));

    return a.exec();
}
