#include <QApplication>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 한 줄로 된 문자열을 입력받을 때
    QLineEdit *lineEdit = new QLineEdit();
    // 입력받는 형태 지정
    lineEdit->setInputMask("000");
    lineEdit->setPlaceholderText("input the number");
    // echoMode: 입력 문자열을 출력하는 모드 (normal, noecho, password, passwordechoonedit)
    lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    lineEdit->show();

    return a.exec();
}
