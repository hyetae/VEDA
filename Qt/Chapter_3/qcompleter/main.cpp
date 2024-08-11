#include <QApplication>
#include <QLineEdit>
#include <QCompleter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineEdit *lineEdit = new QLineEdit();
    QStringList CompletionList;
    CompletionList << "Apple" << "Banana" << "cat" << "dog";

    // 자동 완성을 위한 목록 제공
    QCompleter *stringCompleter = new QCompleter(CompletionList, lineEdit);
    // 대소문자 구분
    stringCompleter->setCaseSensitivity(Qt::CaseSensitive);
    lineEdit->setCompleter(stringCompleter);
    lineEdit->show();

    return a.exec();
}
