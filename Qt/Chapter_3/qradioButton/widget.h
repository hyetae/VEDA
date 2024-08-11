#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QRadioButton;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    // 사용자로부터 복수의 옵션 중 하나만 선택할 때 사용
    // 여러 개의 라디오 버튼을 하나로 묶어서 사용
    QRadioButton *rb[4];
    // 여러 버튼 위젯들을 하나로 관리함
    // exclusive 속성으로 동작
    QButtonGroup *bg;
};
#endif // WIDGET_H
