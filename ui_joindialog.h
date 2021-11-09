/********************************************************************************
** Form generated from reading UI file 'joindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINDIALOG_H
#define UI_JOINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mycombobox.h"

QT_BEGIN_NAMESPACE

class Ui_joinDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QWidget *portWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *portLayout;
    QLabel *portlabel;
    MyComboBox *portBox;
    QLabel *portErr;
    QWidget *nameWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *nameLayout;
    QLabel *namelabel;
    QLineEdit *userNameEdit;
    QLabel *nameErr;
    QPushButton *pushButton_2;

    void setupUi(QDialog *joinDialog)
    {
        if (joinDialog->objectName().isEmpty())
            joinDialog->setObjectName(QString::fromUtf8("joinDialog"));
        joinDialog->resize(360, 560);
        joinDialog->setMinimumSize(QSize(0, 0));
        joinDialog->setMaximumSize(QSize(360, 560));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/wechat.png"), QSize(), QIcon::Normal, QIcon::Off);
        joinDialog->setWindowIcon(icon);
        joinDialog->setSizeGripEnabled(false);
        joinDialog->setModal(false);
        label = new QLabel(joinDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 20, 201, 191));
        label->setAutoFillBackground(false);
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/wechat.png")));
        label->setScaledContents(true);
        pushButton = new QPushButton(joinDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 450, 241, 31));
        portWidget = new QWidget(joinDialog);
        portWidget->setObjectName(QString::fromUtf8("portWidget"));
        portWidget->setGeometry(QRect(59, 259, 234, 60));
        verticalLayout = new QVBoxLayout(portWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        portLayout = new QHBoxLayout();
        portLayout->setObjectName(QString::fromUtf8("portLayout"));
        portlabel = new QLabel(portWidget);
        portlabel->setObjectName(QString::fromUtf8("portlabel"));

        portLayout->addWidget(portlabel);

        portBox = new MyComboBox(portWidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setMinimumSize(QSize(160, 20));
        portBox->setBaseSize(QSize(160, 20));

        portLayout->addWidget(portBox);


        verticalLayout->addLayout(portLayout);

        portErr = new QLabel(portWidget);
        portErr->setObjectName(QString::fromUtf8("portErr"));
        portErr->setStyleSheet(QString::fromUtf8("color=rgb(255, 0, 0)"));

        verticalLayout->addWidget(portErr);

        nameWidget = new QWidget(joinDialog);
        nameWidget->setObjectName(QString::fromUtf8("nameWidget"));
        nameWidget->setGeometry(QRect(60, 340, 234, 58));
        verticalLayout_2 = new QVBoxLayout(nameWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        nameLayout = new QHBoxLayout();
        nameLayout->setObjectName(QString::fromUtf8("nameLayout"));
        namelabel = new QLabel(nameWidget);
        namelabel->setObjectName(QString::fromUtf8("namelabel"));

        nameLayout->addWidget(namelabel);

        userNameEdit = new QLineEdit(nameWidget);
        userNameEdit->setObjectName(QString::fromUtf8("userNameEdit"));
        userNameEdit->setMinimumSize(QSize(160, 20));
        userNameEdit->setMaximumSize(QSize(160, 20));
        userNameEdit->setBaseSize(QSize(160, 20));

        nameLayout->addWidget(userNameEdit);


        verticalLayout_2->addLayout(nameLayout);

        nameErr = new QLabel(nameWidget);
        nameErr->setObjectName(QString::fromUtf8("nameErr"));
        nameErr->setStyleSheet(QString::fromUtf8("color=rgb(255, 0, 0)"));

        verticalLayout_2->addWidget(nameErr);

        pushButton_2 = new QPushButton(joinDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(340, 0, 21, 20));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);

        retranslateUi(joinDialog);

        QMetaObject::connectSlotsByName(joinDialog);
    } // setupUi

    void retranslateUi(QDialog *joinDialog)
    {
        joinDialog->setWindowTitle(QApplication::translate("joinDialog", "wechat-fake", nullptr));
        label->setText(QString());
        pushButton->setText(QApplication::translate("joinDialog", "\347\231\273\345\275\225", nullptr));
        portlabel->setText(QApplication::translate("joinDialog", "\345\217\257\347\224\250\347\253\257\345\217\243", nullptr));
        portErr->setText(QString());
        namelabel->setText(QApplication::translate("joinDialog", "\347\231\273\345\275\225\345\220\215\347\247\260", nullptr));
        nameErr->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class joinDialog: public Ui_joinDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINDIALOG_H
