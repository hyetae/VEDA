#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    // 슬롯은 일반적으로 void 반환
    void slotQuit();
};
#endif // WIDGET_H
