/********************************************************************************
** Form generated from reading UI file 'morphing.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MORPHING_H
#define UI_MORPHING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_morphing
{
public:
    QWidget *centralWidget;
    QLabel *img_source;
    QLabel *img_dest;
    QPushButton *btn_browse;
    QPushButton *btn_process;
    QPushButton *btn_browse_2;
    QLabel *img_result;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *morphing)
    {
        if (morphing->objectName().isEmpty())
            morphing->setObjectName(QStringLiteral("morphing"));
        morphing->resize(1520, 828);
        centralWidget = new QWidget(morphing);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        img_source = new QLabel(centralWidget);
        img_source->setObjectName(QStringLiteral("img_source"));
        img_source->setGeometry(QRect(0, -10, 500, 500));
        img_dest = new QLabel(centralWidget);
        img_dest->setObjectName(QStringLiteral("img_dest"));
        img_dest->setGeometry(QRect(520, -10, 500, 500));
        btn_browse = new QPushButton(centralWidget);
        btn_browse->setObjectName(QStringLiteral("btn_browse"));
        btn_browse->setGeometry(QRect(30, 640, 98, 27));
        btn_process = new QPushButton(centralWidget);
        btn_process->setObjectName(QStringLiteral("btn_process"));
        btn_process->setGeometry(QRect(150, 640, 98, 27));
        btn_browse_2 = new QPushButton(centralWidget);
        btn_browse_2->setObjectName(QStringLiteral("btn_browse_2"));
        btn_browse_2->setGeometry(QRect(270, 640, 99, 27));
        img_result = new QLabel(centralWidget);
        img_result->setObjectName(QStringLiteral("img_result"));
        img_result->setGeometry(QRect(1020, -10, 500, 500));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(400, 640, 99, 27));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(530, 640, 99, 27));
        morphing->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(morphing);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1520, 25));
        morphing->setMenuBar(menuBar);
        mainToolBar = new QToolBar(morphing);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        morphing->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(morphing);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        morphing->setStatusBar(statusBar);

        retranslateUi(morphing);

        QMetaObject::connectSlotsByName(morphing);
    } // setupUi

    void retranslateUi(QMainWindow *morphing)
    {
        morphing->setWindowTitle(QApplication::translate("morphing", "morphing", 0));
        img_source->setText(QString());
        img_dest->setText(QString());
        btn_browse->setText(QApplication::translate("morphing", "Browse", 0));
        btn_process->setText(QApplication::translate("morphing", "Process", 0));
        btn_browse_2->setText(QApplication::translate("morphing", "Browse", 0));
        img_result->setText(QString());
        pushButton_2->setText(QApplication::translate("morphing", "PushButton", 0));
        pushButton->setText(QApplication::translate("morphing", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class morphing: public Ui_morphing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MORPHING_H
