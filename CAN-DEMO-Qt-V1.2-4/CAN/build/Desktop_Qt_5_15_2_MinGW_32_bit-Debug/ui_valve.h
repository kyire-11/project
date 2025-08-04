/********************************************************************************
** Form generated from reading UI file 'valve.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALVE_H
#define UI_VALVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_valve
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout;
    QLabel *label_28;
    QComboBox *comboBox_11;
    QLabel *label_29;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_7;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_13;
    QLabel *label_18;
    QLineEdit *lineEdit_14;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLineEdit *lineEdit_12;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_14;
    QPushButton *pushButton_17;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_12;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *label_9;
    QLabel *label_14;
    QLabel *label_10;
    QLabel *label_15;
    QLabel *label_11;
    QLabel *label_16;
    QChartView *graphicsView;
    QChartView *graphicsView_2;

    void setupUi(QWidget *valve)
    {
        if (valve->objectName().isEmpty())
            valve->setObjectName(QString::fromUtf8("valve"));
        valve->resize(692, 906);
        gridLayout_4 = new QGridLayout(valve);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_7 = new QGroupBox(valve);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout = new QGridLayout(groupBox_7);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_28 = new QLabel(groupBox_7);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout->addWidget(label_28, 0, 0, 1, 1);

        comboBox_11 = new QComboBox(groupBox_7);
        comboBox_11->setObjectName(QString::fromUtf8("comboBox_11"));

        gridLayout->addWidget(comboBox_11, 0, 1, 1, 2);

        label_29 = new QLabel(groupBox_7);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 1, 0, 1, 1);

        checkBox_4 = new QCheckBox(groupBox_7);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 1, 1, 1, 2);

        checkBox_5 = new QCheckBox(groupBox_7);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        gridLayout->addWidget(checkBox_5, 1, 3, 1, 1);

        checkBox_6 = new QCheckBox(groupBox_7);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

        gridLayout->addWidget(checkBox_6, 1, 4, 1, 1);

        checkBox_9 = new QCheckBox(groupBox_7);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));

        gridLayout->addWidget(checkBox_9, 2, 1, 1, 2);

        checkBox_7 = new QCheckBox(groupBox_7);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));

        gridLayout->addWidget(checkBox_7, 2, 3, 1, 1);

        comboBox = new QComboBox(groupBox_7);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 3, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_13 = new QLineEdit(groupBox_7);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));

        horizontalLayout_2->addWidget(lineEdit_13);

        label_18 = new QLabel(groupBox_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_2->addWidget(label_18);

        lineEdit_14 = new QLineEdit(groupBox_7);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));

        horizontalLayout_2->addWidget(lineEdit_14);


        gridLayout->addLayout(horizontalLayout_2, 3, 2, 1, 2);

        pushButton = new QPushButton(groupBox_7);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 4, 1, 1);

        label = new QLabel(groupBox_7);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_7);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEdit, 4, 1, 1, 2);

        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEdit_12 = new QLineEdit(groupBox_7);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEdit_12, 5, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_14 = new QPushButton(groupBox_7);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_14);

        pushButton_17 = new QPushButton(groupBox_7);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_17);

        pushButton_2 = new QPushButton(groupBox_7);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 4);


        gridLayout_4->addWidget(groupBox_7, 0, 0, 1, 1);

        groupBox = new QGroupBox(valve);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 3, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 4, 0, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 5, 0, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 5, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 6, 0, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 6, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 1, 1, 1);

        graphicsView = new QChartView(valve);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(graphicsView, 1, 0, 1, 2);

        graphicsView_2 = new QChartView(valve);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(graphicsView_2, 2, 0, 1, 2);


        retranslateUi(valve);

        QMetaObject::connectSlotsByName(valve);
    } // setupUi

    void retranslateUi(QWidget *valve)
    {
        valve->setWindowTitle(QCoreApplication::translate("valve", "Form", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("valve", "\347\273\230\345\233\276\350\256\276\345\256\232", nullptr));
        label_28->setText(QCoreApplication::translate("valve", "\351\230\200\350\212\202\347\202\271:", nullptr));
        label_29->setText(QCoreApplication::translate("valve", "\347\273\230\345\210\266\345\217\230\351\207\217:", nullptr));
        checkBox_4->setText(QCoreApplication::translate("valve", "\351\230\200\350\212\257\344\275\215\347\247\273", nullptr));
        checkBox_5->setText(QCoreApplication::translate("valve", "PWM1", nullptr));
        checkBox_6->setText(QCoreApplication::translate("valve", "PWM2", nullptr));
        checkBox_9->setText(QCoreApplication::translate("valve", "LVDT\347\224\265\345\216\213", nullptr));
        checkBox_7->setText(QCoreApplication::translate("valve", "\345\244\226\351\203\250\350\276\223\345\205\245", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("valve", "\351\230\200\350\212\257\344\275\215\347\247\273\345\200\274", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("valve", "PWMA\347\224\265\346\265\201\345\217\215\351\246\210\345\200\274", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("valve", "PWMB\347\224\265\346\265\201\345\217\215\351\246\210\345\200\274", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("valve", "\345\244\226\351\203\250\346\250\241\346\213\237\351\207\217", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("valve", "LVDT\345\217\215\351\246\210\347\224\265\345\216\213", nullptr));

        lineEdit_13->setText(QString());
        label_18->setText(QCoreApplication::translate("valve", "\342\200\224\342\200\224", nullptr));
        lineEdit_14->setText(QString());
        pushButton->setText(QCoreApplication::translate("valve", "\350\260\203\346\225\264\351\207\217\347\250\213", nullptr));
        label->setText(QCoreApplication::translate("valve", "\347\273\230\345\233\276\345\221\250\346\234\237(ms)\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("valve", "\346\265\213\350\257\225\346\227\266\351\227\264(min)\357\274\232", nullptr));
        lineEdit_12->setText(QString());
        pushButton_14->setText(QCoreApplication::translate("valve", "\345\274\200\345\247\213\347\273\230\345\233\276", nullptr));
        pushButton_17->setText(QCoreApplication::translate("valve", "\345\201\234\346\255\242\347\273\230\345\233\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("valve", "\351\207\215\346\226\260\347\273\230\345\233\276", nullptr));
        groupBox->setTitle(QCoreApplication::translate("valve", "\345\256\236\346\227\266\346\230\276\347\244\272", nullptr));
        label_2->setText(QCoreApplication::translate("valve", "\346\225\205\351\232\234\346\212\245\350\255\246\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
        label_4->setText(QCoreApplication::translate("valve", "\346\230\257\345\220\246\346\234\211LVDT\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
        label_7->setText(QCoreApplication::translate("valve", "\351\230\200\350\212\257\344\275\215\347\247\273\345\200\274\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
        label_8->setText(QCoreApplication::translate("valve", "PWMA\347\224\265\346\265\201\345\217\215\351\246\210\345\200\274\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
        label_9->setText(QCoreApplication::translate("valve", "PWMB\347\224\265\346\265\201\345\217\215\351\246\210\345\200\274\357\274\232", nullptr));
        label_14->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
        label_10->setText(QCoreApplication::translate("valve", "\345\244\226\351\203\250\346\250\241\346\213\237\351\207\217\357\274\232", nullptr));
        label_15->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
        label_11->setText(QCoreApplication::translate("valve", "LVDT\345\217\215\351\246\210\347\224\265\345\216\213\357\274\232", nullptr));
        label_16->setText(QCoreApplication::translate("valve", "\346\227\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class valve: public Ui_valve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALVE_H
