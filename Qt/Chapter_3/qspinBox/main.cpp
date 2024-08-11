#include <QApplication>
#include <QSpinBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 숫자를 입력받을 때 사용
    // 최댓값과 최솟값 설정 가능, 기본값: 0~99
    // 실수값은 QDoubleSpinBox
    QSpinBox *spinBox = new QSpinBox();
    spinBox->setRange(0, 10);
    spinBox->setSuffix("%");
    spinBox->setWrapping(true);
    spinBox->setSpecialValueText("Percent");
    spinBox->show();

    return a.exec();
}
