#include "qteditor.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QKeySequence>

// QMainWindow 클래스를 상속받은 QtEditor 클래스의 생성자에
// 메인 윈도우를 위한 메뉴바, 툴바, 독위젯 등을 정의해 사용
QtEditor::QtEditor(QWidget *parent) : QMainWindow(parent) {

    // QTextEdit을 생성자 윗부분에 추가
    QTextEdit *textedit = new QTextEdit(this);
    setCentralWidget(textedit); // 중앙 위젯 설정

    // QMenuBar 클래스의 인스턴스 생성 후
    // QMainWindow 클래스의 setMenuBar() 메소드를 호출해 설정
    QMenuBar * menubar = new QMenuBar(this);
    QMenuBar * formatMenu = new QMenuBar(this);
    setMenuBar(menubar);
    setMenuBar(formatMenu);

    // 메뉴, 툴바 등의 동작을 하나로 연결해 사용
    QAction *newAct = new QAction(QIcon("new.png"), "&New", this); // 아이콘 이미지를 Working Directory로 복사해야 한다!
    QAction *newOpen = new QAction("&Open", this);
    QAction *newSave = new QAction("&Save", this);
    QAction *newSaveAs = new QAction("&SaveAs", this);
    QAction *newPrint = new QAction("&Print", this);
    QAction *newQuit = new QAction("&Quit", this);

    QAction *alignLeft = new QAction("&Align", this);
    QAction *alignCenter = new QAction("&Save", this);
    QAction *alignRight = new QAction("&SaveAs", this);
    QAction *alignJustify = new QAction("&Print", this);

    newAct->setShortcut(QKeySequence::New); // 단축키 클래스 사용
    newOpen->setShortcut(QKeySequence::Open);
    newSave->setShortcut(QKeySequence::Save);
    newSaveAs->setShortcut(QKeySequence::SaveAs);
    newPrint->setShortcut(QKeySequence::Print);
    newQuit->setShortcut(QKeySequence::Quit);

    newAct->setStatusTip(tr("make new file"));
    newOpen->setStatusTip(tr("open file"));
    newSave->setStatusTip(tr("save this file"));
    newSaveAs->setStatusTip(tr("save this file as.."));
    newPrint->setStatusTip(tr("print file"));
    newQuit->setStatusTip(tr("quit"));

    connect(newAct, SIGNAL(triggered()), SLOT(newFile())); // SLOT newFile은 헤더에 정의해야 한다
    connect(newOpen, SIGNAL(triggered()), SLOT(newOpen()));
    connect(newSave, SIGNAL(triggered()), SLOT(newSave()));
    connect(newSaveAs, SIGNAL(triggered()), SLOT(newSaveAs()));
    connect(newPrint, SIGNAL(triggered()), SLOT(newPrint()));
    connect(newQuit, SIGNAL(triggered()), SLOT(newQuit()));

    // 기존의 메뉴에 addMenu() 메소드를 사용해 하위 메뉴 추가
    QMenu *fileMenu = menubar->addMenu("&File");
    QMenu *alignMenu = formatMenu->addMenu("&Align");

    fileMenu->addAction(newAct);
    fileMenu->addAction(newOpen);
    fileMenu->addAction(newSave);
    fileMenu->addAction(newSaveAs);
    fileMenu->addAction(newPrint);
    fileMenu->addAction(newQuit);

}

QtEditor::~QtEditor() {
}

void QtEditor::newFile() {
    qDebug("make new file");
}









































