/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *statusText;
    QListWidget *statusList;
    QListWidget *userList;

    void setupUi(QMainWindow *ServerClass)
    {
        if (ServerClass->objectName().isEmpty())
            ServerClass->setObjectName(QStringLiteral("ServerClass"));
        ServerClass->resize(451, 298);
        centralWidget = new QWidget(ServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 351, 281));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        statusText = new QLabel(layoutWidget);
        statusText->setObjectName(QStringLiteral("statusText"));

        verticalLayout->addWidget(statusText);

        statusList = new QListWidget(layoutWidget);
        statusList->setObjectName(QStringLiteral("statusList"));

        verticalLayout->addWidget(statusList);

        userList = new QListWidget(centralWidget);
        userList->setObjectName(QStringLiteral("userList"));
        userList->setGeometry(QRect(370, 30, 71, 261));
        ServerClass->setCentralWidget(centralWidget);

        retranslateUi(ServerClass);

        QMetaObject::connectSlotsByName(ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ServerClass)
    {
        ServerClass->setWindowTitle(QApplication::translate("ServerClass", "Server", 0));
        statusText->setText(QApplication::translate("ServerClass", "<Status>", 0));
    } // retranslateUi

};

namespace Ui {
    class ServerClass: public Ui_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
