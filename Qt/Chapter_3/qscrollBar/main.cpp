#include <QApplication>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel *label = new QLabel("0123456789012345678901234567890123456789");
    // 위젯의 컨텐츠 영역보다 현재 보여지는 영역의 크기가 작은 경우에 스크롤바 사용
    // QTextEdit과 같이 QAbstractScrollArea 클래스를 상속받는 위젯에서 적용
    QScrollArea *sa = new QScrollArea;
    sa->setBackgroundRole(QPalette::Dark);
    sa->setWidget(label);
    sa->resize(60, 30);
    sa->show();

    // 마우스로 스크롤 바의 버튼을 클릭하거나 스크롤 바 중앙의 핸들을 이용해 값 설정
    QScrollBar *slider = sa->horizontalScrollBar();
    slider->setValue(slider->maximum());

    return a.exec();
}
