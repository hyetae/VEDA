#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent), isFirst(true)
{
    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setFrameShape(QFrame::Box);
    label->setMaximumHeight(30);

    const char BtnChar[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    btnGroup = new QButtonGroup(this);
    QGridLayout *gLayout = new QGridLayout();
    connect(btnGroup, SIGNAL(idClicked(int)), SLOT(click(int)));
    for (int y = 0; y < W; y++)
        for (int x = 0; x < W; x++) {
            int n = x + y * W;
            btnGroup->addButton(new QPushButton(BtnChar[n], this), n);
            gLayout->addWidget(btnGroup->button(n), n / W, n % W);
    }

    setWindowTitle("Calculator");

    QVBoxLayout *vbLayout = new QVBoxLayout(this);
    vbLayout->setContentsMargins(1, 1, 1, 1);
    vbLayout->addWidget(label);
    vbLayout->addLayout(gLayout);
    setLayout(vbLayout);
}

Widget::~Widget() {
    delete label;
    Q_FOREACH(auto b, btnGroup->buttons()) delete b;
}

void Widget::click(int id) {
    QPushButton *btn = dynamic_cast<QPushButton*>(btnGroup->button(id));
    QString str1;

    if (btn != nullptr)
        str1 = btn->text();

    switch (id) {
    case 0: case 1: case 2:
    case 4: case 5: case 6:
    case 8: case 9: case 10: case 13:
        // 숫자 버튼 클릭 시 처리
        if (label != nullptr) {
            QString str2 = label->text();
            label->setText((str2 == "0" || isFirst) ? str1 : str2 + str1);
            isFirst = false;
        }
        break;
    case 3: case 7: case 11: case 15:
        // 연산자 버튼 클릭 시 처리
        if (label != nullptr) {
            num = label->text();  // 첫 번째 숫자를 저장
            op = str1;            // 연산자를 저장
            isFirst = true;        // 다음 입력을 새로운 숫자로 처리
        }
        break;
    case 12:
        // 'C' (초기화) 버튼 처리
        label->setText("0");
        num.clear();
        op.clear();
        isFirst = true;
        break;
    case 14:
        // '=' (계산) 버튼 처리
        if (!op.isEmpty() && !num.isEmpty()) {
            qreal result = 0;
            qreal secondNum = label->text().toDouble();
            qreal firstNum = num.toDouble();

            if (op == "+")
                result = firstNum + secondNum;
            else if (op == "-")
                result = firstNum - secondNum;
            else if (op == "x")
                result = firstNum * secondNum;
            else if (op == "/") {
                if (secondNum != 0)
                    result = firstNum / secondNum;
                else {
                    label->setText("Error: Cannot Divide by Zero");
                    return;
                }
            }
            label->setText(QString::number(result));
            num.clear();  // 계산 후 값을 초기화
            op.clear();
            isFirst = true;
        }
        break;
    }
}
