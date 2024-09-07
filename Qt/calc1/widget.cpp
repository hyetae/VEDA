#include "widget.h"

#include <QLabel>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent), isFirst(true)
{
    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setGeometry(10, 5, 230, 40);

    const char BtnChar[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    // 계산, 연산 버튼
    const char* methods[16] = {
        SLOT(setNum()), SLOT(setNum()), SLOT(setNum()), SLOT(setOp()),
        SLOT(setNum()), SLOT(setNum()), SLOT(setNum()), SLOT(setOp()),
        SLOT(setNum()), SLOT(setNum()), SLOT(setNum()), SLOT(setOp()),
        SLOT(setNum()), SLOT(), SLOT(), SLOT(setOp()),
    };

    for (int y = 0; y < W; y++)
        for (int x = 0; x < W; x++) {
            int n = x + y * W;
            btns.append(new QPushButton(BtnChar[n], this));
            btns.at(n)->setGeometry(5 + 60 *  x, 50 + 60 * y, 60, 60);
            if (n != 12 && n != 14)
                connect(btns.at(n), SIGNAL(clicked()), methods[n]);
    }

    // 초기화 버튼
    connect(btns.at(12), &QPushButton::clicked, this, [=](){label->setText("0");});

    // 계산 버튼
    connect(btns.at(14), &QPushButton::clicked, this, [this](){
        qreal result = 0;
        isFirst = true;
        switch (op.at(0).toLatin1()) {
        case '+':
            result = num.toDouble() + label->text().toDouble();
            break;
        case '-':
            result = num.toDouble() - label->text().toDouble();
            break;
        case 'x':
            result = num.toDouble() * label->text().toDouble();
            break;
        case '/':
            if (label->text().toDouble())
                result = num.toDouble() / label->text().toDouble();
            else {
                label->setText("Error: Cannot Divide by Zero");
                return;
            }
            break;
        }
        label->setText(QString::number(result));
    });

    setMinimumSize(250, 295);
    setMaximumSize(250, 295);
    setWindowTitle("Calculator");

}

Widget::~Widget() {
    delete label;
    btns.clear();
}

void Widget::setNum() {
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());
    QString str1;


    if (btn != nullptr)
        str1 = btn->text();

    if (label != nullptr) {
        QString str2 = label->text();
#if 1
        label->setText((str2 == "0" | isFirst) ? str1 : str2 + str1);
#else
        label->setText(QString::number(str2.toDouble() * 10 + str1.toDouble()));
#endif
        isFirst = false;
    }
}

void Widget::setOp() {
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    if (btn != nullptr)
        op = btn->text();

    if (label != nullptr) {
        num = label->text();
        isFirst = true;
    }
}
