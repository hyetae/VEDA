#include <QApplication>
#include <QLCDNumber>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // lcd 형태로 숫자와 관련된 문자 표시
    QLCDNumber *lcd = new QLCDNumber();
    // bin, dec, oct, hex 모드
    lcd->setBinMode();
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->display(4);
    // 숫자 개수 설정
    lcd->setDigitCount(15);
    lcd->show();

    return a.exec();
}
