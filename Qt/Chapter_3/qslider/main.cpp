#include <QApplication>
#include <QSlider>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 수직, 수평의 슬라이더 제공
    // 슬라이더의 비율로 범위 내의 값을 표시
    QSlider *slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    // 틱 표지로 눈금 설정
    slider->setTickPosition(QSlider::TicksAbove);
    // setStyle()로 다양한 스타일 적용 가능
    slider->setStyle(QStyleFactory::create("Fusion"));
    slider->show();

    return a.exec();
}
