#include "widget.h"
#include <QStackedLayout>
#include <QDial>
#include <QLabel>
#include <QCalendarWidget>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial *dial = new QDial(this);
    dial->setRange(0, 2);

    QLabel *label = new QLabel("Stack 1", this);
    QCalendarWidget *calendar = new QCalendarWidget(this);
    QTextEdit *text = new QTextEdit("Stack 3", this);

    // 여러 겹의 레이어로 되어 있는 한 위치에 위젯을 배치할 때
    QStackedLayout *stacked = new QStackedLayout(this);
    stacked->addWidget(label);
    stacked->addWidget(calendar);
    stacked->addWidget(text);

    connect(dial, &QDial::valueChanged, // SIGNAL(valueChanged(int)),
            stacked, &QStackedLayout::setCurrentIndex); // SLOT(setCurrentIndex(int)

    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->addWidget(dial);
    hBox->addLayout(stacked);

    setLayout(hBox);
}

Widget::~Widget() {}
