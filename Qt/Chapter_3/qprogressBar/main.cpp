#include <QApplication>
#include <QProgressBar>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 전체 단계를 정의해 단계별로 진행 사항 표시
    // 수직이나 수평으로도 방향을 설정할 수 있다: setOrientation()
    QProgressBar *pb = new QProgressBar();

    /* STEP 1
    // 기본 범위는 0~100
    pb->setRange(0, 80);
    pb->setValue(20);
    */

    pb->show();

    // 타이머와 람다 함수를 함께 사용한 응용
    QTimer timer;
    int n = 0;
    QObject::connect(&timer, &QTimer::timeout,\
                     [&]{ pb->setValue(++n % 101); });

    timer.start(10);

    return a.exec();
}
