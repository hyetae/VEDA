#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

class QLabel;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *label;
    QVector<QPushButton*> btns;
    QString num, op;
    bool isFirst;
    const qint32 W = 4;

public slots:
    void setNum();
    void setOp();
};
#endif // WIDGET_H
