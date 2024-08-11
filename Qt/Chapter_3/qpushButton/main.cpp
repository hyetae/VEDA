#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 가장 기본적인 입력 위젯
    // & 문자를 사용해 단축키 지정 가능 (macOS 불가)
    QPushButton *pb = new QPushButton("Push&Button", 0);
    // 토글 버튼으로 설정
    pb->setCheckable(true);
    QObject::connect(pb, &QPushButton::toggled,\
                     [&](bool flag){ qDebug() << "toggled"; if (!flag) a.quit(); });
    pb->show();
    return a.exec();
}
