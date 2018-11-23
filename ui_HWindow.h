/********************************************************************************
** Form generated from reading UI file 'HWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HWINDOW_H
#define UI_HWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HWindow
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *main;

    void setupUi(QWidget *HWindow)
    {
        if (HWindow->objectName().isEmpty())
            HWindow->setObjectName(QStringLiteral("HWindow"));
        HWindow->resize(400, 300);
        gridLayout_2 = new QGridLayout(HWindow);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        main = new QGridLayout();
        main->setSpacing(6);
        main->setObjectName(QStringLiteral("main"));

        gridLayout_2->addLayout(main, 0, 0, 1, 1);


        retranslateUi(HWindow);

        QMetaObject::connectSlotsByName(HWindow);
    } // setupUi

    void retranslateUi(QWidget *HWindow)
    {
        HWindow->setWindowTitle(QApplication::translate("HWindow", "HWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HWindow: public Ui_HWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HWINDOW_H
