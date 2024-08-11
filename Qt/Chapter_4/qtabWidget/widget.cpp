#include "widget.h"
#include <QTabWidget>
#include <QDial>
#include <QCalendarWidget>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial *dial = new QDial(this);
    QCalendarWidget *calendar = new QCalendarWidget(this);
    QTextEdit *text = new QTextEdit("Tab 3", this);

    // 탭이 있는 스택된 페이지 영역 제공
    // 한번에 하나의 페이지 영역만 볼 수 있음
    QTabWidget *tab = new QTabWidget(this);

    // 탭 바에 표시되는 타이틀로 구분
    tab->addTab(dial, "Tab &1");
    tab->addTab(calendar, "Tab &2");
    tab->addTab(text, "Tab &3");

    resize(tab->sizeHint());
}

Widget::~Widget() {}
