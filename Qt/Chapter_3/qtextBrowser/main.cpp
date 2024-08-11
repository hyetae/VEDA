#include <QApplication>
#include <QTextBrowser>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QTextEdit 클래스를 상속한다
    // 하이퍼텍스트를 표시할 때 사용한다
    // HTML 태그를 그대로 표시하려면 setPainText() 사용
    QTextBrowser *tb = new QTextBrowser();
    tb->setSource(QUrl("./index.html"));
    tb->show();

    return a.exec();
}
