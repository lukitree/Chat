/********************************************************************************
** Form generated from reading UI file 'connectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDIALOG_H
#define UI_CONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectDialog
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *usernameEdit;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLineEdit *portEdit;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *hostnameEdit;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *connectButton;

    void setupUi(QDialog *ConnectDialog)
    {
        if (ConnectDialog->objectName().isEmpty())
            ConnectDialog->setObjectName(QStringLiteral("ConnectDialog"));
        ConnectDialog->resize(209, 122);
        widget = new QWidget(ConnectDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 60, 193, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        usernameEdit = new QLineEdit(widget);
        usernameEdit->setObjectName(QStringLiteral("usernameEdit"));

        horizontalLayout->addWidget(usernameEdit);

        widget1 = new QWidget(ConnectDialog);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(150, 10, 52, 41));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        portEdit = new QLineEdit(widget1);
        portEdit->setObjectName(QStringLiteral("portEdit"));

        verticalLayout->addWidget(portEdit);

        widget2 = new QWidget(ConnectDialog);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(10, 10, 135, 41));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        hostnameEdit = new QLineEdit(widget2);
        hostnameEdit->setObjectName(QStringLiteral("hostnameEdit"));

        verticalLayout_2->addWidget(hostnameEdit);

        widget3 = new QWidget(ConnectDialog);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(10, 90, 191, 25));
        horizontalLayout_2 = new QHBoxLayout(widget3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        connectButton = new QPushButton(widget3);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        horizontalLayout_2->addWidget(connectButton);

        QWidget::setTabOrder(hostnameEdit, portEdit);
        QWidget::setTabOrder(portEdit, usernameEdit);
        QWidget::setTabOrder(usernameEdit, connectButton);

        retranslateUi(ConnectDialog);
        QObject::connect(connectButton, SIGNAL(clicked()), ConnectDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(ConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDialog)
    {
        ConnectDialog->setWindowTitle(QApplication::translate("ConnectDialog", "ConnectDialog", 0));
        label->setText(QApplication::translate("ConnectDialog", "Username:", 0));
        usernameEdit->setText(QApplication::translate("ConnectDialog", "NoName", 0));
        label_3->setText(QApplication::translate("ConnectDialog", "Port", 0));
        portEdit->setText(QApplication::translate("ConnectDialog", "12234", 0));
        label_2->setText(QApplication::translate("ConnectDialog", "Server Address", 0));
        hostnameEdit->setText(QApplication::translate("ConnectDialog", "127.0.0.1", 0));
        connectButton->setText(QApplication::translate("ConnectDialog", "Connect", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectDialog: public Ui_ConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDIALOG_H
