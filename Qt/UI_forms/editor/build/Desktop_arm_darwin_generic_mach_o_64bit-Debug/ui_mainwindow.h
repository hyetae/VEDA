/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionQuit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionColor;
    QAction *actionFont;
    QAction *actionLeft;
    QAction *actionCenter;
    QAction *actionRight;
    QAction *actionJustify;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_Format;
    QMenu *menuAlign;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(550, 369);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName("actionSave_As");
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName("actionZoom_In");
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName("actionZoom_Out");
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName("actionColor");
        actionFont = new QAction(MainWindow);
        actionFont->setObjectName("actionFont");
        actionLeft = new QAction(MainWindow);
        actionLeft->setObjectName("actionLeft");
        actionCenter = new QAction(MainWindow);
        actionCenter->setObjectName("actionCenter");
        actionRight = new QAction(MainWindow);
        actionRight->setObjectName("actionRight");
        actionJustify = new QAction(MainWindow);
        actionJustify->setObjectName("actionJustify");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName("mdiArea");

        horizontalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 550, 24));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName("menu_File");
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName("menu_Edit");
        menu_Format = new QMenu(menubar);
        menu_Format->setObjectName("menu_Format");
        menuAlign = new QMenu(menu_Format);
        menuAlign->setObjectName("menuAlign");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menubar->addAction(menu_Format->menuAction());
        menu_File->addAction(actionNew);
        menu_File->addAction(actionOpen);
        menu_File->addAction(actionSave);
        menu_File->addAction(actionSave_As);
        menu_File->addSeparator();
        menu_File->addAction(actionPrint);
        menu_File->addSeparator();
        menu_File->addAction(actionQuit);
        menu_Edit->addAction(actionUndo);
        menu_Edit->addAction(actionRedo);
        menu_Edit->addSeparator();
        menu_Edit->addAction(actionCopy);
        menu_Edit->addAction(actionCut);
        menu_Edit->addAction(actionPaste);
        menu_Edit->addSeparator();
        menu_Edit->addAction(actionZoom_In);
        menu_Edit->addAction(actionZoom_Out);
        menu_Format->addAction(actionColor);
        menu_Format->addAction(actionFont);
        menu_Format->addAction(menuAlign->menuAction());
        menuAlign->addAction(actionLeft);
        menuAlign->addAction(actionCenter);
        menuAlign->addAction(actionRight);
        menuAlign->addAction(actionJustify);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        actionZoom_In->setText(QCoreApplication::translate("MainWindow", "Zoom In", nullptr));
        actionZoom_Out->setText(QCoreApplication::translate("MainWindow", "Zoom Out", nullptr));
        actionColor->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        actionFont->setText(QCoreApplication::translate("MainWindow", "Font", nullptr));
        actionLeft->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        actionCenter->setText(QCoreApplication::translate("MainWindow", "Center", nullptr));
        actionRight->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        actionJustify->setText(QCoreApplication::translate("MainWindow", "Justify", nullptr));
        menu_File->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menu_Edit->setTitle(QCoreApplication::translate("MainWindow", "&Edit", nullptr));
        menu_Format->setTitle(QCoreApplication::translate("MainWindow", "&Format", nullptr));
        menuAlign->setTitle(QCoreApplication::translate("MainWindow", "Align", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
