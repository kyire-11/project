/********************************************************************************
** Form generated from reading UI file 'dbc.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBC_H
#define UI_DBC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBC
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;

    void setupUi(QWidget *DBC)
    {
        if (DBC->objectName().isEmpty())
            DBC->setObjectName(QString::fromUtf8("DBC"));
        DBC->resize(664, 431);
        gridLayout = new QGridLayout(DBC);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(DBC);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(562, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        tableWidget = new QTableWidget(DBC);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 2);


        retranslateUi(DBC);

        QMetaObject::connectSlotsByName(DBC);
    } // setupUi

    void retranslateUi(QWidget *DBC)
    {
        DBC->setWindowTitle(QCoreApplication::translate("DBC", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("DBC", " \346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DBC: public Ui_DBC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBC_H
