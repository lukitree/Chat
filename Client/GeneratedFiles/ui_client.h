/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionClear_Chat;
    QWidget *centralWidget;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QListWidget *messageList;
    QLineEdit *messageEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QListWidget *userList;
    QPushButton *sendButton;
    QMenuBar *menuBar;
    QMenu *menuConnect;
    QMenu *menuChat;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QStringLiteral("ClientClass"));
        ClientClass->resize(601, 378);
        actionConnect = new QAction(ClientClass);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(ClientClass);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionClear_Chat = new QAction(ClientClass);
        actionClear_Chat->setObjectName(QStringLiteral("actionClear_Chat"));
        centralWidget = new QWidget(ClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 10, 581, 321));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        messageList = new QListWidget(layoutWidget);
        messageList->setObjectName(QStringLiteral("messageList"));
        messageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        messageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        messageList->setAutoScroll(true);
        messageList->setAlternatingRowColors(false);
        messageList->setSelectionMode(QAbstractItemView::NoSelection);
        messageList->setFlow(QListView::TopToBottom);
        messageList->setProperty("isWrapping", QVariant(false));
        messageList->setWordWrap(true);

        verticalLayout_2->addWidget(messageList);

        messageEdit = new QLineEdit(layoutWidget);
        messageEdit->setObjectName(QStringLiteral("messageEdit"));
        messageEdit->setClearButtonEnabled(false);

        verticalLayout_2->addWidget(messageEdit);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        userList = new QListWidget(layoutWidget1);
        userList->setObjectName(QStringLiteral("userList"));

        verticalLayout->addWidget(userList);

        sendButton = new QPushButton(layoutWidget1);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setAutoDefault(false);

        verticalLayout->addWidget(sendButton);

        splitter->addWidget(layoutWidget1);
        ClientClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 601, 21));
        menuConnect = new QMenu(menuBar);
        menuConnect->setObjectName(QStringLiteral("menuConnect"));
        menuChat = new QMenu(menuBar);
        menuChat->setObjectName(QStringLiteral("menuChat"));
        ClientClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ClientClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ClientClass->setStatusBar(statusBar);
        QWidget::setTabOrder(messageEdit, sendButton);
        QWidget::setTabOrder(sendButton, messageList);
        QWidget::setTabOrder(messageList, userList);

        menuBar->addAction(menuConnect->menuAction());
        menuBar->addAction(menuChat->menuAction());
        menuConnect->addAction(actionConnect);
        menuConnect->addAction(actionDisconnect);
        menuChat->addAction(actionClear_Chat);

        retranslateUi(ClientClass);
        QObject::connect(messageEdit, SIGNAL(returnPressed()), sendButton, SLOT(click()));
        QObject::connect(actionClear_Chat, SIGNAL(triggered()), messageList, SLOT(clear()));

        messageList->setCurrentRow(-1);
        sendButton->setDefault(false);


        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ClientClass)
    {
        ClientClass->setWindowTitle(QApplication::translate("ClientClass", "Client", 0));
        actionConnect->setText(QApplication::translate("ClientClass", "Connect", 0));
        actionDisconnect->setText(QApplication::translate("ClientClass", "Disconnect", 0));
        actionClear_Chat->setText(QApplication::translate("ClientClass", "Clear Chat", 0));
        sendButton->setText(QApplication::translate("ClientClass", "Send", 0));
        menuConnect->setTitle(QApplication::translate("ClientClass", "Connection", 0));
        menuChat->setTitle(QApplication::translate("ClientClass", "Chat", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
