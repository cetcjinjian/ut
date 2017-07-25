/********************************************************************************
** Form generated from reading UI file 'querycode.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYCODE_H
#define UI_QUERYCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QueryCode
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;

    void setupUi(QDialog *queryCode)
    {
        if (queryCode->objectName().isEmpty())
            queryCode->setObjectName(QStringLiteral("queryCode"));
        queryCode->resize(298, 109);
        pushButton = new QPushButton(queryCode);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 40, 61, 20));
        lineEdit = new QLineEdit(queryCode);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(40, 40, 113, 20));

        retranslateUi(queryCode);

        QMetaObject::connectSlotsByName(queryCode);
    } // setupUi

    void retranslateUi(QDialog *queryCode)
    {
        queryCode->setWindowTitle(QApplication::translate("QueryCode", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QueryCode", "\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QueryCode : public Ui_QueryCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYCODE_H
