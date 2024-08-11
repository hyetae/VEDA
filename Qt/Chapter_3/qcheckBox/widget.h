#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QCheckBox;
class QButtonGroup;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    // 체크박스 형태로 사용자로부터 복수 옵션을 동시에 입력받음
    // 여러 버튼을 하나로 묶어 사용 가능
    QCheckBox *cb[4];
    // QButtonGroup: 버튼 위젯들을 물리적으로 묶어 준다
    // QGroupBox: 버튼 위젯들을 시각적으로 묶어 준다
    QButtonGroup *bg;

    int cnt = 0;
    QLabel *label;

public slots:
    void selectButton(int id);
};
#endif // WIDGET_H
