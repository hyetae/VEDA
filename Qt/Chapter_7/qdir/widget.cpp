#include "widget.h"
#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMenu>
#include <QContextMenuEvent>
#include <QApplication>

#include <QMessageBox>
#include <QTextStream>

#include <QProcess>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 경로명을 조작할 때 사용 (파일 경로에 대한 정보에 접근해 파일 시스템 조작)
    // 상대 경로나 절대 경로를 이용해서 파일 참조 가능 (디렉터리와 디렉터리 내 파일 목록에 대한 정보를 생성, 삭제 이동)
    directory = new QDir(".");

    // 메뉴를 위한 액션들을 정의
    QAction *mkdirAciton = new QAction("&Make Directory", this);
    connect(mkdirAciton, SIGNAL(triggered()), SLOT(makeDir()));


    QAction *copyAction = new QAction("&Copy", this);
    connect(copyAction, SIGNAL(triggered()), SLOT(copyFile()));

    QAction *removeAction = new QAction("&Re&move", this);
    connect(removeAction, SIGNAL(triggered()), SLOT(removeDir()));

    QAction *renameAction = new QAction("&Rename", this);
    connect(renameAction, SIGNAL(triggered()), SLOT(renameDir()));

    QAction *quitAction = new QAction("&Quit", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // 액션을 메뉴에 추가
    m_menu = new QMenu(this);
    m_menu->addSection("&QDirectory");
    m_menu->addAction(mkdirAciton);
    m_menu->addSeparator();
    m_menu->addSection("&File");
    m_menu->addAction(copyAction);
    m_menu->addAction(removeAction);
    m_menu->addAction(renameAction);
    m_menu->addSeparator();
    m_menu->addAction(quitAction);

    // 화면에 표시될 위젯들을 정의하고 레이아웃
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);

    QPushButton *actionButton = new QPushButton("Action", this);
    actionButton->setMenu(m_menu); // 팝업 메뉴 설정

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(actionButton);
    layout->addWidget(outputEdit);

    // 시그널과 슬롯을 연결
    connect(dirListWidget, SIGNAL(itemClicked(QListWidgetItem*)),\
            SLOT(selectItem(QListWIdgetItem*)));
    connect(dirListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),\
            SLOT(changeDir()));
    refreshDir(); // 현재 디렉터리 내용을 QListWidget에 표시
}

Widget::~Widget() {}

// 디렉터리 갱신
void Widget::refreshDir() {
    dirListWidget->clear(); // 현재 QListWidget의 내용 모두 삭제

    // QDir 클래스에 저장된 현재 파일의 목록을 QListWidget에 아이템으로 추가
    for (int index = 0; index < directory->entryList().count(); index++)
        dirListWidget->addItem(directory->entryList().at(index));
}

// 마우스 오른쪽 버튼을 누르면 컨텍스트 메뉴 표시
void Widget::selectItem(QListWidgetItem* item) {
    filenameLineEdit->setText(item->text());
}

// 파일 복사
void Widget::copyFile() {
    QString filename = directory->absoluteFilePath(
        dirListWidget->currentItem()->text());

    QFileInfo checkDir(filename);
    if (checkDir.isFile() && filenameLineEdit->text().length()) {
        QString newFile = directory->absoluteFilePath(filenameLineEdit->text());
        QFile::copy(filename, newFile); // 파일 복사, QFile static 메소드 사용
    }
    directory->refresh();
    refreshDir();
}

// QListWidget을 더블 클릭하면 호출
void Widget::changeDir() {
    // 현재 파일 경로를 절대 경로로 변경
    QString filename = directory->absoluteFilePath(
        dirListWidget->currentItem()->text());

    QFileInfo checkDir(filename); // QFileInfo 클래스로 파일 체크
    if (checkDir.isDir()) { // 디렉터리면 파일 이동 후 QListWidget 갱신
        directory->cd(filename);
        directory->refresh();
        refreshDir();
    } else if (checkDir.isExecutable()) {
        // 외부 어플리케이션을 실행시키고, 이 어플리케이션과 통신하기 위해 사용 -> QIODevice 클래스 상속
        // 경로가 포함된 어플리케이션의 이름과 어플리케이션의 명령 인수를 start() 인수로 전달
        QProcess cmd;
        QStringList arguments;
        cmd.start(filename, arguments);

        outputEdit->clear();
        if (!cmd.waitForStarted()) return; // 실행 완료 대기
        QByteArray result = cmd.readAllStandardOutput();
        outputEdit->append(result);
        if (!cmd.waitForFinished()) return; // 종료 완료 대기
        result = cmd.readAllStandardOutput();
        outputEdit->append(result);

    } else if (checkDir.isFile()) { // 파일 읽기
        if (checkDir.isReadable()) {
            QFile file(filename);
            file.open(QFile::ReadOnly);
            QTextStream in(&file);

            outputEdit->setWindowTitle(filename);
            outputEdit->clear();

            QString line;
            while (in.readLineInto(&line))
                outputEdit->append(line);

            file.close();
        } else QMessageBox::warning(this, "Error", "Can't Read this file");
    }
}

// 디렉터리 생성
void Widget::makeDir() {
    if (filenameLineEdit->text().length()) {
        directory->mkdir(filenameLineEdit->text());
        directory->refresh(); // QDir 클래스는 현재의 디렉터리 정보 캐싱
        refreshDir();
    }
}

// 디렉터리나 파일 삭제
void Widget::removeDir() {
    if (filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL) {
        QString filename = directory->absoluteFilePath(
            dirListWidget->currentItem()->text());

        QFileInfo checkDir(filename);

        if (checkDir.isDir()) // 디렉터리면 디렉터리 삭제
            directory->rmdir(filenameLineEdit->text());
        else if (checkDir.isFile()) // 파일이면 파일 삭제
            QFile::remove(filename);

        directory->refresh();
        refreshDir();
    }
}

// 디렉터리나 파일 이름 변경
void Widget::renameDir() {
    if (filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL) {
        directory->rename(dirListWidget->currentItem()->text(),
                          filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

// 컨텍스트 메뉴 오픈
void Widget::contextMenuEvent(QContextMenuEvent *event) {
    QWidget::contextMenuEvent(event);
    m_menu->exec(QCursor::pos());
}
