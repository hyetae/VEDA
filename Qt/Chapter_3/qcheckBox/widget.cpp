#include "widget.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(140, 110);

    // 버튼을 묶어 하나의 슬롯으로 묶는 데에도 사용
    bg = new QButtonGroup(this);
    bg->setExclusive(false);
    connect(bg, SIGNAL(idClicked(int)), SLOT(selectButton(int)));

    for (int i = 0; i < 4; i++) {
        QString str = QString("RadioButton%1").arg(i + 1);
        cb[i] = new QCheckBox(str, this);
        cb[i]->move(10, 10 + 20 * i);
        // addButton()의 2번째 인자가 생략되면 -1이 기본값으로 사용됨
        // -> 27번 라인
        bg->addButton(cb[i], i);
    }

    label = new QLabel("Selected: 0", this);
    label->move(10, 90);
}

void Widget::selectButton(int id) {

    // 슬롯을 호출한 객체는 sender()로 접근
    // 형 변환을 통해 원래의 클래스로 변경
    QButtonGroup *bg = (QButtonGroup*)sender();
    QCheckBox *button = (QCheckBox*)bg->button(id);

    if (button->isChecked())
        this->cnt += 1;
    else this->cnt -= 1;

    label->setText(QString("Selected: %1").arg(cnt));

    qDebug("CheckBox%d is selected(%s)", id + 1,\
                                                    (button->isChecked()) ? "On" : "Off");
}

Widget::~Widget() {}
