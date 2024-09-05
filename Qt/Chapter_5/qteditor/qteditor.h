#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

// QMainWindow 클래스를 상속받는 사용자 정의 위젯을 정의
class QtEditor : public QMainWindow {
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots: // 슬롯 정의부
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void print();
    void quit();
};
#endif // QTEDITOR_H
