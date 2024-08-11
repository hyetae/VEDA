#include "widget.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QStringList labels;
    labels << "&IP Address" << "&Mac Address" << "&Date";
    QLineEdit* lineEdit[3];
    QFormLayout *formLayout = new QFormLayout;
    for(int i = 0; i < 3; i++) {
        lineEdit[i] = new QLineEdit(this);
        formLayout->addRow(labels.at(i), lineEdit[i]);
    }

    // 타이틀과 단축키가 있는 그룹 박스
    // 타이틀: 그룹 박스 위쪽
    // 단축키: 그룹 박스 내 자식 위젯으로 포커스 이동 시
    QGroupBox *groupBox = new QGroupBox("&Widget Group", this);
    groupBox->move(5, 5);
    groupBox->setLayout(formLayout);
    resize(groupBox->sizeHint( ).width()+10,
           groupBox->sizeHint().height()+10);
}

Widget::~Widget() {}
