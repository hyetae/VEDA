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

    for (int y = 0; y < W; y++)
        for (int x = 0; x < W; x++) {
            btns.append(new QPushButton(BtnChar[x + y * W], this));
            btns.at(x + y * W)->setGeometry(5 + 60 *  x, 50 + 60 * y, 60, 60);
        }

    // 숫자 버튼
    connect(btns.at(0), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(1), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(2), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(4), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(5), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(6), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(8), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(9), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(10), SIGNAL(clicked()), SLOT(setNum()));
    connect(btns.at(13), SIGNAL(clicked()), SLOT(setNum()));

    // 초기화 버튼
    connect(btns.at(12), &QPushButton::clicked, this, [=](){label->setText("0");});

    // 연산자 버튼
    connect(btns.at(3), SIGNAL(clicked()), SLOT(setOp()));
    connect(btns.at(7), SIGNAL(clicked()), SLOT(setOp()));
    connect(btns.at(11), SIGNAL(clicked()), SLOT(setOp()));
    connect(btns.at(15), SIGNAL(clicked()), SLOT(setOp()));

    // 계산 버튼
    connect(btns.at(14), &QPushButton::clicked, this, [this](){
        qreal result = 0;
        isFirst = true;
        if (op == '+')
            result = num.toDouble() + label->text().toDouble();
        else if (op == '-')
            result = num.toDouble() - label->text().toDouble();
        else if (op == 'x')
            result = num.toDouble() * label->text().toDouble();
        else if (op == '/') {
            if (label->text().toDouble())
                result = num.toDouble() / label->text().toDouble();
            else {
                label->setText("Error: Cannot Divide by Zero");
                return;
            }
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
        label->setText((str2 == "0" | isFirst) ? str1 : str2 + str1);
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
