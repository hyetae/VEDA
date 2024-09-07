#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *label;
    QButtonGroup *btnGroup;
    QString num, op;
    bool isFirst;
    const qint32 W = 4;

public slots:
    void click(int id);
};
#endif // WIDGET_H
