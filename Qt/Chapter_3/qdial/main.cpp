#include <QApplication>
#include <QDial>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 아날로그 다이얼과 같은 모양으로 범위를 원형으로 설정
    QDial *dial = new QDial();
    // 조정 범위를 340도 -> 360도
    dial->setWrapping(true);
    // notch: 다이얼에 구간을 알 수 있도록 하는 작은 표시
    dial->setNotchesVisible(true);
    dial->setNotchTarget(10);
    dial->show();

    return a.exec();
}
