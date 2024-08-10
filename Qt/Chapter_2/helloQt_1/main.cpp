#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    // QApplication 클래스의 인스턴스 a 생성 → GUI 객체 생성
    // 어플리케이션의 초기화와 이벤트 루프 등을 담당
    // QApplication 객체 생성 → GUI 객체 생성
    // Qt 어플리케이션은 QApplication 클래스의 객체가 반드시 필요
    QApplication a(argc, argv);

    // 첫 번째 인자에는 객체에 적절한 값을 넘기고, 두 번째 인자에는 해당 객체가 들어가야 할 부모 위젯을 설정
    // 자식 위젯은 부모 위젯의 공간에 표시됨, 별도의 창으로 열고자 할 때는 0, nullptr 사용
    // Rich text: QLabel 위젯에 HTML 태그를 이용해 서식 지정
    QLabel hello("<font color=blue>Hello <i>Qt!</i></font>", 0);

    hello.resize(75, 35); // reisize() 메소드로 크기 조정

    hello.show();
    return a.exec();
}
