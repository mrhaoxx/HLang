/********************************************************************************
** Form generated from reading UI file 'commandline.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDLINE_H
#define UI_COMMANDLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_commandline
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QTextBrowser *textBrowser;

    void setupUi(QMainWindow *commandline)
    {
        if (commandline->objectName().isEmpty())
            commandline->setObjectName(QStringLiteral("commandline"));
        commandline->resize(418, 543);
        commandline->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(commandline);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setReadOnly(true);

        gridLayout->addWidget(textBrowser, 0, 0, 1, 2);

        commandline->setCentralWidget(centralWidget);

        retranslateUi(commandline);

        QMetaObject::connectSlotsByName(commandline);
    } // setupUi

    void retranslateUi(QMainWindow *commandline)
    {
        commandline->setWindowTitle(QApplication::translate("commandline", "commandline", nullptr));
        textBrowser->setHtml(QApplication::translate("commandline", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">------------------------CommandLine--------------------------</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&gt;&gt;</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class commandline: public Ui_commandline {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDLINE_H
