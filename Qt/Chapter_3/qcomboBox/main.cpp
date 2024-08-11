#include <QApplication>
#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 여러 옵션 중 하나를 선택할 때
    // 드롭 다운 리스트와 작은 버튼 제공
    QComboBox *comboBox = new QComboBox();
    comboBox->addItem("Apple");
    comboBox->addItem("Banana");
    comboBox->addItem("Cat");
    comboBox->addItem("Dog");
    // 옵션 추가 입력 가
    comboBox->setEditable(true);
    comboBox->show();

    return a.exec();
}
